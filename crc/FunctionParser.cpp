#include "FunctionParser.hpp"
#include "Utils.hpp"

FunctionParser::FunctionParser(): head(nullptr), tail(nullptr), var('x'){}
FunctionParser::FunctionParser(const std::string& s):head(nullptr), tail(nullptr), var('x')
{
    tokenize(s);
}

FunctionParser::FunctionParser(const std::string& s, char variable):head(nullptr), tail(nullptr), var(variable)
{
    tokenize(s);
}

void FunctionParser::tokenize(const std::string& func)
{
    for(size_t i = 0; i < func.length(); ++i)
    {
        if(std::isspace(func[i]))
        {
            continue;
        }
        else if(Utils::IsOpenBracket(func[i])) 
        {
            AddToken(std::string(1, func[i]));
        }
        else if(Utils::IsDigit(func[i]))
        {
            std::string temp = "";
            while(i < func.length() && Utils::IsDigit(func[i]))
            {
                temp += func[i];
                ++i;
            }
            AddToken(temp);
            --i;         
        }
        else if(Utils::IsLetter(func[i]))
        {
            if(func[i] == var)
            {
                AddToken(std::string(1, func[i]));
            }
            else
            {
                std::string temp = "";
                while(i < func.length() && Utils::IsLetter(func[i]))
                {
                    temp += func[i];
                    ++i;
                }
                AddToken(temp);
                --i;   
                if(Utils::IsSpecialFunc(temp)) AddToken(temp);
                else throw std::runtime_error("Invalid special function");
            }
        }
        else if(Utils::IsClosingBraket(func[i]))
        {
            AddToken(std::string(1, func[i]));
        }
        else if(Utils::IsOperator(func[i]))
        {
            if(func[i] == '-')
            {
                if(!tail || tail->data == "(" || Utils::IsOp(tail->data))
                {
                    AddToken(std::string(1, '~'));
                }
                else
                {
                    AddToken(std::string(1, '-'));
                }
            }
            else if(func[i] == '+')
            {
                if(!tail || tail->data == "(" || Utils::IsOp(tail->data))
                {
                    continue;
                }
                else
                {
                    AddToken(std::string(1, '+'));
                }
            }
            else
            {
                AddToken(std::string(1, func[i]));
            }
        }
        else 
        {
            throw std::runtime_error("Invalid operand!");
        }
    }
}

void FunctionParser::AddToken(const std::string& token)
{
    if(!head) 
    {
        try{
            head = new node(token);
            tail = head;
            return;
        }catch(const std::bad_alloc& e){
            std::cout << e.what();
        }
    }

    try{
        node* newNode = new node(token);
        tail->next = newNode;
        tail = tail->next;
    }
    catch(const std::bad_alloc& e){
        std::cout << e.what();
    }
}

Fraction FunctionParser::evaluate(const Fraction& x) 
{
    return Fraction(0);
}

void FunctionParser::ShuntingYard()
{
    return;
}

void FunctionParser::PrintToken() const
{
    node* it = head;
    while(it)
    {
        std::cout << it->data << "";
        it = it->next;
    }
}
