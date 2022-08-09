#include "parser.h"

std::string Parser::trim(const std::string& command) {
    std::string buffer;
    char current;
    for (int i = 0; i < command.length(); i++) {
        current = command[i];
        if (isspace(current)) continue;
        if (current == '/') break;
        buffer.push_back(current);
    }
    return buffer;
}

void Parser::createA(const std::string& command) {
    this->commandType = A_COMMAND;
    auto& current = this->nextLine;
    for (int i = 1; i < current.length(); i++) {
        this->symbol.push_back(current[i]);
    }
}

void Parser::createC(const std::string& command) {
    this->commandType = C_COMMAND;
    auto& current = this->nextLine;
    int equal = current.find('=');
    int semicolon = current.find(';');
    if (equal != std::string::npos) {
        for (int i = 0; i < equal; i++) {
            this->dest.push_back(current[i]);
        }
    } else {
        equal = -1;
    }

    if (semicolon != std::string::npos) {
        for (int i = semicolon + 1; i < current.length(); i++) {
            this->jump.push_back(current[i]);
        }
    } else {
        semicolon = current.length();
    }

    for (int i = equal + 1; i < semicolon; i++) {
        this->comp.push_back(current[i]);
    }
}

void Parser::createL(const std::string& command) {
    this->commandType = L_COMMAND;
    auto& current = this->nextLine;
    for (int i = 1; i < current.length() - 1; i++) {
        this->symbol.push_back(current[i]);
    }
}

bool Parser::hasMoreCommands() {
    bool hasMoreCommand = false;
    std::string buffer;
    while (!this->file.eof()) {
        std::getline(this->file, buffer);
        this->lineConuter++;
        std::string trimmed(trim(buffer));
        if (!trimmed.empty()) {
            hasMoreCommand = true;
            this->nextLine = trimmed;
            break;
        }
    }
    return hasMoreCommand;
}

void Parser::advance() {
    auto& current = this->nextLine;
    this->symbol.clear();
    this->dest.clear();
    this->comp.clear();
    this->jump.clear();
    
    const char firstWord = current[0];
    if (firstWord == '@') {
        createA(current);
    } else if (firstWord == '(') {
        createL(current);
    } else {
        createC(current);
    }
}
