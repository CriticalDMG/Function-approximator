#ifndef UTILS_HPP
#define UTILS_HPP
#include <string>
#include <cstring>

class Utils
{
public:
    //checking for brackets
    static bool IsOpenBracket(char c)
    {
        return c == '(' || c == '[' || c == '{';
    }

    static bool IsClosingBraket(char c)
    {
        return (c == ')' || c == ']' || c == '}');
    }

    //checking for letter
    static bool IsLetter(char c)
    {
        return (c >= 'a' && c <= 'z');
    }

    //Checking for an operator
    static bool IsOperator(char c)
    {
        return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '~');
    }

    //The same as the upper just works with strings
    static bool IsOp(const std::string& str)
    {
        return (str == "+" || str == "-" || str == "*" || str == "/" || str == "^");    
    }

    //Checking for a digit 
    static bool IsDigit(char c)
    {
        return ((c - '0' >= 0) && (c - '0' <= 9)); 
    }

    //Checking for special function like log, sin, cos, tg, cotg etc
    static bool IsSpecialFunc(const std::string& str) 
    {
        return str == "sin" ||  str == "cos" 
               || str == "tg" || str == "cotg" 
               || str == "ln" || str == "exp" 
               || str == "sqrt"; 
    }

    static int GetPrecedence(const std::string& str)
    {
        if(str == "+" || str == "-")
        {
            return 1;
        }
        else if(str == "*" || str == "/")
        {
            return 2;
        }
        else if(str == "~") 
        {
            return 3;
        } 
        else if(str == "^")
        {
            return 4;
        }
        else if(IsSpecialFunc(str)) 
        {
            return 5;
        }

        return 0;
    }

    static bool IsRightAssos(const std::string& str)
    {
        return str == "~" || str == "^";    
    }

    //Transforming string to int
    static int TransfromToInt(const std::string& str)
    {
        int num = 0;
        for(size_t i = 0; i < str.length(); ++i)
        {
            int digit = str[i] - '0';
            num = num * 10 + digit; 
        }

        return num;
    }       

    
};

#endif