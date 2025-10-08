.PHONY: build clean

.DEFAULT_GOAL := build clean

build:
	cmake -S . -B build
	cmake --build build -j

run: build
	./build/example

clean:
	rm -rf build*
