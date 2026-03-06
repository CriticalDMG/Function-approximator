#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP
#include "Fraction.hpp"
#include <vector>
#include <cassert>
#include <iostream>

class Polynom
{
public:
    //constructs for the polynom
    Polynom():coef(1, Fraction(0)) {}
    Polynom(const std::vector<Fraction>& c):coef(c) {}
    Polynom(const Polynom& oth);
    Polynom& operator=(const Polynom& oth);
    ~Polynom() = default;

    //redefining some operators(not all, cause devision is tricky)
    Polynom& operator+=(const Polynom& oth);
    Polynom& operator-=(const Polynom& oth);
    Polynom& operator*=(const Polynom& oth);
    Polynom& operator*=(int oth);
    Fraction& operator[](unsigned int index)
    {
        assert(index <= coef.size());
        return coef[index];
    }
    Fraction operator[](unsigned int index) const
    {
        assert(index <= coef.size());
        return coef[index];
    }
    friend std::ostream& operator<<(std::ostream& os, Polynom& obj)
    {
        for(int i = (int)obj.degree(); i >= 0; --i)
        {
            if(i == 0)
            {
                os << obj[i]; 
                return os;
            }
            os << obj[i] << "*x^" << i << " + ";
        }
        return os;
    }

    //differentiating and integrating(with a constant) a polynom
    void differentiate();
    void integrate(Fraction constant = Fraction(0));

    //calculation f(x) at a point
    Fraction at(const Fraction point) const
    {
        Fraction res(0);
        for(size_t i = 0; i < coef.size(); ++i)
        {
            res = coef[i] + res * point;
        }

        return res;
    }
    
    //removes excess front zeros like 0*x^3 + 0*x^2 + 1 = 1 
    void trim();

    size_t degree() const { return ((coef.empty()) ? -1 : (coef.size())) - 1; }
    std::vector<Fraction> getCoeff() const { return coef; }

private:
    std::vector<Fraction> coef;
};

Polynom operator+(Polynom& obj, const Polynom& oth);
Polynom operator-(Polynom& obj, const Polynom& oth);
Polynom operator*(Polynom& obj, const Polynom& oth);
bool operator==(const Polynom& obj, const Polynom& oth);
bool operator!=(const Polynom& obj, const Polynom& oth);

#endif 