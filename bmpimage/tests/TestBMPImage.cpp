#include <BMPImage/BMPImage.hpp>
#include <ImageTest/ImageTest.hpp>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

#include "catch_amalgamated.hpp"

TEST_CASE("Test bmp file rendering with golden comparison", "[bmp][image]") {
    const std::string fixturesDir = std::string(TESTS_DIR) + "/Fixtures";
    const std::string imagesDir = std::string(TESTS_DIR) + "/Images";

    const char *accept = std::getenv("ACCEPT_IMAGE_TESTS");

    auto renderAndCompare = [&](const std::string &bmpName, const std::string &goldenName) {
        const std::string bmpPath = fixturesDir + "/" + bmpName;

        std::ifstream ifs(bmpPath, std::ios::binary);
        REQUIRE(ifs.good());
        std::vector<uint8_t> bytes((std::istreambuf_iterator<char>(ifs)),
                                   std::istreambuf_iterator<char>());

        BMPImage image;
        REQUIRE(image.readFromBytes(bytes.data(), bytes.size()));

        const int w = image.getWidth();
        const int h = image.getHeight();
        REQUIRE(w > 0);
        REQUIRE(h > 0);

        // Convert 1bpp packed mask to 8bpp grayscale with white background
        std::vector<uint8_t> gray(static_cast<size_t>(w) * static_cast<size_t>(h));
        const uint8_t *mask = image.getBuffer();
        int bytesPerLine = (w + 7) / 8; // 8 pixels per byte

        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                size_t pixelIdx =
                    static_cast<size_t>(y) * static_cast<size_t>(w) + static_cast<size_t>(x);
                int byteIdx = y * bytesPerLine + (x / 8);
                int bitIdx = (x % 8); // LSB-first to match XBM and renderer drawXBitmap
                uint8_t bit = (mask[byteIdx] >> bitIdx) & 0x01;
                gray[pixelIdx] = bit ? 0 : 255; // 1 -> black, 0 -> white
            }
        }

        // Save current render as a PNG for inspection
        const std::string curName = goldenName + std::string("_cur.png");
        REQUIRE(Save8bpp(curName.c_str(), w, h, gray.data()));

        // Compare or seed golden
        int curW = 0, curH = 0;
        std::vector<uint8_t> grayCur;
        REQUIRE(Load8bpp(curName.c_str(), curW, curH, grayCur));

        const std::string goldenPath = imagesDir + "/" + goldenName + std::string(".png");
        int gw = 0, gh = 0;
        std::vector<uint8_t> grayGold;
        auto goldenExists = Load8bpp(goldenPath.c_str(), gw, gh, grayGold);
        if (accept || !goldenExists) {
            printf("Saving golden image because %p %d at path %s\n", (void *)accept, goldenExists,
                   goldenPath.c_str());
            REQUIRE(Save8bpp(goldenPath.c_str(), curW, curH, grayCur.data()));
        } else {
            printf("Comparing %s vs %s: cur=%dx%d golden=%dx%d\n", curName.c_str(),
                   goldenPath.c_str(), curW, curH, gw, gh);
            REQUIRE(gw == curW);
            REQUIRE(gh == curH);
            size_t diffs = 0;
            for (size_t i = 0; i < grayGold.size(); ++i) {
                if (grayCur[i] != grayGold[i]) {
                    ++diffs;
                    if (diffs < 5) { /* print a few sample diffs */
                    }
                }
            }
            if (diffs) {
                printf("Pixel diffs: %zu / %zu (%.3f%%) for %s\n", diffs, grayGold.size(),
                       (100.0 * diffs) / grayGold.size(), goldenName.c_str());
            }
            REQUIRE(Compare8bpp(grayCur.data(), grayGold.data(), grayGold.size()));
        }
    };

    SECTION("Books (grayscale)") { renderAndCompare("books.bmp", "BitmapViewBooks"); }

    SECTION("Books (pre-dithered)") { renderAndCompare("books_dithered.bmp", "BitmapViewBooks"); }
}
