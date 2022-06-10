#include "headl.h" 
const int d = 100;
long double w(double x)
{
          return exp(exp(x) - 1);
}

long double getx(double x)
{
    return 1- 1.0 * x/2  + log(1 + 1.0 * x/2) + log(1.0 * x/2); 
}

void test3()
{
  double W = 0, x ;
  while (W <= 1)
  {
      double lhs, rhs;
      x = 0;
      while ( x < 1)
      {
          lhs = 1 + 1.0*x/(1 - x) * W;
          rhs = powl(exp(1)*W, exp(x) - 1);
          if(lhs < rhs )printf("lhs: %.12f, rhs : %.12f W: %f, x : %f\n", lhs, rhs,W, x);
          x += 1.0/d;
      }
      W += 1.0/d;
    //   printf("%f\n", y);
  }  
}

void test2()
{
  double y = 0, x ;
  while (y <= 10)
  {
      double lhs, rhs;
      x = 0;
      while ( x < 1)
      {
          lhs = 1.0/x * log(1  + 1.0*w(y) *x/(1-x));
          rhs = 1.0 * exp(y) * (exp(x)  - 1)/x;
          if(lhs < rhs )printf("lhs: %.12f, rhs : %.12f y: %f, x : %f\n", lhs, rhs,y, x);
          x += 1.0/d;
      }
      y += 1.0/d;
    //   printf("%f\n", y);
  }  
}

void test1() 
{ 
  double y = 0, x ;
  while (y <= 1000)
  {
      double lhs, rhs;
      x = 0;
      while ( x < 1)
      {
          lhs = 1.0/x * log(1  + (x*w(y))/(1-x)) ;
          rhs = 1.0 * exp(y) * 1.001;
          if(lhs < rhs )printf("lhs: %.12f, rhs : %.12f y: %f, x : %f\n", lhs, rhs,y, x);
          x += 1.0/d;
      }
      y += 1.0/d;
    //   printf("%f\n", y);
  }
}

int main()
{
  freopen("test_in.txt", "r", stdin); 
  freopen("test_out.txt","w", stdout); 
  test3();
}

