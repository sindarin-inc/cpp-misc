#include "StringUtil/StringUtil.hpp"

#include <algorithm>
#include <cstdarg>
#include <cstring>

auto WordCount(const char *str) -> int {
    int wordCount = 0;
    const char *s = str;
    bool newWord = true;
    while (*s) {
        if (isspace(*s)) {
            newWord = true;
        } else if (newWord) {
            wordCount++;
            newWord = false;
        }
        s++;
    }
    return wordCount;
}

// bytesToHex
// https://stackoverflow.com/a/3386294
auto BytesToHex(const uint8_t *data, size_t size, const char *separator) -> std::string {
    std::string result;
    for (size_t i = 0; i < size; ++i) {
        char buf[3];
        // NOLINTNEXTLINE(cert-err33-c) -- this is a safe format string
        snprintf(buf, sizeof(buf), "%02x", data[i]);
        result += buf;
        if (separator && i < size - 1) {
            result += separator;
        }
    }
    return result;
}

auto SafeSnprintf(char *str, size_t size, const char *format, ...) // NOLINT(cert-dcl50-cpp)
    -> bool {
    va_list args;
    va_start(args, format);
    int res = vsnprintf(str, size, format, args);
    va_end(args);

    // check if entire string was written
    if (res >= 0 && res < size) {
        return true;
    }

    // unable to write entire string
    return false;
}

auto HasSuffix(std::string const &str, std::string const &suffix) -> bool {
    return str.size() >= suffix.size() &&
           str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

auto HasPrefix(const char *str, const char *pre, size_t maxToCompare) -> bool {
    if (maxToCompare == 0) {
        maxToCompare = strlen(pre);
    }
    return strncmp(pre, str, maxToCompare) == 0;
}

auto Commify(uint32_t n) -> std::string {
    std::string str = StringFormat("%d", n);
    std::string result;
    // Reserve enough space to avoid reallocations
    result.reserve(str.length() + str.length() / 3);

    int count = 0;
    for (int i = str.length() - 1; i >= 0; --i) {
        result.push_back(str[i]);
        ++count;
        if (count == 3 && i > 0) {
            result.push_back(',');
            count = 0;
        }
    }

    // Since we built the string in reverse
    std::reverse(result.begin(), result.end());
    return result;
}

auto CaseInsensitiveCompare(const std::string &str1, const std::string &str2) -> bool {
    return std::lexicographical_compare(
        str1.begin(), str1.end(), str2.begin(), str2.end(),
        [](char c1, char c2) { return std::tolower(c1) < std::tolower(c2); });
};

auto ReplaceAll(std::string str, const std::string &from, const std::string &to) -> std::string {
    std::string::size_type pos = 0;
    while ((pos = str.find(from, pos)) != std::string::npos) {
        str.replace(pos, from.length(), to);
        pos += to.length();
    }
    return str;
}
