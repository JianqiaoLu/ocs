#include "headl.h"
// long double p(double y)
// {
//     return exp(-1.0 * y - 0.5 * y * y);
// }
// long double p(double y)
// {
//     return exp(-y - 0.1);
// }
// long double p_diff(double y)
// {
//     return  exp(- 1.0 * y -  0.5 * y * y) * (-1.0 - y);
// }
// long double p_diff(double y)
// {
//     return exp(-y - 0.1) * (-1);
// }

// map<long double, long double> pp;
const long double  inf = 0x3f3f3f3f;
long double p[100000];
void test3()
{
    long double appr = 0;
    int d = 10000;
    p[0]  = 1;
    int y = 0;
    // printf("p(%f) = %Lf\n", y, p[y]);
    while (y <= 10*d)
    {
        long double v  = -1.0/ p[max(y - d,0)];
        y += 1;
        p[y] =  p[y - 1] + v*p[y- 1] * 1.0/d;
        if(p[y] > 0) appr += exp(-1.0*y/d) * ( 1- p[y]) * 1.0 /d;
        else appr += exp(-1.0*y/d) * 1.0 /d;
        // printf("p(%f) = %Lf\n ", 1.0 * y/d, p[y] );
    }
    cout << appr;

}
// void test3()
// {
//     printf("")
// }
void test2()
{
    // printf("p(%f) = %Lf\n", y , pp[y]);
    p[0]  = 1;
    int y = 0, d = 1000;
    printf("p(%f) = %Lf\n", y, p[y]);
    while (y <= 2*d)
    {
        int x = d, wor = d;
        long double v = -inf;
        while (x >=0)
        {
            long double vv;
            if(x == d) 
            {
                 vv = -1.0/ p[max(y - d,0)];
            }
            else
            {
            vv = log((1.0 * x/ d * p[max(y - x, 0)])/(1- 1.0 *x/d+ 1.0*x/d*p[max(y - x, 0)]))/ (1-1.0*x/d);
            }
            
            if(vv > v) {
                wor =x;
                v = vv;
            }
            x -= 1;
        }
        y += 1;
        p[y] =  p[y - 1] + v*p[y- 1] * 1.0/d;
        long double vvv;
        if(y<= d)  vvv = exp(-1.0*y/d);
        else vvv = exp(-exp(1.0*y/d-1));
        // printf("p(%f) = %Lf\n ", 1.0 * y/d, p[y] );
        printf("num p = %Lf and cal p = %Lf at y = %Lf \n",  p[y], vvv, 1.0*y/d);
    }
}
// void test()
// {
//     double y = 1.000001;
//     while (y < 10)
//     {
//         double x = 1.0;
//         while (x >= 0)
//         {
//             long double lhs = x * p(y - x) / (1 - x + x * p(y - x));
//             // long double rhs = exp((1 - x) * p_diff(y) / p(y));
//             // if(lhs > rhs) printf("lhs:%.10lf, rhs:%.10lf, x:%f, y:%f \n", lhs, rhs, x,y);
//             printf("lhs:%f, rhs:%f, x:%f, y:%f \n", lhs, rhs, x, y);
//             x -= 0.0001;
//         }
//         y += 0.01;
//     }
// }
int main()
{
    freopen("test_in.txt", "r", stdin);
    freopen("test_out.txt", "w", stdout);
    test2();
}
