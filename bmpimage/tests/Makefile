.PHONY: build test
build:
	@mkdir -p build
	@cd build && cmake .. && cmake --build . -j

test: build
	@cd build && ctest --output-on-failure

test-verbose: build
	@ctest -V -j1 --test-dir build

test-accept: build
	@cd build && ACCEPT_IMAGE_TESTS=1 ctest --output-on-failure

clean:
	@rm -rf build
