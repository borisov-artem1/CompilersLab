#include "preprocessing.h"

prep::preprocessing::preprocessing(std::string& baseString)
{
    for (const auto & it : baseString)
    {
        if (!std::isalnum(it) && manageLetters.find(it) == std::string::npos)
        {
            throw std::runtime_error("Invalid letter detected: " + std::to_string(it));
        }
    }
    preprocessing::baseString = baseString;
}

int prep::preprocessing::precedence(const char& manageToken) noexcept
{
    if (manageToken == '|') { return 1; }
    if (manageToken == '.') { return 2; }
    if (manageToken == '*') { return 3; }
    return 0;
}


std::string prep::preprocessing::toPostString(std::string& regexString) noexcept
{
    std::stack<char> tokenStack;
    std::string outputString;
    replacementPlus(regexString);
    //std::cout << regexString << std::endl;
    for (const auto & currentChar : regexString)
    {
        if (std::isalnum(currentChar))
        {
            outputString += currentChar;
        } else if (currentChar == '(')
        {
            tokenStack.push(currentChar);
        } else if (currentChar == ')')
        {
            while (!tokenStack.empty() && tokenStack.top() != '(')
            {
                outputString += tokenStack.top();
                tokenStack.pop();
            }
            tokenStack.pop();
        } else
        {
            while (!tokenStack.empty() && precedence(tokenStack.top()) >= precedence(currentChar))
            {
                outputString += tokenStack.top();
                tokenStack.pop();
            }
            tokenStack.push(currentChar);
        }
    }

    while (!tokenStack.empty())
    {
        outputString += tokenStack.top();
        tokenStack.pop();
    }
    //std::cout << outputString << std::endl;
    return outputString;
}

const std::string& prep::preprocessing::normalizeString()
{
    if (baseString.empty())
    {
        throw std::runtime_error("Invalid regular expression detected: " + baseString);
    }
    preprocessing::finalPostfixString = toPostString(baseString);
    return finalPostfixString;
}

void prep::preprocessing::replacementPlus(std::string& baseString) noexcept
{
    size_t pos = 0;
    while ((pos = baseString.find('+')) != std::string::npos)
    {
        std::string replacement = "." + baseString.substr(pos - 1, pos) + "*";
        baseString.replace(pos, 1, replacement);
        pos += 3;
    }
}


