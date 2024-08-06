# NOT WRITTEN LIKE A NORMAL MAKEFILE
# Just a convenient way to call CMake functions from Vim
# This assumes you have CMake and Ninja installed and working

all:
	ninja -C build
	./build/bin/sdl3test

setup_release:
	yes | rm -rf build
	cmake -S . -B build/ -DCMAKE_BUILD_TYPE=Release -G Ninja

setup_debug:
	yes | rm -rf build
	cmake -S . -B build/ -DCMAKE_BUILD_TYPE=Debug -G Ninja

clean:
	yes | rm -rf build
