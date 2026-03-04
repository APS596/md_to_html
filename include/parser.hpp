/**
 * @file parser.hpp
 * @brief Parsing function definition
 * @author APS596
 */

#pragma once

#include <iostream>
#include <vector>

#include <token.hpp>

struct State {
    bool heading        = false;
    bool heading_filled = false;
    bool code           = false;
    bool italic         = false;
    bool bold           = false;
    bool italic_bold    = false;
    bool beg_line       = true;
    int tab_level       = 0;
    int heading_level   = 1;
};

/**
 * @brief Parse source markdown into a vector of tokens
 *
 * @return vector of Token
 */
bool checkGrammar(std::vector<Token> tokens);

