#pragma once

#include <token.hpp>

#include <iostream>
#include <string>
#include <vector>


class Generator {

    public:
        Generator(std::vector<Token>& tokens);
        ~Generator();

        std::string extractText(Token t, std::istream& is);
        void generateHTML(std::istream& is, std::ostream& os);
        void generateHTMLPage(std::istream& is, std::ostream& os);

        

    private:
        std::vector<Token>& tokens;
        
        void writeHTMLTitle(int level, std::ostream& os);
        
        bool heading        = false;
        bool code           = false;
        bool italic         = false;
        bool bold           = false;
        bool italic_bold    = false;
        bool beg_line       = true;
        bool paragraph      = false;
        bool paragraph_lf   = false;
        int heading_level;
        unsigned int is_pos = 0;

};


void generateHTML(std::vector<Token> tokens, std::istream& is, std::ostream& os);
