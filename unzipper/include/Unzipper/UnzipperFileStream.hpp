#pragma once

#include <cerrno>
#include <cinttypes>
#include <cstddef>
#include <cstdint>
#include <fcntl.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

enum EPFSSeekWhence { EPFSSeekSet = SEEK_SET, EPFSSeekCur = SEEK_CUR, EPFSSeekEnd = SEEK_END };

class UnzipperFileStream {
public:
    virtual ~UnzipperFileStream() = default;
    virtual explicit operator bool() const = 0;
    virtual void close() = 0;
    virtual auto read(uint8_t *buf, size_t size) -> size_t = 0;
    virtual auto seek(off_t offset, EPFSSeekWhence whence) -> bool = 0;
    virtual auto position() -> size_t = 0;
};

class PosixUnzipperFileStream : public UnzipperFileStream {
public:
    PosixUnzipperFileStream() = default;
    PosixUnzipperFileStream(const char *path) { open(path); }
    ~PosixUnzipperFileStream() { close(); }

    auto open(const char *path) -> bool {
        close();
        fd_ = ::open(path, O_RDONLY);
        return fd_ >= 0;
    }

    explicit operator bool() const override { return fd_ >= 0; }

    void close() override {
        if (fd_ >= 0) {
            ::close(fd_);
            fd_ = -1;
        }
    }

    auto read(uint8_t *buf, size_t size) -> size_t override {
        if (fd_ < 0) return -1;
        return ::read(fd_, buf, size);
    }

    auto seek(off_t offset, EPFSSeekWhence whence) -> bool override {
        if (fd_ < 0) return false;
        off_t res = ::lseek(fd_, offset, static_cast<int>(whence));
        return res != (off_t)-1;
    }

    auto position() -> size_t override {
        if (fd_ < 0) return -1;
        return ::lseek(fd_, 0, SEEK_CUR);
    }

private:
    int fd_ = -1;
};