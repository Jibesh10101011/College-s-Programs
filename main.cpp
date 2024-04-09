#include <iostream>
#include <bitset>
#include <vector>
#include <set>
#include <map>
#include <stack>
#define bitsize 8
using namespace std;
struct Latancies
{
    set<int> forbidden_latancies;
    set<int> permissible_latancies;
};
void print_simple_cycles();
void transition_diagram(bitset<bitsize>&);
void simple_cycles(
    map<pair<string, int>, string>&,
    map<string, set<int>>&,
    string,
    map<string, bool>,
    vector<int>);
void print_transition_diagram(map<pair<string,int>, string>&);
string get_next_state(bitset<bitsize> &, bitset<bitsize> &, int);
vector<int> get_position_vector(string);
void non_linear_pipeline();
string convert_vector_to_string(vector<int> &);
vector<int> collision_vector(Latancies &);
Latancies get_latancies(vector<vector<int>>&);
void print_latancies(Latancies &);
void greedy_cycles_print(set<vector<int>>&);

void print_latancies(Latancies &s)
{
    cout << "Forbidden Latancies = {";
    string temp = "";
    for (auto e : s.forbidden_latancies)
    {
        temp.push_back(e+'0');
        temp.push_back(',');
    }
    if(!temp.empty())
    temp.pop_back();
    cout << temp << "}\n";

    temp = "";
    cout << "Permissible Latancies = {";
    for (auto e : s.permissible_latancies)
    {
        temp.push_back(e+'0');
        temp.push_back(',');
    }
    temp.pop_back();
    cout << temp << "}\n";
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

vector<int> collision_vector(Latancies &s)
{
    vector<int> v(s.forbidden_latancies.size() + s.permissible_latancies.size(), 0);

    /*
        Forbidden Latancy => 1
        Permissible Latancy => 0
    */

    for (auto e : s.forbidden_latancies)
    {
        v[e - 1] = 1;
    }

    return v;
}

string convert_vector_to_string(vector<int> &v)
{
    string temp = "";
    for (int e : v)
        temp.push_back(e + '0');
    return temp;
}


vector<int> get_position_vector(string u)
{
    vector<int> s;
    int diff = u.size() - 1;
    for (int i = diff; i >= 0; i--)
    {
        if (u[i] == '0')
            s.push_back(diff - i + 1);
    }
    return s;
}

string get_next_state(bitset<bitsize> &icv, bitset<bitsize> &curr, int pos)
{
    bitset<bitsize> temp(curr >> pos);
    bitset<bitsize> next_state = temp | icv;
    return next_state.to_string();
}

void print_transition_diagram(map<pair<string, int>, string> &mp)
{
    cout << "Transition Tree : \n";
    for (auto e : mp)
    {
        cout << e.first.first << "---(" << e.first.second <<")---->"<< e.second << '\n';
    }
    cout << endl;
}

vector<vector<int>> cycles;
map<string, set<vector<int>>> universal_map_cycles;

void greedy_cycles_print(set<vector<int>>&s) {
    string fnl="[";
    for(vector<int>v:s) {
        string s="{";
        for(int e:v) {
            s.push_back(e+'0');
            s.push_back(',');
        }
        if(!s.empty()) s.pop_back();
        s.push_back('}');
        fnl+=s;
        fnl.push_back(',');
    }

    if(!fnl.empty()) fnl.pop_back();
    fnl.push_back(']');
    cout<<fnl<<endl;

}


vector<int> get_greddy_cycle(string s,int mn) {
    set<vector<int>>v=universal_map_cycles[s];
    vector<int>f;
    for(vector<int>u:v) {
        for(int e:u) {
            if(e==mn) return u;
        }
    }
    return f;
}

void greedy_cycles(map<string, set<int>> &adjacancy_map) {
    set<vector<int>>s;
    for(auto e:adjacancy_map) {
        int mn=*e.second.begin();
        vector<int>temp=get_greddy_cycle(e.first,mn);
        if(!temp.empty()) s.insert(temp);
    }

    greedy_cycles_print(s);

    double mn=INT8_MAX;
    for(vector<int>u:s) {
        double sum=0.000;
        for(int e:u) sum+=e;
        sum=sum/u.size();

        mn=mn<sum?mn:sum;
    }

    cout<<"Minimal Average Latancy = "<<mn<<endl;
    
}

void print_simple_cycles() {
    set<vector<int>>s;
    for(vector<int>v:cycles) {
      s.insert(v);
    }

    string fnl="[";
    for(vector<int>v:s) {
        string s="{";
        for(int e:v) {
            s.push_back(e+'0');
            s.push_back(',');
        }
        if(!s.empty()) s.pop_back();
        s.push_back('}');
        fnl+=s;
        fnl.push_back(',');
    }

    if(!fnl.empty()) fnl.pop_back();
    fnl.push_back(']');
    cout<<fnl<<endl;

}

void simple_cycles(
    map<pair<string, int>, string> &mp,
    map<string, set<int>> &adjacancy_map,
    string curr_state,
    map<string, bool> vis,
    vector<int> cycle)
{
    if (vis[curr_state])
    {
        universal_map_cycles[curr_state].insert(cycle);
        cycles.emplace_back(cycle);
    }
    else
    {
        for (int e : adjacancy_map[curr_state])
        {
            pair<string, int> pr = {curr_state, e};
            string next_state = mp[pr];
            vis[curr_state] = true;
            if (next_state == curr_state)
            {
                vector<int> temp;
                temp.push_back(e);
                universal_map_cycles[curr_state].insert(temp);
                cycles.emplace_back(temp);
            }
            else
            {
                cycle.emplace_back(e);
                simple_cycles(mp, adjacancy_map, next_state, vis, cycle);
                vis[curr_state] = false;
                cycle.pop_back();
            }
        }
    }
}
void transition_diagram(bitset<bitsize> &icv)
{
    map<pair<string, int>, string> mp;
    string initial_collison_vector = icv.to_string();
    stack<string> stk;
    stk.push(initial_collison_vector);
    map<string, bool> vis;
    while (!stk.empty())
    {
        string curr_vector = stk.top();
        if (!vis[curr_vector])
        {
            vis[curr_vector] = true;
            vector<int> position_vector = get_position_vector(curr_vector);
            bitset<bitsize> curr(curr_vector);
            for (int e : position_vector)
            {
                string next_state = get_next_state(icv, curr, e);
                pair<string, int> pr = {curr_vector, e};
                mp[pr] = next_state;
                stk.push(next_state);
            }
        }
        stk.pop();
    }
    print_transition_diagram(mp);
    map<string, set<int>> adjacancy_map;
    for (auto e : mp)
    {
        adjacancy_map[e.first.first].insert(e.first.second);
    }

    map<string, bool> vis_temp;
    vector<int> cycle;
    simple_cycles(mp, adjacancy_map, initial_collison_vector, vis_temp, cycle);
    cout<<"Simple Cycles = ";
    print_simple_cycles();
    cout<<"\n";
    cout<<"Greedy Cycles = ";
    greedy_cycles(adjacancy_map);
    cout<<"\n";
}
void non_linear_pipeline()
{
    vector<vector<int>> g = {
        {1, 0, 0, 0, 0, 1, 0, 1},
        {0, 1, 0, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 1, 0}};

    Latancies u = get_latancies(g);      // Latancies
    vector<int> v = collision_vector(u); // Collison vector
    bitset<bitsize> icv(convert_vector_to_string(v));
    print_latancies(u);
    cout << "\nInitial Collision Vector = " << icv;
    cout <<"\n\n";
    transition_diagram(icv);
    cout<<'\n';

}


int main()
{
    non_linear_pipeline();
    return 0;
}