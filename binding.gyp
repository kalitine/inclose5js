{
  "targets": [
    {
      "target_name": "inclose5",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [
        "src/index.cc",
        "lib/inclose5/BicsUtils.cpp",
        "lib/inclose5/globalsv.cpp",
        "lib/inclose5/inclose.cpp",
        "lib/inclose5/stdafx.cpp",
        "lib/inclose5/inclose5.cpp"
        ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    }
  ]
}