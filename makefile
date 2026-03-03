all: build

.PHONY: build
build:
	mkdir -p build
	g++ -std=c++23 src/main.cpp -o build/mdhtml
