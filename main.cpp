#include <iostream>
#include <bits/stdc++.h>
#include "BigDecimalIntClass.h"
#include "BigReal.h"

using namespace std;

int main()
{
/*
    BigReal n1 ("11.9000000000000000000000000000000001");
    BigReal n2 ("2333333333339.1134322222222292");
    BigReal n3 = n1 + n2;
    cout << n3<<endl;
    cout<<n2.after<<endl;
*/

    BigReal k("0");
    BigReal h("00002.1111100");
    BigReal i = k-h;
    cout<<i<<endl;
    return 0;
}

//zwedt ? fi el regex b3d el .
//zwedt remove zeroes
