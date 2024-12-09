#pragma once
#include <vector>
#include <string>
#include <stack>

namespace calc
{

    bool isOperator(char c)
    {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    int precedence(char op)
    {
        if (op == '+' || op == '-')
            return 1;
        if (op == '*' || op == '/')
            return 2;
        return 0;
    }

    bool tokenize(const std::string &expr, std::vector<std::string> &tokens)
    {
        size_t i = 0;
        bool lastWasOperator = true; // For detecting negative numbers
        while (i < expr.length())
        {
            if (isspace(expr[i]))
            {
                i++;
            }
            else if (expr[i] == '(' || expr[i] == ')')
            {
                tokens.push_back(std::string(1, expr[i]));
                i++;
                lastWasOperator = (expr[i - 1] != ')');
            }
            else if (isOperator(expr[i]))
            {
                // Handle unary minus for negative numbers
                if (expr[i] == '-' && lastWasOperator)
                {
                    // Negative number
                    size_t j = i + 1;
                    if (j < expr.length() && (isdigit(expr[j]) || expr[j] == '.'))
                    {
                        std::string numStr = "-";
                        while (j < expr.length() && (isdigit(expr[j]) || expr[j] == '.'))
                        {
                            numStr += expr[j];
                            j++;
                        }
                        tokens.push_back(numStr);
                        i = j;
                    }
                    else
                    {
                        tokens.push_back(std::string(1, expr[i]));
                        i++;
                        lastWasOperator = true;
                    }
                }
                else if (i == 0 && expr[i] == '+')
                {
                    // Positive number
                    size_t j = i + 1;
                    if (j < expr.length() && (isdigit(expr[j]) || expr[j] == '.'))
                    {
                        std::string numStr = "";
                        while (j < expr.length() && (isdigit(expr[j]) || expr[j] == '.'))
                        {
                            numStr += expr[j];
                            j++;
                        }
                        tokens.push_back(numStr);
                        i = j;
                    }
                    else
                    {
                        tokens.push_back(std::string(1, expr[i]));
                        i++;
                        lastWasOperator = true;
                    }
                } 
                else
                {
                    tokens.push_back(std::string(1, expr[i]));
                    i++;
                    lastWasOperator = true;
                }
            }
            else if (isdigit(expr[i]) || expr[i] == '.')
            {
                size_t j = i;
                std::string numStr;
                bool hasDot = false;
                while (j < expr.length() && (isdigit(expr[j]) || expr[j] == '.'))
                {
                    if (expr[j] == '.')
                    {
                        if (hasDot)
                        {
                            return false; // More than one dot in number
                        }
                        hasDot = true;
                    }
                    numStr += expr[j];
                    j++;
                }
                // Handle scientific notation
                if (j < expr.length() && (expr[j] == 'e' || expr[j] == 'E'))
                {
                    numStr += expr[j];
                    j++;
                    if (j < expr.length() && (expr[j] == '+' || expr[j] == '-'))
                    {
                        numStr += expr[j];
                        j++;
                    }
                    if (j == expr.length() || !isdigit(expr[j]))
                    {
                        return false; // Invalid scientific notation
                    }
                    while (j < expr.length() && isdigit(expr[j]))
                    {
                        numStr += expr[j];
                        j++;
                    }
                }
                tokens.push_back(numStr);
                i = j;
                lastWasOperator = false;
            }
            else
            {
                // Invalid character
                return false;
            }
        }
        return true;
    }

    // Convert infix expression to postfix notation
    bool toPostfix(const std::vector<std::string> &tokens, std::vector<std::string> &postfix)
    {
        std::stack<std::string> opStack;
        int parentheses = 0;
        std::string prevToken;
        for (const std::string &token : tokens)
        {
            if (token == "(")
            {
                opStack.push(token);
                parentheses++;
            }
            else if (token == ")")
            {
                parentheses--;
                if (parentheses < 0)
                    return false; // Mismatched parentheses
                while (!opStack.empty() && opStack.top() != "(")
                {
                    postfix.push_back(opStack.top());
                    opStack.pop();
                }
                if (opStack.empty())
                    return false; // Mismatched parentheses
                opStack.pop();    // Pop '('
            }
            else if (isOperator(token[0]) && token.length() == 1)
            {
                // Check for consecutive operators
                if (prevToken.empty() || (isOperator(prevToken[0]) && prevToken.length() == 1) || prevToken == "(")
                {
                    return false;
                }
                while (!opStack.empty() && opStack.top() != "(" && precedence(opStack.top()[0]) >= precedence(token[0]))
                {
                    postfix.push_back(opStack.top());
                    opStack.pop();
                }
                opStack.push(token);
            }
            else
            {
                // Operand
                postfix.push_back(token);
            }
            prevToken = token;
        }
        if (isOperator(prevToken[0]) && prevToken.length() == 1)
        {
            return false; // Expression ends with an operator
        }
        while (!opStack.empty())
        {
            if (opStack.top() == "(" || opStack.top() == ")")
            {
                return false; // Mismatched parentheses
            }
            postfix.push_back(opStack.top());
            opStack.pop();
        }
        if (parentheses != 0)
        {
            return false; // Mismatched parentheses
        }
        return true;
    }

    // Evaluate the postfix expression
    bool evaluatePostfix(const std::vector<std::string> &postfix, double &result)
    {
        std::stack<double> valStack;
        for (const std::string &token : postfix)
        {
            if (isOperator(token[0]) && token.length() == 1)
            {
                if (valStack.size() < 2)
                    return false;
                double b = valStack.top();
                valStack.pop();
                double a = valStack.top();
                valStack.pop();
                if (token == "+")
                {
                    valStack.push(a + b);
                }
                else if (token == "-")
                {
                    valStack.push(a - b);
                }
                else if (token == "*")
                {
                    valStack.push(a * b);
                }
                else if (token == "/")
                {
                    if (b == 0)
                        return false; // Division by zero
                    valStack.push(a / b);
                }
            }
            else
            {
                // Operand
                char *end;
                double val = strtod(token.c_str(), &end);
                if (*end != '\0')
                    return false; // Invalid number
                valStack.push(val);
            }
        }
        if (valStack.size() != 1)
            return false;
        result = valStack.top();
        return true;
    }

    bool evaluateExpression(const std::string &expr, double &result) {
        std::vector<std::string> tokens;
        if(!tokenize(expr, tokens)) return false;
        std::vector<std::string> postfix;
        if(!toPostfix(tokens, postfix)) return false;
        if(!evaluatePostfix(postfix, result)) return false;
        return true;
    }
}
