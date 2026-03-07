#include <iostream>
#include <stdexcept>
#include <math.h>
#include "Fraction.hpp"

Fraction::Fraction(type n, type d):numer(n), denom(d)
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

    
    type MaxLimit = 1000000000LL;

    if(denom > MaxLimit)
    {
        type scale = denom / MaxLimit + 1;

        numer = (numer + scale / 2) / scale; 
        denom = (denom + scale / 2) / scale;

        // Re-reduce just in case the scaled fraction can be simplified
        type NewGcd = FindGCD(std::abs(numer), std::abs(denom));
        numer /= NewGcd;
        denom /= NewGcd;
    }
}

type Fraction::FindGCD(type a, type b)
{
    if (a == 0) return b;

    while(b != 0)
    {
        type temp = b;
        b = a % b;
        a = temp;
    }

   return a;
}

type Fraction::FindLCM(type a, type b)
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
    type gcd = FindGCD(denom, oth.denom);
    
    // Instead of d1*d2, we use smaller factors to prevent overflow
    type d1Factor = denom / gcd;
    type d2Factor = oth.denom / gcd;

    numer = (numer * d2Factor) + (oth.numer * d1Factor);
    denom = denom * d2Factor;

    reduce();
    return *this;
}

Fraction& Fraction::operator+=(type val)
{
    if(denom == 1)
    {
        numer = numer + val;
        return *this;
    }

    numer = numer + val*denom;
    reduce();
    return *this;
}

Fraction& Fraction::operator-=(const Fraction& oth)
{
    type gcd = FindGCD(denom, oth.denom);
    type d1Factor = denom / gcd;
    type d2Factor = oth.denom / gcd;

    // Scale each numerator by the OTHER denominator's factor
    numer = (numer * d2Factor) - (oth.numer * d1Factor);
    denom = denom * d2Factor;

    reduce();
    return *this;
}

Fraction& Fraction::operator*=(const Fraction& oth)
{

    // Cross-reduce to prevent overflow
    // Simplify (this->numer / oth.denom) and (oth.numer / this->denom)
    type gcd1 = FindGCD(std::abs(numer), std::abs(oth.denom));
    type gcd2 = FindGCD(std::abs(oth.numer), std::abs(denom));

    numer = (numer / gcd1) * (oth.numer / gcd2);
    denom = (denom / gcd2) * (oth.denom / gcd1);

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

Fraction operator+(Fraction obj, type val)
{
    return obj += val;
}

Fraction operator-(Fraction obj, const Fraction& oth)
{
    return obj -= oth;
}

Fraction operator*(Fraction obj, const Fraction& oth)
{
    return obj *= oth;
}

Fraction operator*(Fraction obj, type oth)
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
