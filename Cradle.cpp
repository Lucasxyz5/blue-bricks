#include <iostream>
#include <sstream>

const char TAB = '\t';
char look;

void getChar() {
    std::cin.get(look);
}

void error(const std::string &s) {
    std::cout << "\n" << "Error " << s << ".\n";
}

void abortBlue(const std::string &s) {
    error(s);
    std::exit(1);
}

void expected(const std::string &s) {
    abortBlue(s + " Expected");
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

char getNumber() {
    if (!isDigit(look)) {
        expected("number");
    }

    char num = look;
    getChar();

    return num;
}

void emit(const std::string &s) {
    std::cout << '\t' << s;
}

void emitLn(const std::string& s) {
    emit(s);
    std::cout << '\n';
}

void expression() {
    std::ostringstream output;
    output << "MOVE #" << getNumber() << ",D0";
    emitLn(output.str());
}

void init() {
    getChar();
}

int main() {
    init();
    expression();
}