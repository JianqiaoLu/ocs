#include "headl.h"
#include <iostream>
#include <random>
#include <iomanip>

const int MAXINT = 1e5;
bool selected[MAXINT];
double r_mass[MAXINT];
vector<pair<int,double>> neibors[1000];
vector<pair<int,double>> current_mass_weight;
double d = 100;
double g(double y)
{
    return expl(y - 1);
}
double g_inver(double y)
{
    return logl(y) + 1;
}
void get_mass(int i)
{
    double r = -1, l = 0;
    for (vector<pair<int, double>>::iterator iter = neibors[i].begin(); iter != neibors[i].end(); iter++)
    {
        r = max(r, (1 - g(r_mass[iter->first])) * iter->second);
    }
    current_mass_weight.clear();
    while ((r - l) > 1e-3)
    {
        double m = l + 1.0 * (r - l) / 2;
        double tt = 0;
        for (vector<pair<int, double>>::iterator iter = neibors[i].begin(); iter != neibors[i].end(); iter++)
        {
            if ((1 - g(r_mass[iter->first])) * iter->second <= m) continue;
            tt += max(g_inver(1 -  1.0 * m / iter->second ) - r_mass[iter->first],0.0);
        }
        if (tt >= 1)
            l = m;
        else
            r = m;
    }
    for (vector<pair<int, double>>::iterator iter = neibors[i].begin(); iter != neibors[i].end(); iter++)
    {
        if ((1 - g(r_mass[iter->first])) * iter->second <= l) 
          current_mass_weight.push_back(make_pair(iter->first, 0));
        else
          current_mass_weight.push_back(make_pair(iter->first, max(g_inver(1 -  1.0 * l / iter->second ) - r_mass[iter->first],0.0)));

    }
}
double choose()
{
    double mass = 0, ch = 0;
    int index = 0;
    vector<pair<int,double>> valid_mass_weight;
    for (vector<pair<int, double>>::iterator iter = current_mass_weight.begin(); iter != current_mass_weight.end(); iter++) 
    {
        if(not selected[iter->first]) valid_mass_weight.push_back(*iter);
    }
    if(not valid_mass_weight.size()) return -1;
    for (vector<pair<int, double>>::iterator iter = valid_mass_weight.begin(); iter != valid_mass_weight.end(); iter++)
    {
        mass += iter->second;
    }
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<double> distr(0, mass);
    double rr =  distr(eng);
    for (vector<pair<int, double>>::iterator iter = valid_mass_weight.begin(); iter != valid_mass_weight.end(); iter++)
    {
        ch+= iter->second;
        if(ch >= rr) 
        {
            index = iter->first;
            break;
        }
    }
    selected[index] = 1;
    return index;
}
void process(int i)
{
    get_mass(i);
    choose();
    return ;
}
int main()
{

    freopen("test_in.txt", "r", stdin);
    // freopen("test_out.txt", "w", stdout);
    memset(selected, 0, sizeof(selected));
    memset(r_mass, 0, sizeof(r_mass));
    vector<vector<pair<int,double>>> onlines =  
    {
        {
            {0,0.1},
            {1,0.3},
        },
        {
            {2,0.3},
            {3,0.5},
        }
    };
    int sizet = onlines.size();
    for (int i = 0; i < sizet; i++)
    {
        neibors[i] = onlines[i];
        process(i);
    }
    for (int i = 0; i < 5; i++)
    {
        cout<<selected[i]<<endl;
    }
    return 0;
}
