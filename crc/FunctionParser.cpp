#include "FunctionParser.hpp"
#include "Utils.hpp"
#include <stack>
#include <queue>

FunctionParser::FunctionParser(): head(nullptr), tail(nullptr), root(nullptr), var('x'){}
FunctionParser::FunctionParser(const std::string& s)
:head(nullptr), tail(nullptr), root(nullptr), var('x')
{
    try{
        tokenize(s);
    }catch(...){
        clear();
    }
}

FunctionParser::FunctionParser(const std::string& s, char variable)
:head(nullptr), tail(nullptr), root(nullptr), var(variable)
{
    try{
        tokenize(s);
    }catch(...){
        clear();
    }
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
        else if(Utils::IsClosingBracket(func[i]))
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
    return eval(root, x);   
}

Fraction FunctionParser::eval(ASTnode* root, const Fraction& x)
{
    if (!root) throw std::runtime_error("Null node in AST!");
    if(!root->left && !root->right)
    {
        if(Utils::IsDigit(root->data[0]))
        {
            Fraction val = Utils::TransfromToInt(root->data);
            return val;
        }
        else if(root->data[0] == var)
        {
            return x;
        }
        throw std::runtime_error("Unknown leaf node: " + root->data);
    }

    if(root->data[0] == '~')
    {
        Fraction RightVal = eval(root->right, x);
        return RightVal * Fraction(-1);
    }
    else if(Utils::IsSpecialFunc(root->data))
    {
        Fraction RightVal = eval(root->right, x);
        if(root->data == "sin")
        {
            return Utils::sin(RightVal);
        }
        else if(root->data == "cos")
        {
            return Utils::cos(RightVal);
        }
        else if(root->data == "tg")
        {
            return Utils::tg(RightVal);
        }
        else if(root->data == "cotg")
        {
            return Utils::cotg(RightVal);
        }
        else if(root->data == "ln")
        {
            return Utils::ln(RightVal);
        }
        else if(root->data == "exp")
        {
            return Utils::exp(RightVal);
        }
        else 
        {
            throw std::runtime_error("Unknown special function!");
        }
    }

    Fraction LeftVal = eval(root->left, x);
    Fraction RightVal = eval(root->right, x);

    if(root->data == "-") return LeftVal - RightVal;
    if(root->data == "+") return LeftVal + RightVal;
    if(root->data == "*") return LeftVal * RightVal;
    if(root->data == "/") return LeftVal / RightVal;
    if(root->data == "^")
    {
        // LeftVal is the base (e.g., 3), RightVal is the exponent (e.g., 10/3)
        type n = RightVal.GetNumerator() / RightVal.GetDenom();
        Fraction part = RightVal - Fraction(n);

        Fraction pow(1);
        type absN = std::abs(n);
        for(type i = 0; i < absN; ++i)
        {
            pow = pow * LeftVal;
        }
        if(n < 0) pow = Fraction(1) / pow; 

        // 2. Calculate the Fractional Power (Using Taylor Series)
        // Only if there is actually a fractional part left
        Fraction fracPower(1);
        if (part != Fraction(0)) 
        {
            // x^f = exp(f * ln(x))
            Fraction lnBase = Utils::ln(LeftVal);
            fracPower = Utils::exp(part * lnBase);
        }

        return pow * fracPower;
    }

    throw std::runtime_error("Unknown operator!");
}

void FunctionParser::ShuntingYard()
{
    if(!head) return;
    std::stack<ASTnode*> operands;
    std::stack<std::string> operators;

    //lambda function to buld the nodes so that the code isnt rewritten 5 seperate times
    auto BuildNode = [&]{
        if(operators.empty()) throw std::runtime_error("operator stack shouldnt be empty!");
        std::string oper = operators.top();
        operators.pop();
        
        ASTnode* node = nullptr;
        try{
            node = new ASTnode(oper);
        }catch(std::bad_alloc& b){
            std::cout << b.what();
        }

        if(oper == "~" || Utils::IsSpecialFunc(oper))
        {
            if(operands.empty()) throw std::runtime_error("operands stack shouldnt be empty!");

            node->right = operands.top();
            operands.pop();
        }
        else
        {
            if(operands.empty()) throw std::runtime_error("operands stack shouldnt be empty!");
            node->right = operands.top();
            operands.pop();

            if(operands.empty()) throw std::runtime_error("operands stack shouldnt be empty!");
            node->left = operands.top();
            operands.pop();
        }

        operands.push(node);
    };

    node* it = head;
    while(it)
    {
        std::string token = it->data;
        it = it->next;
        if(Utils::IsDigit(token[0]) || (token.length() == 1 && token[0] == var))
        {
            try
            {
                operands.push(new ASTnode(token));

            }
            catch(const std::bad_alloc& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        else if(token.length() == 1 && Utils::IsOpenBracket(token[0]))
        {
            operators.push(token);
        }
        else if(Utils::IsSpecialFunc(token))
        {
            operators.push(token);
        }
        else if(token.length() == 1 && Utils::IsClosingBracket(token[0]))
        {
            while(!operators.empty() && !Utils::IsOpenBracket(operators.top()[0]))
            {
                BuildNode();
            }

            if(!operators.empty() && Utils::IsOpenBracket(operators.top()[0]))
            {
                operators.pop();
            }

            if(!operators.empty() && Utils::IsSpecialFunc(operators.top()))
            {
                BuildNode();
            }
        }
        else if(Utils::IsOperator(token[0]))
        {
            while(!operators.empty() && !Utils::IsOpenBracket(operators.top()[0]))
            {
                std::string top = operators.top();

                int FirstPrec = Utils::GetPrecedence(token);
                int SecPrec = Utils::GetPrecedence(top);
                if(SecPrec > FirstPrec || (FirstPrec == SecPrec && !Utils::IsRightAssos(token)))
                {
                    BuildNode();
                }
                else
                {
                    break;
                }
            }
            operators.push(token);
        }
    }

    while(!operators.empty())
    {
        if(Utils::IsOpenBracket(operators.top()[0]))
        {
            throw std::runtime_error("Invalid operand!");
        }
        BuildNode();
    }

    if(!operands.empty())
    {
        root = operands.top();
        operands.pop();
    }
}

void FunctionParser::PrintToken() const
{
    node* it = head;
    while(it)
    {
        std::cout << it->data << "";
        it = it->next;
    }
    std::cout << "\n";
}


void FunctionParser::PrintAST() const
{
    if(!root) return;
    std::queue<ASTnode*> q;
    q.push(root);
    while(!q.empty())
    {
        int size = q.size();

        for(int i = 0; i < size; ++i)
        {
            ASTnode* node = q.front();
            q.pop();
            std::cout << node->data << " ";

            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
        std::cout << "\n";
    }
} 

void FunctionParser::clear()
{
    if(!head) return;
    node* it = head;
    while(it->next)
    {
        node* toDel = it;
        it = it->next;
        delete toDel;
    }

    delete tail;
    head = nullptr;
    tail = nullptr;
}


