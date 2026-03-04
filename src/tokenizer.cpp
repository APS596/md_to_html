/**
 * @file tokenizer.cpp
 * @brief Tokenization of the code
 */

#include <stdexcept>

#include <token.hpp>
#include <tokenizer.hpp>


Tokenizer::Tokenizer():
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
        case '*':  return false;
        default: return true;
    }
}

Token Tokenizer::parseNext(std::istream& is) {


    char c;
    TokenType t;

    tok_pos = pos;
    tok_line = line;
    tok_line_pos = line_pos;

    is.get(c);
    if (c == '\n') {
        return parseNewLine(is, c);
    } else if (c == '#' && beg_line) {
        return parseHeading(is, c);
    } else if (c == '*') {
        return parseEmphasized(is, c);
    } else {
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
    heading_level = 1;
    while (is.get(c) && c == '#') {
        heading_level ++;
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
        while (is.get(c)) {
            if (!isText(c)) {
                break;
            }
            pos ++;
            line_pos ++;
            l ++;
        }
        is.putback(c);
        return Token(TokenType::Text, tok_pos, l, tok_line, tok_line_pos);
}


Token Tokenizer::parseEmphasized(std::istream& is, char& c) {

    char tmp1, tmp2, tmp3;
    int tok_l = 0;
    TokenType t;
    is.get(tmp1);

    if (tmp1 == '*') {
        is.get(tmp2);
        if (tmp2 == '*') {
            is.get(tmp3);
            if (tmp3 == '*') {
               throw std::invalid_argument("unexpected '*' character, consider using \\*");
            } else {
                tok_l = 3;
                t = TokenType::ItalicBold;
                is.putback(tmp3);
            }
        } else {
            tok_l = 2;
            t = TokenType::Bold;
            is.putback(tmp2);
        }
    } else {
        tok_l = 1;
        t = TokenType::Italic;
        is.putback(tmp1);
    }
    pos += tok_l;
    line_pos += tok_l;
    return Token(t, tok_pos, tok_l, tok_line, tok_line_pos);
}


std::vector<Token> Tokenizer::tokenize(std::istream& is) {
    
    std::vector<Token> tokens {};
    char c;

    while (is.get(c)) {
        is.putback(c);
        tokens.push_back(parseNext(is));    
    }
    std::cout << "--" << pos << std::endl;

    return tokens;
}
