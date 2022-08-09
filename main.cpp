#include <iostream>

#include "assembler.h"

int main(int argc, char **argv) {
    Assembler assembler;
    if (argc == 1) {
        std::cout << "Error: .asm file not given";
    } else if (argc > 2) {
        std::cout << "Error: too many file has given";
    } else {
        if (assembler.open(argv[1])) {
            if (assembler.run()) std::cout << "Success";
        }
    }
}