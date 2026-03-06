#include <iostream>
#include <stdexcept>
#include <math.h>
#include "Fraction.hpp"

Fraction::Fraction(int n, int d):numer(n), denom(d)
{
    if(d == 0)
    {
        throw "Denominator cannot be 0";
    }
    reduce();
}

Fraction::Fraction(const Fraction& oth): numer(oth.numer), denom(oth.denom) {}
Fraction& Fraction::operator=(const Fraction& oth)
{
    if(this != &oth)
    {
        numer = oth.numer;
        denom = oth.denom;
    }

    return *this;
}

//Reducing the fraction by fanding the gcd
void Fraction::reduce()
{
    if(denom < 0)
    {
        denom = -denom;
        numer = -numer;
    }
    int gcd = FindGCD(std::abs(numer), std::abs(denom));

    numer /= gcd;
    denom /= gcd;
}

int Fraction::FindGCD(int a, int b)
{
    if (a == 0) return b;

    while(a != b)
    {
        if(a > b)
        {
            a = a - b;
        }
        else
        {
            b = b - a;
        }
    }

   return a;
}

int Fraction::FindLCM(int a, int b)
{
    if(a == 0) return 0;
    return abs((a / FindGCD(a, b)) * b);
}

Fraction& Fraction::operator+=(const Fraction& oth)
{
    if(numer == 0)
    {
        *this = oth;
        return *this;
    } 
    int lcm = FindLCM(denom, oth.denom);

    numer = numer * (lcm / denom) + oth.numer * (lcm / denom);
    denom = lcm;

    reduce();
    return *this;
}

Fraction& Fraction::operator-=(const Fraction& oth)
{
    int lcm = FindLCM(denom, oth.denom);
    numer = numer * (lcm / denom) - oth.numer * (lcm / denom);
    denom = lcm;

    reduce();
    return *this;
}

Fraction& Fraction::operator*=(const Fraction& oth)
{
    numer *= oth.numer;
    denom *= oth.denom;

    reduce();

    return *this;
}

Fraction& Fraction::operator/=(const Fraction& oth)
{
    if(oth.numer == 0)
    {
        numer = 0;
        return *this;
    } 
    
    numer *= oth.denom;
    denom *= oth.numer;

    reduce();
    
    return *this;
}

Fraction operator+(Fraction obj, const Fraction& oth)
{
    return obj += oth;
}

Fraction operator-(Fraction obj, const Fraction& oth)
{
    return obj -= oth;
}

Fraction operator*(Fraction obj, const Fraction& oth)
{
    return obj *= oth;
}

Fraction operator*(Fraction obj, int oth)
{   
    return obj *= oth;
}

Fraction operator/(Fraction obj, const Fraction& oth)
{
    return obj /= oth;
}

bool operator<=(const Fraction& obj, const Fraction& oth)
{
    return !(obj > oth);
}

bool operator>=(const Fraction& obj, const Fraction& oth)
{
    return !(obj < oth);
}

bool operator>(const Fraction& obj, const Fraction& oth)
{ 
    return oth < obj;
}

bool operator<(const Fraction& obj, const Fraction& oth)
{
    return((obj.GetNumerator() * oth.GetDenom()) < (obj.GetDenom() * oth.GetNumerator()));
}

bool operator==(const Fraction& obj, const Fraction& oth)
{
    if(obj.GetNumerator() == 0 && oth.GetNumerator() == 0) return true;
    return ((obj.GetNumerator() == oth.GetNumerator()) && (obj.GetDenom() == oth.GetDenom()));
}

bool operator!=(const Fraction& obj, const Fraction& oth)
{
    return !(obj == oth);
}
