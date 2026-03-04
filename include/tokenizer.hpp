#pragma once

#include <vector>

#include <token.hpp>

class Tokenizer {
    public:
        Tokenizer();
        ~Tokenizer();

        /**
         * @brief extract next token from input stream
         * @param is input stream
         */
        Token parseNext(std::istream& is);

        Token parseNewLine(std::istream& is, char& c);
        Token parseHeading(std::istream& is, char& c);
        Token parseText(std::istream& is, char& c);
        Token parseItalic(std::istream& is, char& c);
        Token parseBold(std::istream& is, char& c);
        Token parseItalicBold(std::istream& is, char& c);
        /**
         * @brief tokenize input source
         * @param is input stream
         */
        std::vector<Token> tokenize(std::istream& is);

    private:

        bool heading, text, code, italic, bold, italic_bold, beg_line;

        unsigned int line;
        unsigned int line_pos;
        unsigned int pos;
        unsigned int tab_level;
        unsigned int heading_level;
    
        unsigned int tok_pos;
        unsigned int tok_line;
        unsigned int tok_line_pos;
};



