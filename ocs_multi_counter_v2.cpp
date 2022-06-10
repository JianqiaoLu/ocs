#include "headl.h"
void decreasing_p_v1(int d)
{
    vector<long double> prev(d + 1, 1), next(d + 1, 1);
    vector<vector<long double> > ans;
    int up = 20 * log(d);
    for (int t = 1; t <= d; t++)
    {
        prev[t] = pow(expl(-1.0 * t / d), up + 1);
    }
    ans.push_back(prev);
    for (int k = up; k >= 1; k--)
    {
        for (int t = 1; t <= d; t++)
        {
            double num = (next[t - 1]) * (d - k) * (prev[t - 1]);
            double dom = k * (next[t - 1]) + (d - k) * (prev[t - 1]);
            next[t] = 1.0 * num / dom;
        }
        prev = next;
        ans.push_back(prev);
        cout << "层数" << k << "  " << prev[d] << endl;
    }
    int a = 1;
}

void decreasing_p_v2(int d)
{
    vector<long double> prev(d + 1, 1), next(d + 1, 1);
    vector<vector<long double> > ans;
    int up = log(d) * 2;
    for (int t = 1; t <= d; t++)
    {
        prev[t] = pow(expl(-1.0 * t / d), up + 1);
    }
    for (int k = up; k >= 1; k--)
    {
        for (int t = 1; t <= d; t++)
        {
            double num = (next[t - 1]) * (d - k) * pow(prev[t - 1], 1.0 * k / (k + 1));
            double dom = k * exp(1.0 * (t - 1) / d) * (next[t - 1]) + (d - k) * pow(prev[t - 1], 1.0 * k / (k + 1));
            next[t] = 1.0 * num / dom;
        }
        prev = next;
        ans.push_back(prev);
        cout << "层数" << k << "  " << prev[d] << endl;
    }
}
void decreasing_p_v3(int d)
{
    vector<long double> prev(d + 1, 1), next(d + 1, 1);
    vector<vector<long double>> ans;
    int up = log(d);
    for (int t = 1; t <= d; t++)
    {
        prev[t] = pow(expl(1.0 * t / d), up);
    }
    ans.push_back(prev);
    for (int k = up - 1; k >= 1; k--)
    {
        for (int t = 1; t <= d; t++)
        {
            next[t] = next[t - 1] + prev[t - 1] * k / d;
        }
        prev = next;
        ans.push_back(prev);
        cout << "层数" << k << "  " << prev[d] << endl;
    }
    return;
}

void test(int d, int k1)
{
    int ld = log(d);
    double y = 1.0;
    for (int k = 1; k <= k1; k++)
    {
        double i1 = expl(1.0 * y * ld) / powl(ld, k), i2 = 0;
        for (int i = 1; i <= k; i++)
        {
            i1 *= (ld - i);
        }
        for (int i = 0; i < k; i++)
        {
            double yi = pow(y, i);
            for (int j = 1; j <= i; j++)
            {
                yi /= j;
            }

            for (int j = 0; j < i; j++)
            {
                yi *= (ld - k + j);
            }
            double mid = 1;
            for (int j = 1; j <= k - i; j++)
            {
                mid *= 1.0 * (ld - j) / ld;
            }
            yi *= (1 - mid);
            i2 += yi;
        }
        double ans = i1 + i2;
        cout << "层数" << ld - k << " " << ans << endl;
    }
}

int main()
{
    // freopen("test_in.txt", "r", stdin);
    // test(1e6, log(1e6) - 1);
    // decreasing_p_v3(1e6);
}
