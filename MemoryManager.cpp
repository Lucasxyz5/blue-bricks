#include <iostream>
#include <sstream>
#include <vector>
#include <string>

const int DIV_REMAIN_INDEX = 2;
const int RETURN_VALUE = 0;

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