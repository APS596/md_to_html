all: build

.PHONY: build
build:
	mkdir -p build
	g++ -std=c++23 -Iinclude src/main.cpp src/token.cpp src/parser.cpp -o build/mdhtml

