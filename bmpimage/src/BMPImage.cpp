#include "BMPImage/BMPImage.hpp"

#include <Log/Log.hpp>
#include <Spiram/Memory.hpp>

#include "Ditherer.hpp"
#include "bmp.h"

constexpr const char *TAG = "BMPImage";

std::shared_ptr<uint8_t[]> bmpConversionLUT = nullptr;

void BMPImage::createLUT() {
    if (bmpConversionLUT) {
        return;
    }

    bmpConversionLUT = SpiramArrayPtr<uint8_t>(256);

    // store bit-reversed and value flipped version of each byte
    // converts from bmp 1 bit to xbm format
    for (int i = 0; i < 256; i++) {
        uint8_t val = i;
        uint8_t out = 0;
        for (int b = 0; b < 8; b++) {
            out <<= 1;
            out |= val & 0b1;
            val >>= 1;
        }

        out ^= 0xFF;
        bmpConversionLUT[i] = out;
    }
}

auto BMPImage::readFromBytes(uint8_t *bmpbytes, int size) -> bool {
    bmp_image *img = BmpReadFromMemory(bmpbytes, static_cast<size_t>(size));
    if (!img) {
        LOGE(TAG, "Failed to read BMP image from memory");
        return false;
    }

    width_ = img->dib.bmiHeader.biWidth;
    height_ = img->dib.bmiHeader.biHeight;

    int datasize = img->dib.bmiHeader.biSizeImage;
    int bytesPerLine = datasize / height_;

    int bitcount = img->dib.bmiHeader.biBitCount;
    if (bitcount != 8 && bitcount != 1) {
        LOGE(TAG, "%d bit bmp not supported", bitcount);
        return false;
    }

    bitsPerPixel_ = bitcount;
    int outputBytesPerLine = (width_ + 7) / 8;
    int outputTotalBytes = outputBytesPerLine * height_;

    // allocate output buffer
    outputBuffer_ = SpiramArrayPtr<uint8_t>(outputTotalBytes);

    // if the bmp already has 1 bit per pixel, it can be displayed directly
    // convert to xbm format
    if (bitsPerPixel_ == 1) {
        // BMP stores lines of pixels starting at the bottom
        // copy starting at the bottom to match current bitmap format
        uint8_t *imptr;
        uint8_t *buf = outputBuffer_.get();

        for (int y = height_ - 1; y >= 0; y--) {
            imptr = &img->ciPixelArray[y * bytesPerLine];
            // bit convert to match xbm format
            for (int x = 0; x < outputBytesPerLine; x++) {
                buf[x] = bmpConversionLUT[imptr[x]];
            }

            buf += outputBytesPerLine;
        }
    } else if (bitsPerPixel_ == 8) {

        // this is an 8 bit grayscale image
        // dither the image into the allocated output buffer
        Ditherer::getInstance().ditherToBitmap(img->ciPixelArray, outputBuffer_.get(), width_,
                                               height_, bytesPerLine, true);
    }

    BmpCleanup(nullptr, img);
    return true;
}

auto BMPImage::getBitsPerPixel() const -> int { return bitsPerPixel_; }

auto BMPImage::getBuffer() -> uint8_t * { return outputBuffer_.get(); }

auto BMPImage::getWidth() const -> int { return width_; }

auto BMPImage::getHeight() const -> int { return height_; }
