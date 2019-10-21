#include <iostream>
#include "math/MathFunctions.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 3){
        // printf("Usage: %s base exponent \n", argv[0]);
        cout << "Usage: " << argv[0] << "base exponent" <<endl;
        return 1;
    }
    double base = atof(argv[1]);
    int exponent = atoi(argv[2]);
    double result = power(base, exponent);
    //printf("%g ^ %d is %g\n", base, exponent, result);
    cout << base << "^" << exponent << " is " << result <<endl;
    return 0;
}
