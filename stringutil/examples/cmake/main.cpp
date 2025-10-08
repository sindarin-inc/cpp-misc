#include <StringUtil/StringUtil.hpp>
#include <cstdint>
#include <cstdio>

int main() {
    const char *text = "hello world from stringutil";
    std::printf("WordCount: %d\n", WordCount(text));

    const uint8_t bytes[] = {0xDE, 0xAD, 0xBE, 0xEF};
    auto hex = BytesToHex(bytes, sizeof(bytes), ":");
    std::printf("BytesToHex: %s\n", hex.c_str());

    auto formatted = StringFormat("Pi approx = %.2f", 3.14159);
    std::printf("StringFormat: %s\n", formatted.c_str());

    std::printf("HasPrefix(abcdef, abc): %s\n", HasPrefix("abcdef", "abc") ? "true" : "false");
    std::printf("HasSuffix(filename.txt, .txt): %s\n",
                HasSuffix(std::string("filename.txt"), ".txt") ? "true" : "false");

    std::printf("Commify(12345678): %s\n", Commify(12345678).c_str());

    std::printf("CaseInsensitiveCompare(Apple, banana): %s\n",
                CaseInsensitiveCompare(std::string("Apple"), std::string("banana")) ? "true"
                                                                                    : "false");

    auto replaced = ReplaceAll("one potato, two potato", "potato", "bagel");
    std::printf("ReplaceAll: %s\n", replaced.c_str());

    return 0;
}
