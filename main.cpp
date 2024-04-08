#include <iostream>
#include<bitset>
#include <vector>
#include <set>
#include <map>
#define bitsize 8
using namespace std;

struct Latancies
{
    set<int> forbidden_latancies;
    set<int> permissible_latancies;
};

void print_latancies(Latancies &s) {
    cout<<"Forbidden Latancies = {";
    string temp="";
    for(auto e:s.forbidden_latancies) {
        temp.push_back(e);
        temp.push_back(',');
    }
    temp.pop_back();
    cout<<temp<<"}\n";

    temp="";
    cout<<"\nPermissible Latancies = {";
    for(auto e:s.permissible_latancies) {
        temp.push_back(e);
        temp.push_back(',');
    }
    temp.pop_back();
    cout<<temp<<"}\n";

}

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

string convert_vector_to_string(vector<int>&v) {
    string temp="";
    for(int e:v) temp.push_back(e+'0');
    return temp;
}

void non_linear_pipeline() {
    vector<vector<int>> g = {
        {1, 0, 0, 0, 0, 1, 0, 1},
        {0, 1, 0, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 1, 0}
    };

    Latancies u = get_latancies(g); // Latancies 
    vector<int>v=collision_vector(u); // Collison vector
    bitset<bitsize> icv(convert_vector_to_string(v));

    cout<<"Collision Vector = "<<icv;
    cout<<endl;

}

int main()
{
    non_linear_pipeline();
}