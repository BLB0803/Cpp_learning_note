#include <iostream>
// #include "math/MathFunctions.h"
#include "config.h"

#ifdef USE_MYMATH
    #include "math/MathFunctions.h"
#else
    #include<math.h>
#endif

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 3){
        cout << "Usage: " << argv[0] << "base exponent" <<endl;
        return 1;
    }
    double base = atof(argv[1]);
    int exponent = atoi(argv[2]);

#ifdef USE_MYMATH
    cout << "Using our own math lib. "<<endl;
    double result = power(base, exponent);
#else
    cout << "Using standard math lib. "<<endl;
    double result = pow(base, exponent);
#endif
    cout << base << "^" << exponent << " is " << result <<endl;
    return 0;
}
