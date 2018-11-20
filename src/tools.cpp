#include <napi.h>

extern "C"
{
#include <glib.h>
#include <zlib.h>
}

#define COMPRESS_XMP_TAGS "only large entries"

char *dt_exif_xmp_encode_internal(const unsigned char *input, const int len, int *output_len, gboolean do_compress)
{
  char *output = NULL;

  if (do_compress)
  {
    int result;
    uLongf destLen = compressBound(len);
    unsigned char *buffer1 = (unsigned char *)malloc(destLen);

    result = compress(buffer1, &destLen, input, len);

    if (result != Z_OK)
    {
      free(buffer1);
      return NULL;
    }

    // we store the compression factor
    const int factor = MIN(len / destLen + 1, 99);

    char *buffer2 = (char *)g_base64_encode(buffer1, destLen);
    free(buffer1);
    if (!buffer2)
      return NULL;

    int outlen = strlen(buffer2) + 5; // leading "gz" + compression factor + base64 string + trailing '\0'
    output = (char *)malloc(outlen);
    if (!output)
    {
      g_free(buffer2);
      return NULL;
    }

    output[0] = 'g';
    output[1] = 'z';
    output[2] = factor / 10 + '0';
    output[3] = factor % 10 + '0';
    g_strlcpy(output + 4, buffer2, outlen);
    g_free(buffer2);

    if (output_len)
      *output_len = outlen;
  }
  else
  {
    const char hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

    output = (char *)malloc(2 * len + 1);
    if (!output)
      return NULL;

    if (output_len)
      *output_len = 2 * len + 1;

    for (int i = 0; i < len; i++)
    {
      const int hi = input[i] >> 4;
      const int lo = input[i] & 15;
      output[2 * i] = hex[hi];
      output[2 * i + 1] = hex[lo];
    }
    output[2 * len] = '\0';
  }

  return output;
}

// encode binary blob into text:
char *dt_exif_xmp_encode(const unsigned char *input, const int len, int *output_len)
{
#define COMPRESS_THRESHOLD 100

  gboolean do_compress = FALSE;

  // if input data field exceeds a certain size we compress it and convert to base64;
  // main reason for compression: make more xmp data fit into 64k segment within
  // JPEG output files.
  const char *config = COMPRESS_XMP_TAGS;

  if (!strcmp(config, "always"))
    do_compress = TRUE;
  else if ((len > COMPRESS_THRESHOLD) && !strcmp(config, "only large entries"))
    do_compress = TRUE;
  else
    do_compress = FALSE;

  return dt_exif_xmp_encode_internal(input, len, output_len, do_compress);

#undef COMPRESS_THRESHOLD
}

unsigned char *dt_exif_xmp_decode(const char *input, const int len, int *output_len)
{
  unsigned char *output = NULL;

  // check if data is in compressed format
  if (!strncmp(input, "gz", 2))
  {
    // we have compressed data in base64 representation with leading "gz"

    // get stored compression factor so we know the needed buffer size for uncompress
    const float factor = 10 * (input[2] - '0') + (input[3] - '0');

    // get a rw copy of input buffer omitting leading "gz" and compression factor
    unsigned char *buffer = (unsigned char *)strdup(input + 4);
    if (!buffer)
      return NULL;

    // decode from base64 to compressed binary
    gsize compressed_size;
    g_base64_decode_inplace((char *)buffer, &compressed_size);

    // do the actual uncompress step
    int result = Z_BUF_ERROR;
    uLongf bufLen = factor * compressed_size;
    uLongf destLen;

    // we know the actual compression factor but if that fails we re-try with
    // increasing buffer sizes, eg. we don't know (unlikely) factors > 99
    do
    {
      if (output)
        free(output);
      output = (unsigned char *)malloc(bufLen);
      if (!output)
        break;

      destLen = bufLen;

      result = uncompress(output, &destLen, buffer, compressed_size);

      bufLen *= 2;

    } while (result == Z_BUF_ERROR);

    free(buffer);

    if (result != Z_OK)
    {
      if (output)
        free(output);
      return NULL;
    }

    if (output_len)
      *output_len = destLen;
  }
  else
  {
// we have uncompressed data in hexadecimal ascii representation

// ascii table:
// 48- 57 0-9
// 97-102 a-f
#define TO_BINARY(a) (a > 57 ? a - 97 + 10 : a - 48)

    // make sure that we don't find any unexpected characters indicating corrupted data
    if (strspn(input, "0123456789abcdef") != strlen(input))
      return NULL;

    output = (unsigned char *)malloc(len / 2);
    if (!output)
      return NULL;

    if (output_len)
      *output_len = len / 2;

    for (int i = 0; i < len / 2; i++)
    {
      const int hi = TO_BINARY(input[2 * i]);
      const int lo = TO_BINARY(input[2 * i + 1]);
      output[i] = (hi << 4) | lo;
    }
#undef TO_BINARY
  }

  return output;
}
