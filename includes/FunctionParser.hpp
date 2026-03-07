#ifndef FUNCTIONPARSE_HPP
#define FUNCTIONPARSE_HPP
#include "Fraction.hpp"
#include <string>
#include <cstring>

//linked list nodes
struct node
{
    std::string data;
    node* next;
    
    node(): data(), next(nullptr) {}
    node(const std::string d):data(d), next(nullptr) {}
    node(const std::string d, node* n):data(d), next(n) {}
};

//AST nodes
struct ASTnode
{
    std::string data;
    ASTnode* left;
    ASTnode* right;

    ASTnode():data(), left(nullptr), right(nullptr) {}
    ASTnode(const std::string& d):data(d), left(nullptr), right(nullptr) {}
    ASTnode(const std::string& d, ASTnode* l, ASTnode* r)
    :data(d), left(l), right(r) {}
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
        clear();
    }

    //Function building and evaluating AST using shunting yard
    Fraction evaluate(const Fraction& x); 
    void ShuntingYard();
    
    //Functions to print AST and the linked list
    void PrintToken() const;
    void PrintAST() const; 

    node* GetHead() const { return head; }
    node* GetTail() const { return tail; }
    ASTnode* GetRoot() const { return root; }
    char GetVariable() const { return var; }

private:
    void clear();
    void tokenize(const std::string& func);
    void AddToken(const std::string& token);
    Fraction eval(ASTnode* root, const Fraction& x);

private:
    node* head;
    node* tail;
    ASTnode* root;
    char var;
};

#endif
