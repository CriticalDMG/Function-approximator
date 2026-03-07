#ifndef FRACTION_HPP
#define FRACTION_HPP
#include <iostream>

//int will probably overflow when taylor series appear
typedef long long type;

class Fraction
{
public:
    //constructors
    Fraction():numer(0), denom(1) {}
    Fraction(type n, type d);
    explicit Fraction(type a): numer(a), denom(1) {}
    Fraction(const Fraction& oth);
    Fraction& operator=(const Fraction& oth);
    ~Fraction() = default;

    //defining operation with fractions
    Fraction& operator-=(const Fraction& oth);
    Fraction& operator+=(const Fraction& oth);
    Fraction& operator+=(type val);
    Fraction& operator*=(const Fraction& oth);
    Fraction& operator*=(type oth)
    {
        numer *= oth;
        reduce();
        return *this;
    }
    Fraction& operator/=(const Fraction& oth);

    // void SetNumer(int a) { numer = a; }
    // void SetDenom(int a) { denom = a; }

    friend std::ostream& operator<<(std::ostream& os, const Fraction& fr)
    {
        if(fr.numer == 0 || fr.denom == 1)
        {
            os << fr.numer;
            return os;
        }
        os << fr.numer << "/" << fr.denom;
        return os;
    } 

    friend std::istream& operator>>(std::istream& in, Fraction& fr)
    {
        char c;
        if(in >> fr.numer >> c >> fr.denom)
        {   
            if(fr.denom == 0)
            {
                fr.denom = 1;
            }
            fr.reduce();
        }
        return in;
    }
    
    type GetNumerator() const { return numer; }
    type GetDenom() const { return denom; }
    double ConvToDouble()
    {
        double res = (double)numer / (double)denom;
        return res;
    }
private:
    void reduce();
    type FindGCD(type a, type b);
    type FindLCM(type a, type b);
    type numer;
    type denom;
};

Fraction operator+(Fraction obj, const Fraction& oth);
Fraction operator+(Fraction obj, type val);
Fraction operator-(Fraction obj, const Fraction& oth);
Fraction operator*(Fraction obj, const Fraction& oth);
Fraction operator*(Fraction obj, type oth);
Fraction operator/(Fraction obj, const Fraction& oth);
bool operator<=(const Fraction& obj, const Fraction& oth);
bool operator>=(const Fraction& obj, const Fraction& oth);
bool operator>(const Fraction& obj, const Fraction& oth);
bool operator<(const Fraction& obj, const Fraction& oth);
bool operator==(const Fraction& obj, const Fraction& oth);
bool operator!=(const Fraction& obj, const Fraction& oth);

#endif
