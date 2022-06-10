#include <iostream>
#include <math.h>
using namespace std;
const int d = 10000;
const int inf = 0xffffffff;

double get_y1(double a, double x)
{
    return 1.0 * exp(1.0 * a * x * x * x + 0.5 * x * x + x);
}
double get_y2(double a3, double a2, double x)
{
    return 1.0 * exp(1.0 * a3 * x * x * x + a2 * x * x + x);
}
int test3()
{

    freopen("numbers_test.txt", "w", stdout);
    long double w[d];
    // printf("w[%d]: %f\n" , 0 , w[0]);
    w[0] = 1;
    int k1 = 1;
    for (int i = 1; i <= d; i++)
    {
        long double dom = 0;
        for (int k = k1; k < d; k++)
        {
            long double v = powl((d - k) / (k * w[i - 1] + d - k), 1.0 / k);
            if (dom < v)
            {
                dom = v;
                k1 = k;
            }
            else
                break;
        }
        w[i] = 1.0 * w[i - 1] / dom;
        printf("%f %d %.12Lf\n", 1.0 * i / d,k1,  w[i]);
    }
    return 0;
    // freopen("test_out.txt", "w", stdout);
    // double a2 = 0.5;
    // while (a2 > 0)
    // {
        // double a3 = 1;
        // int loc;
        // for (int i = 1; i < d; i++)
        // {
            // double x = 1.0 * i / d;
            // double l = 0, r = 1.0;
            // while (abs(r - l) > 1e-10)
            // {
                // double m = (r - l) * 1.0 / 2 + l;
                // double ans = get_y2(m, a2, x);
                // if (ans > w[i])
                    // r = m;
                // else
                    // l = m;
            // }
            // if (a3 > l)
                // a3 = l, loc = i;
        // }
        // printf("a2 = %.12f, a3 =  %.12f is on %d\n", a2, a3, loc);
        // a2 -= 0.0001;
    // }
    // return 0;
}
int test2()
{
    freopen("numbers_test.txt", "w", stdout);
    double w[d];
    // printf("w[%d]: %f\n" , 0 , w[0]);
    w[0] = 1;
    int k1 = 1;
    for (int i = 1; i <= d; i++)
    {
        double dom = 0;
        for (int k = k1; k < d; k++)
        {
            double v = powl((d - k) / (k * w[i - 1] + d - k), 1.0 / k);
            if (dom < v)
            {
                dom = v;
                k1 = k;
            }
            else
                break;
        }
        w[i] = 1.0 * w[i - 1] / dom;
        printf("%f %d %.12f\n", 1.0 * i / d, k1, w[i]);
    }
    freopen("test_out.txt", "w", stdout);
    double a = 1.0;
    for (int i = 1; i < d; i++)
    {
        double x = 1.0 * i / d;
        double l = 0, r = 1.0;
        while (abs(r - l) > 1e-10)
        {
            double m = (r - l) * 1.0 / 2 + l;
            double ans = get_y1(m, x);
            if (ans > w[i])
                r = m;
            else
                l = m;
        }
        printf("%d : %.12Lf\n", i, l);
        a = min(a, l);
    }
    // printf("%.12f",a);
    return 0;
}
int test4()
{
    freopen("test1.txt","w", stdout);
    long double w[d+1];
    w[0] = 1;
    for(int i = 1;  i <= d ; i++) w[i] = w[i-1] + 1.0 * w[i-1]*w[i-1] / ( d - 1), printf("%.12Lf",w[i]);
}
int main()
{
    test3();
}