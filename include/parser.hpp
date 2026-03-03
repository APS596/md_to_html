/**
 * @file parser.hpp
 * @brief Parsing function definition
 * @author APS596
 */

#pragma once

#include <iostream>
#include <vector>

#include <token.hpp>


/**
 * @brief Parse source markdown into a vector of tokens
 *
 * @param is input stream for markdown source
 *
 * @return vector of Token
 */
const std::vector<Token> tokenizer(std::istream& is);


/**
 * @brief main parsing function, handle token generation, grammar checking and html generation
 *
 * @param is input stream (usually markdown source file)
 */
void parseMarkdown(std::istream& is);
