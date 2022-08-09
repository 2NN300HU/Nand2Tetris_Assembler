#include "code.h"

std::array<bool, 3> Code::dest(const std::string& code) {
    std::array<bool, 3> res = {0};
    for (int i = 0; i < code.length(); i++) {
        switch (code[i]) {
            case 'A':
                res[0] = true;
                break;
            case 'D':
                res[1] = true;
                break;
            case 'M':
                res[2] = true;
                break;
            default:
                throw std::invalid_argument("Invalid dest field");
                break;
        }
    }
    return res;
}

std::array<bool, 7> Code::comp(const std::string& code) {
    std::string bin;
    if (code == "0")
        bin = "0101010";
    else if (code == "1")
        bin = "0111111";
    else if (code == "-1")
        bin = "0111010";

    else if (code == "D")
        bin = "0001100";
    else if (code == "A")
        bin = "0110000";
    else if (code == "M")
        bin = "1110000";

    else if (code == "!D")
        bin = "0001101";
    else if (code == "!A")
        bin = "0110001";
    else if (code == "!M")
        bin = "1110001";

    else if (code == "-D")
        bin = "0001111";
    else if (code == "-A")
        bin = "0110011";
    else if (code == "-M")
        bin = "1110011";

    else if (code == "D+1" || code == "1+D")
        bin = "0011111";
    else if (code == "A+1" || code == "1+A")
        bin = "0110111";
    else if (code == "M+1" || code == "1+M")
        bin = "1110111";

    else if (code == "D-1")
        bin = "0001110";
    else if (code == "A-1")
        bin = "0110010";
    else if (code == "M-1")
        bin = "1110010";

    else if (code == "D+A" || code == "A+D")
        bin = "0000010";
    else if (code == "D+M" || code == "M+D")
        bin = "1000010";

    else if (code == "D-A")
        bin = "0010011";
    else if (code == "D-M")
        bin = "1010011";

    else if (code == "A-D")
        bin = "0000111";
    else if (code == "M-D")
        bin = "1000111";

    else if (code == "A&D" || code == "D&A")
        bin = "0000000";
    else if (code == "M&D" || code == "D&M")
        bin = "1000000";

    else if (code == "A|D" || code == "D|A")
        bin = "0010101";
    else if (code == "M|D" || code == "D|M")
        bin = "1010101";
    else
        throw std::invalid_argument("Invalid comp field");
    std::array<bool, 7> res;
    for (int i = 0; i < 7; i++) {
        res[i] = bin[i] - '0';
    }
    return res;
}

std::array<bool, 3> Code::jump(const std::string& code) {
    std::array<bool, 3> res = {0};
    int dec;
    if (code.empty())
        dec = 0;
    else if (code == "JGT")
        dec = 1;
    else if (code == "JEQ")
        dec = 2;
    else if (code == "JGE")
        dec = 3;
    else if (code == "JLT")
        dec = 4;
    else if (code == "JNE")
        dec = 5;
    else if (code == "JLE")
        dec = 6;
    else if (code == "JMP")
        dec = 7;
    else
        throw std::invalid_argument("Invalid jump field");
    for (int i = 0; i < 3; i++) {
        res[2 - i] = dec % 2;
        dec /= 2;
    }
    return res;
}