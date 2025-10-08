.PHONY: build clean menuconfig save-defconfig

.DEFAULT_GOAL := build

build:
	idf.py build

menuconfig:
	idf.py menuconfig

save-defconfig:
	idf.py save-defconfig

clean:
	rm -rf build*
