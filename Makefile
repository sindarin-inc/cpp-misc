.PHONY: build-cmake-defer build-cmake-spiram-cpp build-cmake-stringutil build-cmake build-esp-idf-defer build-esp-idf-spiram-cpp build-esp-idf-stringutil build-esp-idf test-bmpimage test clean format
.DEFAULT_GOAL := all

build-cmake-defer:
	@$(MAKE) -C defer/examples/cmake run

build-cmake-spiram-cpp:
	@$(MAKE) -C spiram-cpp/examples/cmake run

build-cmake-stringutil:
	@$(MAKE) -C stringutil/examples/cmake run

build-cmake: build-cmake-defer build-cmake-spiram-cpp build-cmake-stringutil

build-esp-idf-defer:
	@$(MAKE) -C defer/examples/esp-idf build

build-esp-idf-spiram-cpp:
	@$(MAKE) -C spiram-cpp/examples/esp-idf build

build-esp-idf-stringutil:
	@$(MAKE) -C stringutil/examples/esp-idf build

build-esp-idf: build-esp-idf-defer build-esp-idf-spiram-cpp build-esp-idf-stringutil

test-bmpimage:
	@$(MAKE) -C bmpimage/tests test

test: test-bmpimage

all: build-cmake build-esp-idf test
	@echo "All examples built successfully"

clean:
	@$(MAKE) -C defer/examples/cmake clean
	@$(MAKE) -C defer/examples/esp-idf clean
	@$(MAKE) -C spiram-cpp/examples/cmake clean
	@$(MAKE) -C spiram-cpp/examples/esp-idf clean
	@$(MAKE) -C stringutil/examples/cmake clean
	@$(MAKE) -C stringutil/examples/esp-idf clean
	@$(MAKE) -C bmpimage/tests clean

# Format all tracked C/C++ sources via git, excluding freetype and Catch2 amalgamation
CLANG_FORMAT ?= clang-format
FORMAT_FILES := $(shell git ls-files '*.c' '*.cc' '*.cxx' '*.cpp' '*.h' '*.hpp' | grep -Ev '^(vendor/)')

format:
	@echo Formatting $$((`echo "$(FORMAT_FILES)" | wc -w`)) files...
	@echo "$(FORMAT_FILES)" | xargs -n 50 $(CLANG_FORMAT) -i
