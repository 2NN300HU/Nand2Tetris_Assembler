#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "code.h"
#include "parser.h"
#include "symbolTable.h"

class Assembler {
   private:
    SymbolTable symbolTable;
    std::string fileName;
    std::ifstream openFile();
    void firstPass(std::ifstream &file);
    void secondPass(std::ifstream &file);
    std::ifstream init();
    std::string getFileName(const std::string &fileName);

   public:
    bool open(const std::string &fileName);
    bool run();
};

#endif