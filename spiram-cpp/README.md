## SPIRAM C++ utilities for ESP-IDF

This component provides C++ helpers to allocate STL containers and strings in PSRAM (SPIRAM) on ESP32 platforms. It also contains a compatibility layer for non-Espressif platforms that falls back to the equivalent STL types.

### Usage

Include headers from `include/Spiram/` and link the component via IDF Component Manager or as a local component.

Key types and utilities:
- `SpiramAllocator<T>`: allocator targeting `MALLOC_CAP_SPIRAM`
- `SpiramString`: `std::basic_string` using `SpiramAllocator<char>`
- `SpiramVector<T>` / `SpiramMap<K,V>` / `SpiramOrderedMap<K,V>`
- `SpiramMalloc/SpiramFree/SpiramRealloc`, `SpiramPtr`, `SpiramArrayPtr`
