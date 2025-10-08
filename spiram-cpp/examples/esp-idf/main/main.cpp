#include <Spiram/Allocator.hpp>
#include <Spiram/Map.hpp>
#include <Spiram/Memory.hpp>
#include <Spiram/String.hpp>
#include <Spiram/Vector.hpp>
#include <cstdio>
#include <string>
#include <vector>

extern "C" void app_main(void) {
    // Exercise SpiramString
    SpiramString s1("hello");
    SpiramString s2(std::string("world"));
    SpiramString combined(s1 + SpiramString(" ") + s2);

    // Exercise SpiramVector
    SpiramVector<int> v;
    v.push_back(1);
    v.push_back(2);

    // Exercise SpiramMap
    SpiramMap<SpiramString, int> m;
    m[combined] = 42;

    // Exercise Spiram malloc wrappers
    void *p = SpiramMalloc(128);
    p = SpiramRealloc(p, 256);
    SpiramFree(p);

    // Print something so we know it links
    printf("combined(%zu): %s; v.size=%zu; m.size=%zu\n", static_cast<size_t>(combined.size()),
           combined.c_str(), static_cast<size_t>(v.size()), static_cast<size_t>(m.size()));
}
