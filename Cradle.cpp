#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "MemoryManager.cpp"
#include "Essentials.cpp"

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
    regAvailable[DIV_REMAIN_INDEX] = false;
    regAvailable[RETURN_VALUE] = false;
}

int main() {
    init();
    header();

    expression(RETURN_VALUE);

    footer();
}