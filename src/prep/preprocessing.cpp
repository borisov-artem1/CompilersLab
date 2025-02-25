#include "preprocessing.h"

prep::preprocessing::preprocessing(std::string& baseString)
{
    for (const auto & it : baseString)
    {
        if (!isValidRegex(baseString))
        {
            throw std::runtime_error("Invalid regex detected in prep constructor: " + std::to_string(it));
        }
    }

    preprocessing::baseString = makeConcatenation(baseString);
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
        throw std::runtime_error("In function normalizedString. Invalid regular expression detected: " + baseString);
    }
    preprocessing::finalPostfixString = toPostString(baseString);
    return finalPostfixString;
}

void prep::preprocessing::replacementPlus(std::string& baseString) noexcept
{
    size_t pos = 0;

    while ((pos = baseString.find('+')) != std::string::npos)
    {
        std::string replacement;
        std::string blockOfElem = baseString.substr(pos - 1, 1);
        int n = 0;
        if (baseString[pos - 1] == ')') // для нулевого элемента исправить
        {
            int balance = 0;
            blockOfElem = "";
            for (auto it = baseString.begin(); it != baseString.begin() + pos; ++it)
            {
                if (*it == '(')
                {
                    --balance;
                } else if (*it == ')')
                {
                    ++balance;
                }
                blockOfElem += *it;
                ++n;
                if (balance == 0)
                {
                    break;
                }
            }

        } else { n = 1; }

        replacement = "." + blockOfElem + "*";
        baseString.replace(pos, 1, replacement);
        pos += n + 2;
        //std::cout << baseString << std::endl;
    }
}

bool prep::preprocessing::isValidRegex(const std::string& regex) noexcept
{
    std::stack<char> bracketStack;
    bool lastWasOperator = true;
    bool lastWasOpenBracket = false;
    int operandCount = 0;

    for (size_t i = 0; i < regex.size(); ++i) {
        char c = regex[i];

        if (std::isalnum(c)) {
            lastWasOperator = false;
            lastWasOpenBracket = false;
            operandCount++;
        }
        else if (c == '(') {
            bracketStack.push(c);
            lastWasOperator = true;
            lastWasOpenBracket = true;
        }
        else if (c == ')') {
            if (bracketStack.empty() || lastWasOperator) return false;
            bracketStack.pop();
            lastWasOperator = false;
        }
        else if (c == '*' || c == '+') {
            if (lastWasOperator || lastWasOpenBracket) return false;
            lastWasOperator = false;
        }
        else if (c == '.' || c == '|') {
            if (lastWasOperator || i == regex.size() - 1) return false;
            lastWasOperator = true;
        }
        else {
            return false;
        }
    }

    return bracketStack.empty() && !lastWasOperator && operandCount > 0;
}

std::string prep::preprocessing::makeConcatenation(const std::string& regex) noexcept
{
    std::string normalized;

    for (size_t i = 0; i < regex.length(); ++i) {
        const char current = regex[i];
        normalized += current;

        if (i + 1 < regex.length()) {
            char next = regex[i + 1];

            if ((isalnum(current) || current == ')' || current == '*' || current == '+') &&
                (isalnum(next) || next == '(')) {
                normalized += '.';
                }
        }
    }

    return normalized;
}



