/**
 * @file parser.cpp
 *
 * @author APS596
 */

#include <exception>
#include <format>
#include <parser.hpp>

#include <stdexcept>
#include <token.hpp>


bool checkGrammar(std::vector<Token> tokens) {

    State state {};

    for (auto& t: tokens) {
        switch (t.type) {
            case TokenType::Title1:
                state.beg_line = false;
                state.heading = true;
                state.heading_level = 1;
                break;
            case TokenType::Title2:
                state.beg_line = false;
                state.heading = true;
                state.heading_level = 2;
                break;
            case TokenType::Title3:
                state.beg_line = false;
                state.heading = true;
                state.heading_level = 3;
                break;
            case TokenType::Title4:
                state.beg_line = false;
                state.heading = true;
                state.heading_level = 4;
                break;
            case TokenType::Title5:
                state.beg_line = false;
                state.heading = true;
                state.heading_level = 5;
                break;
            case TokenType::Title6:
                state.beg_line = false;
                state.heading = true;
                state.heading_level = 6;
                break;

            case TokenType::Return:
                if (state.heading && !state.heading_filled) {
                    throw std::invalid_argument(std::format("Empty title, {}", t.getInfo()));
                } else if (state.heading && state.heading_filled) {
                    state.heading = false;
                    state.heading_filled = true;
                } else if (state.italic) {
                    throw std::invalid_argument(std::format("Italic block not closed before line return, {}", t.getInfo()));
                } else if (state.bold) {
                    throw std::invalid_argument(std::format("Bold block not closed before line return, {}", t.getInfo()));
                } else if (state.italic_bold) {
                    throw std::invalid_argument(std::format("ItalicBold block not closed before line return, {}", t.getInfo()));
                }

                state.beg_line = true;
                break;

            case TokenType::Text:
                if (state.heading) {
                    state.heading_filled = true;
                }
                break;
            
            case TokenType::Italic:
                state.italic ^= 1;
                break;

            case TokenType::Bold:
                state.bold ^= 1;
                break;

            case TokenType::ItalicBold:
                state.italic_bold ^= 1;
                break;

            default:
                break;
        }
    }

    return true;
}
