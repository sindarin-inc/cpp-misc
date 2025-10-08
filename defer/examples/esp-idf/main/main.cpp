#include <Defer/Defer.hpp>
#include <cstdio>

extern "C" void app_main() {
    std::printf("enter\n");
    defer { std::printf("exit\n"); };
    std::printf("done\n");
}
