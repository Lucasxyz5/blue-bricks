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

void skipWhitespace() {
    while (look == ' ') {
        getChar();
    }
}

void emit(const std::string &s, bool indent = true) {
    if (indent) { std::cout << '\t'; }
    std::cout  << s;
}

void emitLn(const std::string& s, bool indent = true) {
    emit(s, indent);
    std::cout << '\n';
}

void printLn(std::string s, bool indent = true) {
    std::ostringstream output;
    output << s;
    emitLn(output.str(), indent);
}

void header() {
    emitLn(".text", false);
    emitLn(".globl _main", false);
    emitLn("_main:", false);
}

void footer() {
    emitLn("ret");
}