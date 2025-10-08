#pragma once

#include <vector>

template <typename T>
struct SpiramAllocator;

template <typename T>
using SpiramVector = std::vector<T, SpiramAllocator<T>>;
