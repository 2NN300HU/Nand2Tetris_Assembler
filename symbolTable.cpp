#include "symbolTable.h"

bool SymbolTable::contains(const std::string& symbol) {
    auto itr = this->symbolTable.find(symbol);
    if (itr == this->symbolTable.end()) return false;
    return true;
}
