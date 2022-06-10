#include "headl.h"

long double w(double y)
{
    return exp( y + 1.0 * y*y/2);
}
void test(int d)
{
    for (double y = 0; y < 10; y += 1.0 / d)
    {
        for (double x = 0; x < 1; x += 1.0 / d)
        {
              long double lhs = 1.0 * w(y + x) /  w(y);
              long double rhs = 1.0*x/(1-x) *w(y) + 1;
              if(lhs > rhs) printf("lhs:%f, rhs:%f, x:%f , y:%f \n",  lhs, rhs, x, y);
        }
    }
}
int main()
{
    // freopen("test_in.txt", "r", stdin);
    freopen("test_out.txt", "w", stdout);
    test(100);
}
