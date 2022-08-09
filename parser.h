#ifndef PARSER_H
#define PARSER_H

#include <cctype>
#include <fstream>
#include <string>
#include <vector>

enum CommandType {
    A_COMMAND,
    C_COMMAND,
    L_COMMAND
};

class Parser {
   private:
    std::ifstream& file;
    CommandType commandType;
    bool hasMoreCommand = true;
    std::string nextLine;
    std::string symbol;
    std::string dest;
    std::string comp;
    std::string jump;
    int lineConuter =0;

    std::string trim(const std::string& command);
    void createA(const std::string& command);
    void createC(const std::string& command);
    void createL(const std::string& command);

   public:
    Parser(std::ifstream& stream) : file(stream) {}
    bool hasMoreCommands();
    void advance();

    CommandType getCommandType() {
        return this->commandType;
    }

    std::string getSymbol() {
        return this->symbol;
    }

    std::string getDest() {
        return this->dest;
    }
    std::string getComp() {
        return this->comp;
    }

    std::string getJump() {
        return this->jump;
    }

    int getLine(){
        return this->lineConuter;
    }
};

#endif