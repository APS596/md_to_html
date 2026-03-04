/**
 * @file main.cpp
 * @brief Call the parser and the html generator from file and parse input parameters
 * @author APS596
 */

#include <iostream>
#include <fstream>

#include <token.hpp>
#include <tokenizer.hpp>

int main (int argc, char *argv[]) {
    
    if (argc >= 2) {

        // Open file
        std::ifstream source {argv[1]};
        if (!source.is_open()) {
            throw std::invalid_argument(std::format("Unable to open file {}", argv[1]));
        }
            
        auto tokenizer = Tokenizer();

        auto tokens = tokenizer.tokenize(source);

        for (auto& t: tokens) {
            std::cout << t << std::endl;
        }

    } else {
        std::cout << "Markdown HTML converter. Usage mdhtml source.md > page.html" << std::endl;
    }

    return 0;
}
