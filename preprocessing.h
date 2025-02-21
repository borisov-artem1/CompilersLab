#pragma once
#include <iostream>
#include <stack>

namespace prep
{
    const std::string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string manageLetters = "().*|+[]";
    class [[nodiscard]] preprocessing {
        std::string baseString;
        std::string finalPostfixString;
    public:
        explicit preprocessing(std::string& baseString);
        const std::string& normalizeString();
        ~preprocessing() = default;
    private:
        [[nodiscard]] std::string toPostString(const std::string& regexString) noexcept;
        [[nodiscard]] int precedence(const char& manageToken) noexcept;
    };
}



