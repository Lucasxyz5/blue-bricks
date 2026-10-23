#include <iostream>
#include <sstream>
#include <vector>
#include <string>

const char TAB = '\t';
char look;

class RegisterManager {
    private:
    std::vector<std::string> registers = { "%eax", "%ebx", "%ecx", "%edx", "%r8d", "%r9d"};
    std::vector<bool> regAvailable = std::vector<bool>(registers.size(), true);
    public:
    RegisterManager() {

    }

    std::string allocReg() {
        for (int i = 0; i < registers.size(); i++) {
            if (regAvailable[i] == true) {
                regAvailable[i] = false;
                return registers[i];
            }
        }
        return "error";
    }

    bool freeReg(std::string reg) {
        for (int i = 0; i < registers.size(); i++) {
            if (registers[i] == reg) {
                if (regAvailable[i]) {
                    return false;
                }
                regAvailable[i] = true;
                return true;
            }
        }
        return false;
    }
};


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

void emit(const std::string &s, bool indent = true) {
    if (indent) { std::cout << '\t'; }
    std::cout  << s;
}

void emitLn(const std::string& s, bool indent = true) {
    emit(s, indent);
    std::cout << '\n';
}

void expression() {
    std::ostringstream output;
    output << "movl $" << getNumber() << ", %eax";
    emitLn(output.str());
}

void header() {
    emitLn(".text", false);
    emitLn(".globl _main", false);
    emitLn("_main:", false);
}

void footer() {
    emitLn("ret");
}

void init() {
    getChar();
}

int main() {
    RegisterManager regManager;
    init();
    header();

    expression();

    footer();
}