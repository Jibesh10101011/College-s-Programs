#include <iostream>
#include<bitset>
#include <vector>
#include <set>
#include <map>
#include<stack>
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

vector<int> get_position_vector(string u) {
    vector<int>s;
    int diff=u.size()-1;
    for(int i=diff;i>=0;i--) {
        if(u[i]=='0') s.push_back(diff-i+1);
    }
    return s;

}

string get_next_state(bitset<bitsize>&icv,bitset<bitsize>&curr,int pos) {
    bitset<bitsize>temp(curr>>pos);
    bitset<bitsize>next_state=temp|icv;
    return next_state.to_string();
}

void print_transition_diagram(map<pair<string,int>,string>&mp) {
    cout<<"Transition Tree : \n";
    for(auto e:mp) {
        cout<<e.first.first<<" "<<e.first.second<<" "<<e.second<<'\n';
    }
    cout<<endl;
}

void transition_diagram(bitset<bitsize> &icv) {
    map<pair<string,int>,string>mp;

    string initial_collison_vector=icv.to_string();
    stack<string>stk; 
    stk.push(initial_collison_vector);
    
    map<string,bool>vis;
    while(!stk.empty()) {
        string curr_vector=stk.top();
        if(!vis[curr_vector]) {
            vis[curr_vector]=true;
            vector<int>position_vector=get_position_vector(curr_vector);
            bitset<bitsize>curr(curr_vector);
            for(int e:position_vector) {
                string next_state=get_next_state(icv,curr,e);
                pair<string,int> pr={curr_vector,e};
                mp[pr]=next_state;
                stk.push(next_state);
            }
        }
        stk.pop();
    }


    print_transition_diagram(mp);

}



int main()
{
   bitset<bitsize> icv("01011010");
   transition_diagram(icv);
    // vector<int>v=get_position_vector("01111111");
    // for(auto e:v) {
    //     cout<<e<<" ";
    // }
   return 0;
}