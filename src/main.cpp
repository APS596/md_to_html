/**
 * @file main.cpp
 * @brief Call the parser and the html generator from file and parse input parameters
 * @author APS596
 */

#include <ios>
#include <iostream>
#include <fstream>

#include <token.hpp>
#include <tokenizer.hpp>
#include <parser.hpp>
#include <generator.hpp>

int main (int argc, char *argv[]) {
    
    if (argc >= 2) {

        // Open file
        std::ifstream source {argv[1]};
        if (!source.is_open()) {
            throw std::invalid_argument(std::format("Unable to open file {}", argv[1]));
        }
            
        auto tokenizer = Tokenizer();

        auto tokens = tokenizer.tokenize(source);

        std::cout << "Token generation ... \n" << std::endl;

        for (auto& t: tokens) {
            std::cout << t << std::endl;
        }

        std::cout << "======================================" << std::endl;

        std::cout << "grammar check ..." << std::endl;
        bool res = checkGrammar(tokens);
        std::cout << std::boolalpha << res << std::endl;

        std::cout << "======================================" << std::endl;

        std::cout << "Code generation\n" << std::endl;

        source.clear();
        source.seekg(0);

        std::ofstream page {"page.html"};

        generateHTML(tokens, source, page);

    } else {
        std::cout << "Markdown HTML converter. Usage mdhtml source.md > page.html" << std::endl;
    }

    return 0;
}
