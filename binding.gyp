{
  "targets": [
    {
      "target_name": "darkroom-xmp-tools",
      "sources": [
        "src/init.cpp",
        "src/tools.cpp",
        "src/sharpen.cpp",
        "src/levels.cpp",
        "src/shadhi.cpp",
        "src/defringe.cpp",
        "src/exposure.cpp",
        "src/blend.cpp",
        "src/clipping.cpp",
        "src/masks.cpp"
      ],
      "include_dirs" : [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      "conditions": [
        ['OS=="mac"', {
          "include_dirs" : [
            "/usr/include",
            "/usr/local/include",
            "/usr/local/Cellar/glib/2.56.1/lib/glib-2.0/include",
            "/usr/local/Cellar/glib/2.56.1/include/glib-2.0"
          ],
          "libraries": [
            '<!@(pkg-config --libs glib-2.0)',
            '<!@(pkg-config --libs zlib)'
          ],
          'cflags': [
            '<!@(pkg-config --cflags glib-2.0)',
            '<!@(pkg-config --cflags zlib)'
          ]
        }]
      ],
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }
  ]
}
