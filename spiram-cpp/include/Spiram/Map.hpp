#pragma once

#include <functional>
#include <map>
#include <unordered_map>

template <typename T>
struct SpiramAllocator;

template <typename K, typename V>
using SpiramMap = std::unordered_map<K, V, std::hash<K>, std::equal_to<K>,
                                     SpiramAllocator<std::pair<const K, V>>>;

template <typename K, typename V>
using SpiramOrderedMap = std::map<K, V, std::less<K>, SpiramAllocator<std::pair<const K, V>>>;
