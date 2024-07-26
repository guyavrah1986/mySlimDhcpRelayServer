module;

#include <iostream>

export module my_module;
export module PublicFunc;

using namespace std;

export void PublicFunc(int x)
{
    cout << "x is:" << x << endl;    
}