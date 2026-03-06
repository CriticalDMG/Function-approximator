#ifndef FUNCTIONPARSE_HPP
#define FUNCTIONPARSE_HPP
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
    FunctionParser(const std::string& s);
    FunctionParser(const std::string& s, char variable);
    ~FunctionParser()
    {
        node* it = head;
        while(it != tail)
        {
            node* ToDel = it;
            it = it->next;
            delete ToDel;
        }

        delete tail;
        head = nullptr;
        tail = nullptr;
    }

    node* GetHead() const { return head; }
    node* GetTail() const { return tail; }
private:
    node* head;
    node* tail;
    char var;
};
#endif
