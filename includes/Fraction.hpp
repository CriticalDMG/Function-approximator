#ifndef FRACTION_HPP
#define FRACTION_HPP
#include <iostream>
class Fraction
{
public:
    //constructors
    Fraction():numer(0), denom(1) {}
    Fraction(int n, int d);
    explicit Fraction(int a): numer(a), denom(1) {}
    Fraction(const Fraction& oth);
    Fraction& operator=(const Fraction& oth);
    ~Fraction() = default;

    //defining operation with fractions
    Fraction& operator+=(const Fraction& oth);
    Fraction& operator-=(const Fraction& oth);
    Fraction& operator*=(const Fraction& oth);
    Fraction& operator*=(int oth)
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
    
    int GetNumerator() const { return numer; }
    int GetDenom() const { return denom; }
private:
    void reduce();
    int FindGCD(int a, int b);
    int FindLCM(int a, int b);
    int numer;
    int denom;
};

Fraction operator+(Fraction obj, const Fraction& oth);
Fraction operator-(Fraction obj, const Fraction& oth);
Fraction operator*(Fraction obj, const Fraction& oth);
Fraction operator*(Fraction obj, int oth);
Fraction operator/(Fraction obj, const Fraction& oth);
bool operator<=(const Fraction& obj, const Fraction& oth);
bool operator>=(const Fraction& obj, const Fraction& oth);
bool operator>(const Fraction& obj, const Fraction& oth);
bool operator<(const Fraction& obj, const Fraction& oth);
bool operator==(const Fraction& obj, const Fraction& oth);
bool operator!=(const Fraction& obj, const Fraction& oth);

#endif
