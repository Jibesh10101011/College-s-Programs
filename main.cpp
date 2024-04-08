#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;

struct Latancies
{
    set<int> forbidden_latancies;
    set<int> permissible_latancies;
};

set<int> latancies_from_sigle_row(vector<int> &v)
{

    set<int> s;

    for (int i = 0; i < v.size(); i++)
    {
        for (int j = i + 1; j < v.size(); j++)
        {
            s.insert(v[j] - v[i]);
        }
    }

    return s;
}

Latancies get_latancies(vector<vector<int>> &g)
{
    int m = g.size();    // Rows
    int n = g[0].size(); // Cols
    Latancies s;
    for (int i = 0; i < m; i++)
    {
        vector<int> exist = {};
        for (int j = 0; j < n; j++)
        {
            if (g[i][j])
                exist.push_back(j);
        }
        for (int k = 0; k < exist.size(); k++)
        {
            for (int l = k + 1; l < exist.size(); l++)
            {
                s.forbidden_latancies.insert(exist[l] - exist[k]);
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (!s.forbidden_latancies.count(i))
        {
            s.permissible_latancies.insert(i);
        }
    }
    return s;
}


vector<int> collision_vector(Latancies &s) {
    vector<int>v(s.forbidden_latancies.size()+s.permissible_latancies.size(),0);

    /*
        Forbidden Latancy => 1
        Permissible Latancy => 0
    */

   for(auto e:s.forbidden_latancies) {
        v[e-1]=1;
   }

   return v;

}

int main()
{

    vector<vector<int>> g = {
        {1, 0, 0, 0, 0, 1, 0, 1},
        {0, 1, 0, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 1, 0}
    };

    Latancies u = get_latancies(g);

    for (auto e : u.forbidden_latancies)
    {
        cout << e << " ";
    }

    cout << endl;

    for (auto e : u.permissible_latancies)
    {
        cout << e << " ";
    }

    cout<<endl;

    vector<int>v=collision_vector(u);

    cout<<"Collision Vector = ";
    for(auto e:v) {
        cout<<e<<" ";
    }

    return 0;
}