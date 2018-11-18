#ifndef TOOLS_H
#define TOOLS_H

char *dt_exif_xmp_encode(const unsigned char *input, const int len, int *output_len);

unsigned char *dt_exif_xmp_decode(const char *input, const int len, int *output_len);

#endif
