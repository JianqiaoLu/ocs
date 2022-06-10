#include "headl.h" 
long double w(long double y)
{
    return 1.0 * exp(exp(y) - 1);
}
long double f(long double x, long double y)
{

    return 1.0/(x*expl(y))* logl(1.0*(1 +  x*(w(y) - 1))/(1 - x));
    // return  w1(y);
}
int main() 
{ 
    for (int y = 0; y < 10 ; y++)
    {
        printf("y : %d, v : %f\n", y, f(0.9999,y));
    }
}
