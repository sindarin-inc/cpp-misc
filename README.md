# cpp-misc

Assorted C++ utility libraries, primarily aimed at embedded/ESP-IDF targets, but most also build on desktop for testing.

## Libraries

### bmpimage

Simple 1bpp and 8bpp bitmap handling with dithering support.

- Include: `#include <BMPImage/BMPImage.hpp>`

### defer

Single-header scope guard macro for RAII-style defers.

- Include: `#include <Defer/Defer.hpp>`
- Usage:
  ```cpp
  {
      FILE* f = fopen("/tmp/file", "w");
      defer { if (f) fclose(f); };
      // ... use f ...
  } // fclose runs automatically
  ```

### idflog

Compatibility header for logging that uses ESP_LOG* if available otherwise falls back to `printf`.

- Include: `#include <Log/Log.hpp>`
- Usage:
  ```cpp
  {
      constexpr const char *TAG = "MyModule";
      LOGD(TAG, "Stuff happened %d times", count);
  }
  ```

### spiram-cpp

C++ helpers for ESP32 PSRAM (SPIRAM) allocation with STL-like containers and `std::string` compatible types. Falls back to normal STL on non-IDF builds.

- Include: `#include <Spiram/Allocator.hpp>`
- Include: `#include <Spiram/Map.hpp>`
- Include: `#include <Spiram/Memory.hpp>`
- Include: `#include <Spiram/String.hpp>`
- Include: `#include <Spiram/Vector.hpp>`

### stringutil

Small collection of string helpers.

- Include: `#include <StringUtil/StringUtil.hpp>`

### unzipper

Streaming decompressor for zip files. Useful for reading/decompressing parts of zip files without unzipping the whole thing.

- Include: `#include <Unzipper/Unzipper.hpp>`

## Building

- Desktop examples: inside each `examples/cmake` directory, run `make run`
- ESP-IDF examples: inside each `examples/esp-idf` directory, run `idf.py build` (or `make build`)
