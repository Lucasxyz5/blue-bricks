#include <iostream>
#include <sstream>
#include <vector>
#include <string>

const char TAB = '\t';
char look;

std::vector<std::string> registers = {
    "%eax", "%ecx", "%edx", "%esi", "%edi",
    "%r8d", "%r9d", "%r10d", "%r11d"
};

std::vector<std::string> registers64 = {
    "%rax", "%rcx", "%rdx", "%rsi", "%rdi",
    "%r8", "%r9", "%r10", "%r11"
};
std::vector<bool> regAvailable = std::vector<bool>(registers.size(), true);

int allocReg() {
    for (int i = 0; i < registers.size(); i++) {
        if (regAvailable[i] == true) {
            regAvailable[i] = false;
            return i;
        }
    }
    return -1;
}

bool freeReg(int reg) {
    if (regAvailable[reg]) {
        return false;
    }
    regAvailable[reg] = true;
    return true;
}

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

std::string getNumber() {
    if (!isDigit(look)) {
        expected("number");
    }

    std::string num = "";

    while(isDigit(look)) {
        num += look;
        getChar();
    }

    if (std::stoi(num) > 2147483647) {
        abortBlue("Integers cannot be greater than 32 bits");
    }

    return num;
}

char getOperand() {
    if (look != '+' && look != '-') {
        expected("Operand");
    }

    char opr = look;
    getChar();

    return opr;
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

void operation(char operand, int regIa, int regIb) {
    std::ostringstream output;

    if (operand == '+') {
        output << "addl " << registers[regIb] << ", " << registers[regIa];
    }
    else if (operand == '-') {
        output << "subl " << registers[regIa] << ", " << registers[regIb];
        emitLn(output.str());
        output.str("");
        output << "movl " << registers[regIb] << ", " << registers[regIa];
    }

    emitLn(output.str());
}

bool expression(int regI) {
    if (isDigit(look)) {
        std::ostringstream output;
        std::string reg = registers[regI];
        output << "movl $" << getNumber() << ", " << reg;
        emitLn(output.str());
        return true;
    }
    else if (look == '(') {
        getChar();
        char opr = getOperand();
        skipWhitespace();
        if (!expression(regI)) {
            return false;
        }
        emitLn("pushq " + registers64[regI]);

        skipWhitespace();
        if (!expression(regI)) {
            return false;
        }
        int stackRegI = allocReg();
        emitLn("popq " + registers64[stackRegI]);

        operation(opr, regI, stackRegI);
        freeReg(stackRegI);

        skipWhitespace();
        if (look != ')') {
            expected(")");
        }

        getChar();
        
        return true;
    }
    else {
        expected("expression");
        return false;
    }
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
    init();
    header();

    int exprRegI = allocReg();
    expression(exprRegI);

    footer();
}