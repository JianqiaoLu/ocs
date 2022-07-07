#include "headl.h"
#include <iostream>
#include <random>
#include <iomanip>
#include "hungarian.h"
double vertex_weight[100000];
int nbnum = 2000;
struct OnlineAlg
{
    vector<pair<int, double>> current_mass_weight;
    bool selected[100000];
    double r_mass[100000];
    vector<int> neibors[1000];
    double alg = 0;
    OnlineAlg(vector<vector<int>> onlines, int n)
    {
        alg = 0;
        memset(selected, 0, n);
        std::fill_n(r_mass, n, 0.0);
        for (int i = 0; i < onlines.size(); i++)
        {
            neibors[i] = onlines[i];
            alg += process(i);
        }
    }
    double g(double y)
    {
        // return expl(y - 1);
        return expl(y - 1);
    }
    double g_inver(double y)
    {
        return logl(y) + 1;
    }
    void get_mass(int i)
    {
        double r = -1, l = 0;
        for (vector<int>::iterator iter = neibors[i].begin(); iter != neibors[i].end(); iter++)
        {
            r = max(r, (1 - g(r_mass[*iter])) * vertex_weight[*iter]);
        }
        current_mass_weight.clear();
        while ((r - l) > 1e-5)
        {
            double m = l + 1.0 * (r - l) / 2;
            double tt = 0;
            for (vector<int>::iterator iter = neibors[i].begin(); iter != neibors[i].end(); iter++)
            {
                if ((1 - g(r_mass[*iter])) * vertex_weight[*iter] <= m)
                    continue;
                tt += max(g_inver(1 - 1.0 * m / vertex_weight[*iter]) - r_mass[*iter], 0.0);
            }
            if (tt >= 1)
                l = m;
            else
                r = m;
        }
        for (vector<int>::iterator iter = neibors[i].begin(); iter != neibors[i].end(); iter++)
        {
            if ((1 - g(r_mass[*iter])) * vertex_weight[*iter] <= l)
                current_mass_weight.push_back(make_pair(*iter, 0));
            else
            {
                current_mass_weight.push_back(make_pair(*iter, max(g_inver(1 - 1.0 * l / vertex_weight[*iter]) - r_mass[*iter], 0.0)));
                r_mass[*iter] += max(g_inver(1 - 1.0 * l / vertex_weight[*iter]) - r_mass[*iter], 0.0);
            }
        }
    }
    double choose()
    {
        double mass = 0, ch = 0;
        int index = 0;
        vector<pair<int, double>> valid_mass_weight;
        for (vector<pair<int, double>>::iterator iter = current_mass_weight.begin(); iter != current_mass_weight.end(); iter++)
        {
            if (not selected[iter->first])

            {
                valid_mass_weight.push_back(*iter);
                mass += iter->second;
            }
        }
        if (not valid_mass_weight.size())
            return 0;
        std::random_device rd;
        std::default_random_engine eng(rd());
        std::uniform_real_distribution<double> distr(0, mass);
        double rr = distr(eng);
        for (vector<pair<int, double>>::iterator iter = valid_mass_weight.begin(); iter != valid_mass_weight.end(); iter++)
        {
            ch += iter->second;
            if (ch >= rr)
            {
                index = iter->first;
                break;
            }
        }
        selected[index] = 1;
        return vertex_weight[index];
    }
    double process(int i)
    {
        get_mass(i);
        return choose();
    }

};
vector<vector<int>> hd2()
{
    vector<vector<int>> ans = {
        {0,1},
        {1,2},
    };
    return ans;
}
vector<vector<int>> hd_expyforoneelement(int n)
{
    int m = n/nbnum;
    vector<vector<int>> ans;
    // ans.push_back()
    // for (int i = 0; i < n/m; i = i + n/m/10)
    // {
    //     vector<int> nb(n/m/10);
    //     std::iota (std::begin(nb), std::end(nb), i );
    //     if(i > 0)nb.push_back(0);
    //     ans.push_back(nb);
    // }
    
    for (int i = 0; i < m; i++)
    {
        vector<int> nb(n/m);
        std::iota (std::begin(nb), std::end(nb), i * n/m);
        if(i > 0)nb.push_back(0);
        ans.push_back(nb);
    }
    return ans;
}
vector<vector<int>> hd(int n)
{
    vector<vector<int>> ans;
    vector<int> ol1(n - 1);
    std::iota (std::begin(ol1), std::end(ol1), 0);
    for (int i = 0; i < n - 1; i++)
    {
        ans.push_back(ol1);
    }
    ol1.push_back(n - 1);
    ans.push_back(ol1);
    return ans;
}

vector<vector<int>> uptri(int n)
{
    vector<vector<int>> ans;
    for (int i = 0; i < n; i++)
    {
        vector<int> nb;
        for (int j = i; j < n; j++)
        {
            nb.push_back(j);
        }
        ans.push_back(nb);
    }
    return ans;
}
void init_weight(int n)
{
    std::fill_n(vertex_weight, n, 1);
    // vertex_weight[0]  = 10;
    // for (int i = 0; i < nbnum;i++)
    // {
    //     vertex_weight[i] = 10;
    // }
    
    // vertex_weight[0] = 1;
    // vertex_weight[0] = 100000;
    // vertex_weight[1] = 100000;
    // for (int i = 0; i < n; i++)
    // {
    //     vertex_weight[i] =   i ;
    // }
}

int main()
{
    int itn = 10, n = 1000;
    double ep = 0;
    init_weight(n);
    vector<vector<int>> onlines = uptri(n);
    int sizet = onlines.size();
    hungarian<double> offline_alg(n, sizet);
    for (int i = 0; i < sizet; i++)
    {
        for (vector<int>::iterator iter = onlines[i].begin(); iter != onlines[i].end(); iter++)
        {
            offline_alg.addEdge(*iter, i, vertex_weight[*iter]);
        }
    }
    double opt = offline_alg.solve(), alg;
    for (int i = 0; i < itn; i++)
    {

        OnlineAlg online_alg (onlines, n);
        alg = online_alg.alg;
        ep += 1.0 * alg / opt / itn;
    }
    cout<<"optimal is " << opt << endl;
    cout<<"alg in the last run is " << alg << endl;
    cout << "ratio is " << ep << endl;
    return 0;
}
