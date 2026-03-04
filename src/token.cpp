#include <format>

#include <token.hpp>

Token::Token(
    TokenType t, 
    unsigned int pos,
    unsigned int length,
    unsigned int line,
    unsigned int line_pos
):
    type(t),
    pos(pos),
    length(length),
    line(line),
    line_pos(line_pos)
{}


Token::~Token() {}


std::string tokenName(TokenType t) {
    switch (t) {
        case TokenType::Return:     return "\\n";
        case TokenType::Tab:        return "\\t";
        case TokenType::Text:       return "Text";
        case TokenType::Eof:        return "EOF";
        case TokenType::Title1:     return "Heading1";
        case TokenType::Title2:     return "Heading2";
        case TokenType::Title3:     return "Heading3";
        case TokenType::Title4:     return "Heading4";
        case TokenType::Title5:     return "Heading5";
        case TokenType::Title6:     return "Heading6";
        case TokenType::Italic:     return "Italic";
        case TokenType::Bold:       return "Bold";
        case TokenType::ItalicBold: return "ItalicBold";
        case TokenType::BlockQuote: return "BlockQuote";
        case TokenType::Code:       return "Code";
        default: return "too bad, not implemented !";
    }
}


std::string Token::getInfo() {
    return std::string(std::format("{} on {}:{}, l:{}, pos:{}", tokenName(type), line, line_pos, length, pos));
}

std::ostream& operator<<(std::ostream& os, Token t) {
    os << t.getInfo();
    return os;
}
