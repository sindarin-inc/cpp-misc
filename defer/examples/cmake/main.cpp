#include <Defer/Defer.hpp>
#include <cstdio>

int main() {
    std::printf("enter\n");
    defer { std::printf("exit\n"); };
    std::printf("done\n");
    return 0;
}
