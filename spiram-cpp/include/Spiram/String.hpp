#pragma once

#include <functional>
#include <istream>
#include <memory>
#include <sstream>
#include <string>
#include <string_view>

#include "Spiram/Allocator.hpp"

class SpiramString : public std::basic_string<char, std::char_traits<char>, SpiramAllocator<char>> {
public:
    using Base = std::basic_string<char, std::char_traits<char>, SpiramAllocator<char>>;
    using Base::Base;

    explicit SpiramString(const std::string &str)
        : basic_string(str.begin(), str.end(), SpiramAllocator<char>()) {}

    explicit SpiramString(const Base &str)
        : basic_string(str.begin(), str.end(), SpiramAllocator<char>()) {}

    explicit operator std::string() const { return {this->begin(), this->end()}; }

    using Base::operator=;

    auto operator==(const SpiramString &str) const -> bool {
        return this->compare(str.c_str()) == 0;
    }
    auto operator==(const std::string &stdStr) const -> bool {
        return this->compare(stdStr.c_str()) == 0;
    }
    auto operator==(const char *str) const -> bool { return this->compare(str) == 0; }

    [[nodiscard]] auto substr(size_t pos = 0, size_t len = npos) const -> SpiramString {
        return {Base::substr(pos, len), SpiramAllocator<char>()};
    }
};

auto operator==(const std::string &stdStr, const SpiramString &spiramStr) -> bool;

namespace std {
template <>
struct hash<SpiramString> {
    auto operator()(const SpiramString &s) const noexcept -> size_t {
        return std::hash<std::string_view>{}(std::string_view(s.data(), s.size()));
    }
};
} // namespace std

class SpiramStringBuf : public std::streambuf {
public:
    SpiramStringBuf(const SpiramString &str) {
        char *begin = const_cast<char *>(str.data());
        char *end = begin + str.size();
        setg(begin, begin, end);
    }

protected:
    auto seekoff(off_type off, std::ios_base::seekdir dir, std::ios_base::openmode which)
        -> pos_type override {
        if (dir == std::ios_base::beg) {
            setg(eback(), eback() + off, egptr());
        } else if (dir == std::ios_base::cur) {
            setg(eback(), gptr() + off, egptr());
        } else if (dir == std::ios_base::end) {
            setg(eback(), egptr() + off, egptr());
        }
        return gptr() - eback();
    }

    auto seekpos(pos_type pos, std::ios_base::openmode which) -> pos_type override {
        return seekoff(pos, std::ios_base::beg, which);
    }
};

class SpiramIStream : public std::istream {
public:
    SpiramIStream(SpiramString str) : std::istream(&buf_), str_(std::move(str)), buf_(str_) {}

private:
    SpiramString str_;
    SpiramStringBuf buf_;
};
