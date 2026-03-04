all: build

SRCS := src/token.cpp src/parser.cpp src/tokenizer.cpp src/main.cpp

.PHONY: build
build:
	mkdir -p build
	g++ -std=c++23 -Iinclude $(SRCS) -o build/mdhtml

