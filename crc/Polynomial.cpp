#include "Polynomial.hpp"

Polynom::Polynom(const Polynom& oth):coef(oth.coef) {}

Polynom& Polynom::operator=(const Polynom& oth)
{
    if(this != &oth)
    {
        this->coef = oth.coef;
    }
    return *this;
}

Polynom& Polynom::operator+=(const Polynom& oth)
{ 
    size_t pow = (this->degree() > oth.degree()) ? 
               this->coef.size() : oth.coef.size();
    coef.resize(pow);

    for(size_t i = 0; i < degree() + 1; ++i)
    {
        coef[i] = coef[i] + oth[i];    
    }
    trim();
    return *this;
}

Polynom& Polynom::operator-=(const Polynom& oth)
{  
    (*this) *= -1;
    (*this) += oth;
    (*this) *= -1;

    return *this;
}

Polynom& Polynom::operator*=(const Polynom& oth)
{
    if(coef.empty() || oth.coef.empty())
    {
        coef = { Fraction(0) };
        return *this;
    }
    size_t deg = degree() + oth.degree() - 1;
    std::vector<Fraction> res(deg + 1, Fraction());

    for(size_t i = 0; i < degree() + 1; ++i)
    {
        for(size_t j = 0; j < oth.degree() + 1; ++j)
        {
            res[i + j] = res[i + j] + coef[i] * oth[j];
        }
    }   
    
    coef = std::move(res);
    trim();
    return *this;
}

Polynom& Polynom::operator*=(int oth)
{
    for(size_t i = 0; i < coef.size(); ++i)
    {
        coef[i] *= oth;
    }

    return *this;
}

void Polynom::differentiate()
{
    for(int i = (int)degree(); i > 0; --i)
    {
        coef[i] = coef[i] * i;
    }

    trim();
}

void Polynom::integrate(Fraction constant)
{
    std::vector<Fraction> res(coef.size(), Fraction(0));
    res.push_back(Fraction(constant));
    for(size_t i = 0; i < coef.size(); ++i)
    {
        Fraction temp (1, i + 1);
        res[i + 1] = coef[i] * temp;
    }

    coef = res;
}

void Polynom::trim()
{
    int i = degree();
    while(i > 0 && coef[i] == Fraction(0))
    {
        --i;
    }

    coef.resize(i + 1);
}


Polynom operator+(Polynom& obj, const Polynom& oth)
{
    Polynom temp(obj);
    temp += oth;
    return temp;
}

Polynom operator-(Polynom& obj, const Polynom& oth)
{
    Polynom temp(obj);
    temp -= oth;
    return temp;
}

Polynom operator*(Polynom& obj, const Polynom& oth)
{
    Polynom temp(obj);
    temp *= oth;
    return temp;
}

bool operator==(const Polynom& obj, const Polynom& oth)
{
    return obj.getCoeff() == oth.getCoeff();
}

bool operator!=(const Polynom& obj, const Polynom& oth)
{
    return !(obj == oth);
}

