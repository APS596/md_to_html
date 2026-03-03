/**
 * @brief Generate HTML page from markdown file
 */

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

void generateHeader(std::string title, std::ostream& os) {
    os << "<!DOCTYPE html>" << '\n'
              << "<html lang=\"en\">" << '\n'
              << "<head>" << '\n'
              << "<meta charset=\"UTF-8\">" << '\n'
              << "<title>" << title << "</title>" << '\n'
              // << "<link rel=\"stylesheet\" href=\"./style.css\">" << '\n'
              << "</head>" << '\n'
              << "<body>" << std::endl;
}


void generateFoot(std::ostream& os) {
    os << "</body>" << '\n'
              << "</html>" << std::endl;
}


void parseItalicBold(std::istream& is, std::ostream& os) {
    char c;
    os << "<b><i>";
    while (!is.eof()) {
        c = is.get();
        if (c == '*') {
            is.get();
            is.get();
            break;
        } else if (c == '\n') {
            throw std::invalid_argument("Unexpected line break");   
        } else {
            os << c;
        }
    }
    os << "</i></b>" << std::flush;
}


void parseBold(std::istream& is, std::ostream& os) {
    char c;
    if (!is.eof()) {
        c = is.get();
        if (c == '*') {
            parseItalicBold(is, os);
        } else {
            is.putback(c);
            os << "<b>";
            while (!is.eof()) {
                c = is.get();
                if (c == '*') {
                    is.get();
                    break;
                } else if (c == '\n') {
                    throw std::invalid_argument("Unexpected line break");   
                } else {
                    os << c;
                }
            }
            os << "</b>" << std::flush;
        }
    }
}


void parseItalic(std::istream& is, std::ostream& os) {
    char c;
    if (!is.eof()) {
        c = is.get();
        if (c == '*') {
            parseBold(is, os);
        } else {
            is.putback(c);
            os << "<i>";
            while (!is.eof()) {
                c = is.get();
                if (c == '*') {
                    break;
                } else if (c == '\n') {
                    throw std::invalid_argument("Unexpected line break");   
                } else {
                    os << c;
                }
            }
            os << "</i>" << std::flush;
        }
    } 
}


void parseText(std::istream& is, std::ostream& os) {
    char c;
    while (!is.eof()) {
        c = is.get();
        if (c == '*') {
            parseItalic(is, os);
        } else if (c == '\n') {
            break;
        } else {
            os << c;
        }
    }
}


void parseTitle(std::istream& is, std::ostream& os, int level) {
    char c = is.get();
    if (c) {
        if (c == '#' && level <= 6) {
            parseTitle(is, os, level + 1);
        } else {
            os << "<h" << level << ">";
            parseText(is, os);
            os << "</h" << level << ">" << std::endl;
        }
    } else {
        throw std::invalid_argument("Empty title provided");
    }
}


void parseParagraph(std::istream& is, std::ostream& os) {
    os << "<p>" << '\n';
    parseText(is, os);
    os << '\n' << "</p>" << std::endl;
}


void parseMarkDown(std::istream& is, std::ostream& os) {
    char c;
    while (!is.eof()) {
        c = is.get();
        if (c == '#') {
            parseTitle(is, os, 1);
        } else if (c != '\n') {
            is.putback(c);
            parseParagraph(is, os);
        }
        is >> std::ws;
    }
}


void generateHTML(std::istream& is, std::ostream& os) {
    generateHeader("page", os);
    parseMarkDown(is, os);
    generateFoot(os);
}



int main (int argc, char *argv[]) {
    
    if (argc < 2) {
        std::cout << "Usage \"mdhtml page.md\"" << std::endl;
        return -1;
    }

    // open file
    std::ifstream file {argv[1]};

    if (file.is_open()) {
        generateHTML(file, std::cout);
    }

    return 0;
}
