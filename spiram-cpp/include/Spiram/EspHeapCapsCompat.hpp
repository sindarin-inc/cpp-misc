#pragma once

#if defined(ESP_PLATFORM)

#include <esp_heap_caps.h>

#else

#include <cstdlib>

inline void *heap_caps_malloc(size_t size, unsigned caps) {
    (void)caps;
    return std::malloc(size);
}
inline void heap_caps_free(void *p) { std::free(p); }
inline void *heap_caps_realloc(void *p, size_t size, unsigned caps) {
    (void)caps;
    return std::realloc(p, size);
}

#ifndef MALLOC_CAP_SPIRAM
#define MALLOC_CAP_SPIRAM 0
#endif

#endif
