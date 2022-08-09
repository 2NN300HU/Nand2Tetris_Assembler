#include "assembler.h"

std::ifstream Assembler::openFile() {
    std::ifstream stream;
    stream.open(this->fileName + ".asm");
    if (!stream.is_open()) throw std::invalid_argument(this->fileName + ".asm File doesn't exists");
    return stream;
}
void Assembler::firstPass(std::ifstream &file) {
    int lineCounter = 0;
    Parser parser(file);
    while (parser.hasMoreCommands()) {
        parser.advance();
        if (parser.getCommandType() == L_COMMAND) {
            this->symbolTable.addEntry(parser.getSymbol(), lineCounter);
        } else {
            lineCounter++;
        }
    }
}
void Assembler::secondPass(std::ifstream &file) {
    std::ofstream stream;
    stream.open(this->fileName + ".hack", std::ios::out | std::ios::binary);

    if (!stream.is_open()) {
        throw std::runtime_error("Failed to write file");
    }
    int variableCounter = 16;
    Parser parser(file);
    while (parser.hasMoreCommands()) {
        try {
            parser.advance();
            unsigned char binary[2] = {0};
            if (parser.getCommandType() == A_COMMAND) {
                int res;
                auto symbol = parser.getSymbol();
                if (symbol[0] < '0' || symbol[0] > '9') {
                    if (symbolTable.contains(symbol)) {
                        res = symbolTable.getAddress(symbol);
                    } else {
                        symbolTable.addEntry(symbol, variableCounter);
                        res = variableCounter;
                        variableCounter++;
                    }

                } else {
                    int sum = 0;
                    for (int i = 0; i < symbol.length(); i++) {
                        if (symbol[0] < '0' || symbol[0] > '9') {
                            throw std::invalid_argument("Symbol started with number");
                        }
                        sum = sum * 10 + symbol[i] - '0';
                    }
                    res = sum;
                }

                binary[0] = res / 256;
                binary[1] = res % 256;

            } else if (parser.getCommandType() == C_COMMAND) {
                int res = 7;
                auto comp = Code::comp(parser.getComp());
                auto dest = Code::dest(parser.getDest());
                auto jump = Code::jump(parser.getJump());
                for (auto &i : comp) {
                    res = res * 2 + i;
                }
                for (auto &i : dest) {
                    res = res * 2 + i;
                }
                for (auto &i : jump) {
                    res = res * 2 + i;
                }
                binary[0] = res / 256;
                binary[1] = res % 256;
            } else {
                continue;
            }
            stream.write((const char *)binary, sizeof(binary));

        } catch (std::invalid_argument &e) {
            std::string err = ":" + std::to_string(parser.getLine()) + ": error: " + e.what();
            throw std::invalid_argument(err);
        }
    }
}

std::ifstream Assembler::init() {
    auto stream = openFile();
    this->symbolTable.addEntry("SP", 0);
    this->symbolTable.addEntry("LCL", 1);
    this->symbolTable.addEntry("ARG", 2);
    this->symbolTable.addEntry("THIS", 3);
    this->symbolTable.addEntry("THAT", 4);
    this->symbolTable.addEntry("SCREEN", 16384);
    this->symbolTable.addEntry("KBD", 24576);
    for (int i = 0; i < 16; i++) {
        this->symbolTable.addEntry("R" + std::to_string(i), i);
    }
    return stream;
}

std::string Assembler::getFileName(const std::string &fileName) {
    int divider = fileName.length() - 4;
    auto ext = fileName.substr(divider);
    if (ext != ".asm") throw std::invalid_argument("The given file is not .asm file");
    auto res = fileName.substr(0, divider);
    return res;
}

bool Assembler::open(const std::string &fileName) {
    try {
        this->fileName = getFileName(fileName);
    } catch (std::exception &e) {
        std::cout << this->fileName + ".asm" + e.what() << std::endl;
        return false;
    }
    return true;
}

bool Assembler::run() {
    try {
        auto stream = init();
        firstPass(stream);
        stream.clear();
        stream.seekg(0);
        secondPass(stream);
    } catch (std::invalid_argument &e) {
        std::cout << this->fileName + ".asm" + e.what() << std::endl;
        auto temp = this->fileName + ".hack";
        std::remove(temp.c_str());
        return false;
    }
    return true;
}