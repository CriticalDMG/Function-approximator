#ifndef FUNCTIONPARSE_HPP
#define FUNCTIONPARSE_HPP
#include "Fraction.hpp"
#include <string>
#include <cstring>

//linked list
struct node
{
    std::string data;
    node* next;
    
    node(): data(), next(nullptr) {}
    node(const std::string d):data(d), next(nullptr) {}
    node(const std::string d, node* n):data(d), next(n) {}
};

//this class will parse the function from the input
class FunctionParser
{
public:
    FunctionParser();
    FunctionParser(const std::string& s); //the variable will be defaultly set as x
    FunctionParser(const std::string& s, char variable); //->here the user can choose, but it doesnt really matter honestly 
    ~FunctionParser()
    {
        node* it = head;
        while(it->next)
        {
            node* ToDel = it;
            it = it->next;
            delete ToDel;
        }

        delete tail;
        head = nullptr;
        tail = nullptr;
    }

    Fraction evaluate(const Fraction& x); 
    
    void PrintToken() const;

    node* GetHead() const { return head; }
    node* GetTail() const { return tail; }
    char GetVariable() const { return var; }
    
private:
    void ShuntingYard();
    void tokenize(const std::string& func);
    void AddToken(const std::string& token);

private:
    node* head;
    node* tail;
    char var;
};

#endif
