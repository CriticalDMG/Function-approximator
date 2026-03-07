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

    static bool IsClosingBracket(char c)
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
    static Fraction TransfromToInt(const std::string& str)
    {
        Fraction num(0);
        for(size_t i = 0; i < str.length(); ++i)
        {
            type digit = str[i] - '0';
            num = num * 10 + digit; 
        }

        return num;
    }       

    //Approximating sin(x) using taylor series
    static Fraction sin(const Fraction& val)
    {
        Fraction sum(val);
        Fraction term(val);
        Fraction Minusx2(val*val*Fraction(-1));

        for(int i = 1; i <= 8; ++i)
        {
            term = term * Minusx2;

            type div = (2 * i) * (2 * i + 1);
            term = term / Fraction(div);

            sum += term;
        }
        return sum;
    }

    //Approximating cos(x) using taylor series
    static Fraction cos(const Fraction& val)
    {
        Fraction sum(val);
        Fraction term(val);
        Fraction Minusx2(val*val*Fraction(-1));

        for(int i = 1; i <= 8; ++i)
        {
            term = term * Minusx2;
            int div = (2 * i - 1) * (2 * i);

            term = term / Fraction(div);

            sum += term;
        }

        return sum;
    }

    //Approximating tg(x) using taylor series for sin and cos
    static Fraction tg(const Fraction& val)
    {
        return Fraction(sin(val)/cos(val));
    }

    //Approximating cotg(x) using taylor series for cos and sin
    static Fraction cotg(const Fraction& val)
    {
        return Fraction(cos(val))/sin(val);
    }

    //Approximating exp(x) using taylor series for e^x
    static Fraction exp(const Fraction& val)
    {

        if (val.GetNumerator() < 0) 
        {
            Fraction PositiveVal = val * Fraction(-1);
            return Fraction(1) / exp(PositiveVal);
        }

        Fraction sum(1);
        Fraction term(1);

        for(int i = 1; i <= 8; ++i)
        {
            term = term * val;
            term = term / Fraction(i);

            sum = sum + term;

            if(term == Fraction(0)) break;
        }

        return sum;
    }


    //Approximating ln(x) using taylro series for ln(1 - x) and ln(1 + x)
    static Fraction ln(const Fraction& val)
    {
        if(val.GetNumerator() <= 0)
        {
            throw std::runtime_error("cannot take ln(0) and nums < 0!");
        }

        Fraction t = (val + (-1)) / (val + 1);  // t = (x-1)/(x+1)
        Fraction TSqr = t * t;                  // Calculate t^2 once

        Fraction numer = t;                     // Starts as t
        Fraction sum = t;                       // Starts as t

        for(int i = 1; i <= 8; ++i)             
        {
            numer = numer * TSqr;               // This makes it t^3, t^5, etc.
            int OddDiv = 2 * i + 1;             // 3, 5, 7 etc

            Fraction curr = numer / Fraction(OddDiv);
            if(curr.GetNumerator() == 0) break;
            sum += curr;
        }

        return sum * Fraction(2);
    }
};

#endif