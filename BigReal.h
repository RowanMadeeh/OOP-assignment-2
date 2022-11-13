#include <iostream>
#include <bits/stdc++.h>
#include "BigDecimalIntClass.h"

using namespace std;

class BigReal
{

private:

    string num;
    BigDecimalInt before;
    BigDecimalInt after;

public:

    BigReal(string realNumber);

    BigReal(double realNumber = 0.0);

    BigReal(BigDecimalInt realNumber);

    BigReal(const BigReal& other);

    BigReal(BigReal&& other);

    BigReal& operator = (BigReal& other);

    BigReal& operator = (BigReal&& other);

    BigReal operator + (BigReal& other);

    BigReal operator - (BigReal& other);

    bool operator < (BigReal anotherReal);

    bool operator > (BigReal anotherReal);

    bool operator == (BigReal anotherReal);

    int size();

    char sign();

    friend ostream& operator << (ostream& out, BigReal& num);

    friend istream& operator >> (istream& out, BigReal& num);

    void assign(string realNumber);

};
