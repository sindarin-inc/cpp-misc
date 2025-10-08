#pragma once

#include <cassert>
#include <cstddef>
#include <memory>
#include <utility>

#include "Spiram/EspHeapCapsCompat.hpp"

template <typename T>
struct SpiramAllocator {
    using value_type = T;

    SpiramAllocator() = default;

    template <typename U>
    SpiramAllocator(const SpiramAllocator<U> &) {}

    auto allocate(std::size_t n) -> T * {
        // Using a pointer type as T will otherwise raises a warning since a common bug is to use a
        // pointer type in sizeof incorrectly. But we really do want the size of the pointer. As of
        // this writing, there are a couple of `SpiramMap` that have `const char *` as their values.
        // NOLINTNEXTLINE(bugprone-sizeof-expression)
        return reinterpret_cast<T *>(heap_caps_malloc(n * sizeof(T), MALLOC_CAP_SPIRAM));
    }

    template <typename... ARGS>
    auto allocateShared(ARGS &&...args) -> std::shared_ptr<T> {
        T *tp = allocate(1);
        assert(tp);
        T *p = new (tp) T(std::forward<ARGS>(args)...);
        return std::shared_ptr<T>(p, &heap_caps_free);
    }

    void deallocate(T *p, std::size_t n) { heap_caps_free(reinterpret_cast<void *>(p)); }
};

template <typename T, typename... ARGS>
auto SpiramPtr(ARGS &&...args) -> std::shared_ptr<T> {
    static SpiramAllocator<T> allocator;
    return allocator.allocateShared(std::forward<ARGS>(args)...);
}

template <typename T, typename U>
auto operator==(const SpiramAllocator<T> &, const SpiramAllocator<U> &) -> bool {
    return true;
}

template <typename T, typename U>
auto operator!=(const SpiramAllocator<T> &, const SpiramAllocator<U> &) -> bool {
    return false;
}
