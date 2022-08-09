#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <string>
#include <unordered_map>

class SymbolTable {
   private:
    std::unordered_map<std::string, int> symbolTable;

   public:
    void addEntry(const std::string& symbol, const int address) {
        this->symbolTable.insert(std::make_pair(symbol, address));
    }

    bool contains(const std::string& symbol);

    int getAddress(const std::string& symbol) {
        return this->symbolTable[symbol];
    }
};

#endif