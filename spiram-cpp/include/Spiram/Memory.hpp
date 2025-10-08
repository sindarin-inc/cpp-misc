#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>

#include "Spiram/EspHeapCapsCompat.hpp"

template <typename T>
class CustomDeleter {
public:
    using FreeFuncPtr = void (*)(void *);

    explicit CustomDeleter(FreeFuncPtr freeFunc) : freeFunc_(freeFunc) {}

    void operator()(T *d) const { freeFunc_(d); }

private:
    FreeFuncPtr freeFunc_;
};

inline auto SpiramMalloc(size_t size) -> void * {
    return heap_caps_malloc(size, MALLOC_CAP_SPIRAM);
}
inline void SpiramFree(void *ptr) { heap_caps_free(ptr); }
inline auto SpiramRealloc(void *ptr, size_t size) -> void * {
    return heap_caps_realloc(ptr, size, MALLOC_CAP_SPIRAM);
}

template <typename T>
auto CustomArrayPtr(size_t len, void *(*mallocFunc)(size_t), void (*freeFunc)(void *))
    -> std::shared_ptr<T[]> {
    return std::shared_ptr<T[]>(static_cast<T *>(mallocFunc(len * sizeof(T))),
                                CustomDeleter<T>(freeFunc));
}

template <typename T>
auto SpiramArrayPtr(size_t len) -> std::shared_ptr<T[]> {
    return CustomArrayPtr<T>(len, &SpiramMalloc, &SpiramFree);
}

// miniz compatibility allocators
auto SpiZAlloc(void *opaque, size_t items, size_t size) -> void *;
void SpiZFree(void *opaque, void *address);
