#ifndef CODE_H
#define CODE_H

#include <array>
#include <stdexcept>
#include <string>

class Code {
   public:
    static std::array<bool, 3> dest(const std::string& code);
    static std::array<bool, 7> comp(const std::string& code);
    static std::array<bool, 3> jump(const std::string& code);
};

#endif