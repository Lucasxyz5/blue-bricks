#include <iostream>
#include <sstream>
#include <vector>
#include <string>

const char TAB = '\t';
char look;

void getChar() {
    if (!std::cin.get(look)) {
        look = '\0';
    }
}

void error(const std::string &s) {
    std::cout << "\n" << "error " << s << ".\n";
}

void abortBlue(const std::string &s) {
    error(s);
    std::exit(1);
}

void expected(const std::string &s) {
    abortBlue(s + " expected, got " + look);
}

void match(char x) {
    if (look == x) {
        getChar();
    }
    else {
        expected(std::string(1, x));
    }
}

bool isAlphaBlue(char x) {
    return ((x >= 'a' && x <= 'z') ||
            (x >= 'A' && x <= 'Z'));
}

bool isDigit(char x) {
    return (x >= '0' && x <= '9');
}

char getName() {
    if (!isAlphaBlue(look)) {
        expected("name");
    }

    char name = look;
    getChar();

    return name;
}