#include <iostream>

const char TAB = '\t';
char look;

void getChar() {
    std::cin.get(look);
}

void error(const std::string &s) {
    std::cout << "\n" << "Error " << s << ".\n";
}

void abort(const std::string &s) {
    error(s);
    std::exit(1);
}

void expected(const std::string &s) {
    abort(s + "Expected");
}

void init() {
    getChar();
}

int main() {
    init();
}