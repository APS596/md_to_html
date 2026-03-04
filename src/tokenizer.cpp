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

Token Tokenizer::parseNext(std::istream& is) {

    char c;
    TokenType t;

    tok_pos = pos;
    tok_line = line;
    tok_line_pos = line_pos;

    c = is.get();

    if (c == '\n') {
        line ++;
        line_pos = 1;
        pos ++;
        beg_line = true;
        return Token(TokenType::Return, tok_pos, 1, tok_line, tok_line_pos);
    } 

    else if (c == '#' && beg_line) {
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

    else {
        beg_line = false;
        pos ++;
        line_pos ++;
        return Token(TokenType::Eof, tok_pos, 1, tok_line, tok_line_pos);
    }
}

std::vector<Token> Tokenizer::tokenize(std::istream& is) {
    
    std::vector<Token> tokens {};

    while (!is.eof()) {
        tokens.push_back(parseNext(is));    
    }
    std::cout << "--" << pos << std::endl;

    return tokens;
}
