/**
 * @file token.hpp
 * @brief markdown representation in the form of tokens
 * @author APS596
 */

#pragma once

#include <iostream>
#include <string>


/**
 * @brief Markdown tokens
 */
enum class TokenType {
    Return,               //< '\n' caracter
    Tab,                  //< '\t' or "    " (4 spaces)
    Eof,                  //< end of source
    Text,                 //< Raw text 
    Title1,               //< Level 1 heading
    Title2,               //< Level 2 heading
    Title3,               //< Level 3 heading
    Title4,               //< Level 4 heading
    Title5,               //< Level 5 heading
    Title6,               //< Level 6 heading
    BlockQuote,           //< '<' line
    Italic,               //< '*'
    Bold,                 //< "**"
    ItalicBold,           //< "***"
    Code,                 //< '`'
    OrderedListItem,      //< 'x.' where x is a number
    UnorderedListItem,    //< '-'
    OpeningParenthesis,   //< '('
    ClosingParenthesis,   //< ')'
    OpeningBracket,       //< '['
    ClosingBracket,       //< ']'
    ExclamationMark,      //< '!'
};


/**
 * @brief get token name from TokenType
 * @param t token type
 * @return std::string
 */
std::string tokenName(TokenType t);


/**
 * @brief Token
 */
class Token {

    public:
        Token(
            TokenType t, 
            unsigned int pos,
            unsigned int length,
            unsigned int line,
            unsigned int line_pos
        );
        Token(Token &&) = default;
        Token(const Token &) = default;
        Token &operator=(Token &&) = default;
        Token &operator=(const Token &) = default;
        ~Token();

        /**
         * @brief Nicely serialize debug information of the token in a string
         */
        std::string getInfo();


        TokenType type;            //< type of the token

    private:
        unsigned int pos;          //< position of the first character of the token in the file
        unsigned int length;       //< number of character in the token

        unsigned int line;         //< on which line is this token
        unsigned int line_pos;     //< what is its position on the line
};


/**
 * Wrapper to getInfo()
 */
std::ostream& operator<<(std::ostream& os, Token t);
