/**
 * @brief Generate HTML page from markdown file
 */

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

void generateHeader(std::string title) {
    std::cout << "<!DOCTYPE html>" << '\n'
              << "<html lang=\"en\">" << '\n'
              << "<head>" << '\n'
              << "<meta charset=\"UTF-8\">" << '\n'
              << "<title>" << title << "</title>" << '\n'
              // << "<link rel=\"stylesheet\" href=\"./style.css\">" << '\n'
              << "</head>" << '\n'
              << "<body>" << std::endl;
}


void generateFoot() {
    std::cout << "</body>" << '\n'
              << "</html>" << std::endl;
}


void parseItalicBold(std::istream& is) {
    char c;
    std::cout << "<b><i>";
    while (!is.eof()) {
        c = is.get();
        if (c == '*') {
            is.get();
            is.get();
            break;
        } else if (c == '\n') {
            throw std::invalid_argument("Unexpected line break");   
        } else {
            std::cout << c;
        }
    }
    std::cout << "</i></b>" << std::flush;
}


void parseBold(std::istream& is) {
    char c;
    if (!is.eof()) {
        c = is.get();
        if (c == '*') {
            parseItalicBold(is);
        } else {
            is.putback(c);
            std::cout << "<b>";
            while (!is.eof()) {
                c = is.get();
                if (c == '*') {
                    is.get();
                    break;
                } else if (c == '\n') {
                    throw std::invalid_argument("Unexpected line break");   
                } else {
                    std::cout << c;
                }
            }
            std::cout << "</b>" << std::flush;
        }
    }
}


void parseItalic(std::istream& is) {
    char c;
    if (!is.eof()) {
        c = is.get();
        if (c == '*') {
            parseBold(is);
        } else {
            is.putback(c);
            std::cout << "<i>";
            while (!is.eof()) {
                c = is.get();
                if (c == '*') {
                    break;
                } else if (c == '\n') {
                    throw std::invalid_argument("Unexpected line break");   
                } else {
                    std::cout << c;
                }
            }
            std::cout << "</i>" << std::flush;
        }
    } 
}


void parseText(std::istream& is) {
    char c;
    while (!is.eof()) {
        c = is.get();
        if (c == '*') {
            parseItalic(is);
        } else if (c == '\n') {
            break;
        } else {
            std::cout << c;
        }
    }
}


void parseTitle(std::istream& is, int level) {
    char c = is.get();
    if (c) {
        if (c == '#' && level <= 6) {
            parseTitle(is, level + 1);
        } else {
            std::cout << "<h" << level << ">";
            parseText(is);
            std::cout << "</h" << level << ">" << std::endl;
        }
    } else {
        throw std::invalid_argument("Empty title provided");
    }
}


void parseParagraph(std::istream& is) {
    std::cout << "<p>" << '\n';
    parseText(is);
    std::cout << '\n' << "</p>" << std::endl;
}


void parseMarkDown(std::istream& is) {
    char c;
    while (!is.eof()) {
        c = is.get();
        if (c == '#') {
            parseTitle(is, 1);
        } else if (c != '\n') {
            is.putback(c);
            parseParagraph(is);
        }
        is >> std::ws;
    }
}


void generateHTML(std::istream& is) {
    generateHeader("page");
    parseMarkDown(is);
    generateFoot();
}



int main (int argc, char *argv[]) {
    
    if (argc < 2) {
        std::cout << "Usage \"mdhtml page.md\"" << std::endl;
        return -1;
    }

    // open file
    std::ifstream file {argv[1]};

    if (file.is_open()) {
        generateHTML(file);
    }

    return 0;
}
