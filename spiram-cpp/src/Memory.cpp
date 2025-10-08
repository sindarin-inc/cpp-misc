#include "Spiram/Memory.hpp"

auto SpiZAlloc(void *opaque, size_t items, size_t size) -> void * {
    return SpiramMalloc(items * size);
}

void SpiZFree(void *opaque, void *address) { SpiramFree(address); }
