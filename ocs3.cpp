#include "headl.h" 
// const int d = 100;
long double f(double x, double w)
{
    if(x == 0) return w;
    else 
    {
        return logl(1 - x + x*expl(w)) / x - logl(1- x)/x;
    }
}

void test2(int d)
{
    long double ans = 0 ;
    for (int i = 0; i < 100 * d; i++)
    {
        long double x = 1.0 * i / d, omega;
        omega = x;
        ans += 1.0/d *  expl(-x) * (1 - 1.0/(expl(1.1*omega)));
    }
    cout<<ans;
}
void test(int d)
{
  long double w[10 * d + 1] ;
  long double ans = 0;
  w[0] = 0;
  for (int i = 1; i <= 10* d; i++)
  {
      long double l  = 0 , r = 1; 
      while (abs(r - l ) > 1e-3)
      {
          long double m1 = (l + l + r)/3, m2 = (l + r + r)/3;
          if(f(m1,w[i-1]) < f(m2,w[i-1])) r = m2;
          else l = m1;
      }
      long double x = 1.0 * i / d;
      w[i] = w[i-1] + f((r + l) /2, w[i-1])/d;
      ans += 1.0/d *  expl(-x) * (1 - 1.0/expl(w[i]));
    //   printf("%f : %Lf\n",1.0 * i/d,  1 - 1.0/expl(w[i]));
  }
  cout<<ans;
//   for (int i = 0; i < 10 *d ; i++)
//   {
//       long double x = 1.0 * i / d;
//       else ans += 1.0/d *  expl(-x) ;
//   }
}
int main() 
{ 
    test2(5000);
}
