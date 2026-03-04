#include <tokenizer.hpp>

Tokenizer::Tokenizer():
    heading(false),
    text(false),
    code(false),
    italic(false),
    bold(false),
    italic_bold(false),
    beg_line(true),

    line(1),
    line_pos(0),
    pos(0),
    tab_level(0),
    heading_level(0)
{}

Tokenizer::~Tokenizer() {}

Token Tokenizer::parseNext(std::istream& is) {
    char c;
    c = is.get();
    return Token(TokenType::Text, pos, 1, line, line_pos);
}

std::vector<Token> Tokenizer::tokenize(std::istream& is) {
    
    std::vector<Token> tokens {};

    while (!is.eof()) {
        std::cout << "parsing ..." << std::endl;
        tokens.push_back(parseNext(is));    
    }

    return tokens;
}
