#include <generator.hpp>


Generator::Generator(std::vector<Token>& tokens): tokens(tokens) {}

Generator::~Generator() {}


/**
 * @brief extract Token text from position in input stream
 *
 * @deprecated
 */
std::string Generator::extractText(Token t, std::istream& is) {
    if (t.getPos() < is_pos) {
        return "";
    }

    char c;
    while (t.getPos() < is_pos) {
        is_pos ++;
        is.get(c);
    }

    std::string buf {};
    for (int i = 0; i < t.getLength(); i++) {
        buf += is.get();
        is_pos ++;
    }
    return buf;
}

void generateHTMLHeader(std::ostream& os) {
    os << "<!DOCTYPE html>"                                   << '\n'
       << "<html lang=\"en\">"                                << '\n'
       << "<head>"                                            << '\n'
       << "<meta charset=\"UTF-8\">"                          << '\n'
       << "<title>My Website</title>"                         << '\n'
       // << "<link rel=\"stylesheet\" href=\"./style.css\">" << '\n'
       << "</head>"                                           << '\n'
       << "<body>"                                            << std::endl;
}


void generateHTMLFoot(std::ostream& os) {
    os << "</body>" << '\n'
       << "</html>" << std::endl;
}


void Generator::writeHTMLTitle(int level, std::ostream& os) {
    if (paragraph) {
        os << "</p>" << std::endl;
        paragraph = false;
        paragraph_lf = false;
    }
    heading = true; 
    beg_line = false; 
    heading_level = level; 
    is_pos += level; 
    os << "<h" << level << ">";
}


void Generator::generateHTMLPage(std::istream& is, std::ostream& os) {
    bool returned = false;
    for (auto& t: tokens) {
        switch (t.type) {
            case TokenType::Title1 : 
                writeHTMLTitle(1, os);
                break;

            case TokenType::Title2 : 
                writeHTMLTitle(2, os);
                break;

            case TokenType::Title3 : 
                writeHTMLTitle(3, os);
                break;

            case TokenType::Title4 : 
                writeHTMLTitle(4, os);
                break;

            case TokenType::Title5 : 
                writeHTMLTitle(5, os);
                break;

            case TokenType::Title6 : 
                writeHTMLTitle(6, os);
                break;

            case TokenType::Text:
                if (beg_line) {
                    paragraph = true;
                    beg_line = false;
                    os << "<p>";
                }
                if (paragraph_lf) {
                    paragraph_lf = false;
                    os << "<br>";
                }
                os << t.getText();
                break;

            case TokenType::Italic:
                if (beg_line && !paragraph_lf) {
                    os << "<p>";
                    beg_line = false;
                    paragraph = true;
                }
                if (paragraph_lf) {
                    paragraph_lf = false;
                    os << "<br>";
                }
                if (italic) {
                    italic = false;
                    os << "</em>";
                } else {
                    italic = true;
                    os << "<em>";
                }
                break;


            case TokenType::Bold:
                if (beg_line) {
                    os << "<p>";
                    beg_line = false;
                    paragraph = true;
                }
                if (paragraph_lf) {
                    paragraph_lf = false;
                    os << "<br>";
                }
                if (bold) {
                    bold = false;
                    os << "</strong>";
                } else {
                    bold = true;
                    os << "<strong>";
                }
                break;

            case TokenType::ItalicBold:
                if (beg_line) {
                    os << "<p>";
                    beg_line = false;
                    paragraph = true;
                }
                if (paragraph_lf) {
                    paragraph_lf = false;
                    os << "<br>";
                }
                if (italic_bold) {
                    italic_bold = false;
                    os << "</em></strong>";
                } else {
                    italic_bold = true;
                    os << "<strong><em>";
                }
                break;

            case TokenType::Return:
                if (paragraph) {
                    if (paragraph_lf) {
                        paragraph_lf = false;
                        paragraph = false;
                        os << "</p>" << std::endl;
                    }
                } else if (italic) {
                    italic = false;
                    returned = true;
                    os << "</em>" << std::endl;
                } else if (bold) {
                    bold = false;
                    returned = true;
                    os << "</strong>" << std::endl; 
                } else if (italic_bold) {
                    italic_bold = false;
                    returned = true;
                    os << "</em></strong>" << std::endl;
                } else if (heading) {
                    heading = false;
                    os << "</h" << heading_level << ">";
                    if (!returned) {
                        os << std::endl;
                    }
                } else {
                    os << std::endl;
                }
                is_pos += 1;
                beg_line = true;
                break;
            default: break;
        }
    }
}

void Generator::generateHTML(std::istream& is, std::ostream& os) {
    
    generateHTMLHeader(os);

    generateHTMLPage(is, os);

    generateHTMLFoot(os);

}


void generateHTML(std::vector<Token> tokens, std::istream& is, std::ostream& os) {
    Generator gen {tokens};

    gen.generateHTML(is, os);
}
