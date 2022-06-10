#include "headl.h" 
long double w(double x)
{
    return exp(exp(x) -1 );
}

const int d = 1000;
int main() 
{ 

  freopen("test_in.txt", "r", stdin); 
  freopen("test_out.txt","w", stdout); 
  for (double  y = 0; y <= 1; y += 1.0/d)
  {
    int loc = 1;
    double v = 1e10;
    for (int k = 1; k < d; k++)
    {
        long double lhs = (1  - 1.0 * k /d )  /  ( 1.0*k/d * w(y)+  1  - 1.0 * k/d );
        long double rhs = powl(w(y)/w(y + 1.0/d),k);
        v  = rhs - lhs;
        printf("y: %f k : %d v: %.10f\n", y,k,v );
        // if((rhs - lhs) < v) loc = k, v = (rhs- lhs);
        // if(abs(lhs  - rhs) < 1e-10) printf("y:%f, k:%d\n",y, k);
    }
    printf("y: %f k : %d v: %.10f\n", y,loc,v );
  }
}
