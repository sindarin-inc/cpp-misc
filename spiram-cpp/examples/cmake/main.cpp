#include <Spiram/Allocator.hpp>
#include <Spiram/Map.hpp>
#include <Spiram/Memory.hpp>
#include <Spiram/String.hpp>
#include <Spiram/Vector.hpp>
#include <cstdio>

int main() {
    SpiramString a("hello"), b("desktop");
    SpiramString combined = SpiramString(a + SpiramString(" ") + b);

    SpiramVector<int> v;
    v.push_back(3);

    SpiramMap<SpiramString, int> m;
    m[combined] = 7;

    void *p = SpiramMalloc(64);
    p = SpiramRealloc(p, 128);
    SpiramFree(p);

    std::printf("%s v.size=%zu m.size=%zu\n", combined.c_str(), (size_t)v.size(), (size_t)m.size());
    return 0;
}
