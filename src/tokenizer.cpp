#include <stdexcept>
#include <token.hpp>
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
    line_pos(1),
    pos(0),
    tab_level(0),
    heading_level(0)
{}

Tokenizer::~Tokenizer() {}

bool isText(char c) {
    switch (c) {
        case '\n': return false;
        default: return true;
    }
}

Token Tokenizer::parseNext(std::istream& is) {

    char c;
    TokenType t;

    tok_pos = pos;
    tok_line = line;
    tok_line_pos = line_pos;

    c = is.get();

    if (c == '\n') {
        return parseNewLine(is, c);
    } 

    else if (c == '#' && beg_line) {
        return parseHeading(is, c);
    }

    else {
        return parseText(is, c);
    }
}

Token Tokenizer::parseNewLine(std::istream& is, char& c) {
        line ++;
        line_pos = 1;
        pos ++;
        beg_line = true;
        return Token(TokenType::Return, tok_pos, 1, tok_line, tok_line_pos);
}

Token Tokenizer::parseHeading(std::istream& is, char& c) {
    TokenType t;
    beg_line = false;
    while (c == '#') {
        heading_level ++;
        if (!is.eof()) {
            c = is.get();
        } else {
            throw std::invalid_argument(std::format("Unexpected line return after heading token on line {}", line));
        }
    }
    is.putback(c);
    switch (heading_level) {
        case 1: t = TokenType::Title1; break;
        case 2: t = TokenType::Title2; break;
        case 3: t = TokenType::Title3; break;
        case 4: t = TokenType::Title4; break;
        case 5: t = TokenType::Title5; break;
        case 6: t = TokenType::Title6; break;
        default: throw std::invalid_argument("bad heading token");
    }
    pos += heading_level;
    line_pos += heading_level;
    auto tok = Token(t, tok_pos, heading_level, tok_line, tok_line_pos);
    heading_level = 0;
    return tok; 
}

Token Tokenizer::parseText(std::istream& is, char& c) {
        beg_line = false;
        pos ++;
        line_pos ++;
        unsigned int l = 1;
        while (isText(c)) {
            if (is.eof()) {
                break;
            }
            c = is.get();
            pos ++;
            line_pos ++;
            l ++;
        }
        return Token(TokenType::Text, tok_pos, l-1, tok_line, tok_line_pos);
}

Token Tokenizer::parseItalic(std::istream& is, char& c) {
    return Token(TokenType::Eof, 0, 0, 0, 0);
}

Token Tokenizer::parseBold(std::istream& is, char& c) {
    return Token(TokenType::Eof, 0, 0, 0, 0);
}

Token Tokenizer::parseItalicBold(std::istream& is, char& c) {
    return Token(TokenType::Eof, 0, 0, 0, 0);
}

std::vector<Token> Tokenizer::tokenize(std::istream& is) {
    
    std::vector<Token> tokens {};

    while (!is.eof()) {
        tokens.push_back(parseNext(is));    
    }
    std::cout << "--" << pos << std::endl;

    return tokens;
}
