.PHONY: defer-examples-cmake defer-examples-esp-idf spiram-cpp-examples-cmake spiram-cpp-examples-esp-idf stringutil-examples-cmake stringutil-examples-esp-idf clean all format

defer-examples-cmake:
	@$(MAKE) -C defer/examples/cmake run

defer-examples-esp-idf:
	@$(MAKE) -C defer/examples/esp-idf build

spiram-cpp-examples-cmake:
	@$(MAKE) -C spiram-cpp/examples/cmake run

spiram-cpp-examples-esp-idf:
	@$(MAKE) -C spiram-cpp/examples/esp-idf build

stringutil-examples-cmake:
	@$(MAKE) -C stringutil/examples/cmake run

stringutil-examples-esp-idf:
	@$(MAKE) -C stringutil/examples/esp-idf build

cmake-examples: defer-examples-cmake spiram-cpp-examples-cmake stringutil-examples-cmake

clean:
	@$(MAKE) -C defer/examples/cmake clean
	@$(MAKE) -C defer/examples/esp-idf clean
	@$(MAKE) -C spiram-cpp/examples/cmake clean
	@$(MAKE) -C spiram-cpp/examples/esp-idf clean
	@$(MAKE) -C stringutil/examples/cmake clean
	@$(MAKE) -C stringutil/examples/esp-idf clean

all: defer-examples-cmake defer-examples-esp-idf spiram-cpp-examples-cmake spiram-cpp-examples-esp-idf stringutil-examples-cmake stringutil-examples-esp-idf
	@echo "All examples built successfully"

# Format all tracked C/C++ sources via git, excluding freetype and Catch2 amalgamation
CLANG_FORMAT ?= clang-format
FORMAT_FILES := $(shell git ls-files '*.c' '*.cc' '*.cxx' '*.cpp' '*.h' '*.hpp')

format:
	@echo Formatting $$((`echo "$(FORMAT_FILES)" | wc -w`)) files...
	@echo "$(FORMAT_FILES)" | xargs -n 50 $(CLANG_FORMAT) -i
