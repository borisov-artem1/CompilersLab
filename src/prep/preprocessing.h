#pragma once
#include <iostream>
#include <stack>

namespace prep
{
    const std::string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string manageLetters = "().*|+";
    class [[nodiscard]] preprocessing {
        std::string baseString;
        std::string finalPostfixString;
    public:
        explicit preprocessing(std::string& baseString);
        const std::string& normalizeString();
        ~preprocessing() = default;
        static void replacementPlus(std::string& baseString) noexcept;
    private:
        [[nodiscard]] std::string toPostString(std::string& regexString) noexcept;
        [[nodiscard]] int precedence(const char& manageToken) noexcept;
        [[nodiscard]] static bool isValidRegex(const std::string& regex) noexcept;
        [[nodiscard]] static std::string makeConcatenation(const std::string& regex) noexcept;
    };
}



