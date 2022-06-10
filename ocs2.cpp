#include "headl.h" 
const int d = 1000;
double get_w(double a4,double a3, double x)
{
    return 1.0 * exp(1.0 * a4 * x * x * x * x + a3 * x * x * x + 0.49 * x * x + x);
}
void get()
{
    double w[d + 1];
    w[0] = 1;
    for (int i = 1; i <= d ; i++)
    {
        w[i] = w[i-1] + 1.0 * w[i-1]*w[i-1] /(d-1);
        // printf("w[%f] : %f\n", 1.0 * i / d,w[i] );
    }
    freopen("test_out.txt", "w", stdout);
    double a4 = 0.5;
    while (a4 > 0)
    {
        double a3 = 1;
        int loc;
        for (int i = 1; i < d; i++)
        {
            double x = 1.0 * i / d;
            double l = 0, r = 1.0;
            while (abs(r - l) > 1e-10)
            {
                double m = (r - l) * 1.0 / 2 + l;
                double ans = get_w(a4, m, x);
                if (ans > w[i])
                    r = m;
                else
                    l = m;
            }
            if (a3 > l)
                a3 = l, loc = i;
        }
        printf("a4 = %.12f, a3 =  %.12f is on %d\n", a4, a3, loc);
        a4 -= 0.0001;
    }
}
void test()
{
    long double num = 1e10;int mx = 0;
    for (int gap = 2; gap < d ; gap++)
    {
        long double w = 1;
        for (int i = 0; i <= gap ; i++)
        {
            w += w* w / (gap - 1);
        }
        if(w < num) num = w, mx = gap;
        cout<< gap << ":" << w << endl;
    }
    
}
int main() 
{ 
  freopen("test_in.txt", "r", stdin); 
//   freopen("test_out.txt","w", stdout); 
//   get();
  test();
  return 0;
}
