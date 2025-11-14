#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <unordered_set>

using namespace std;

bool bpm(int u, const vector<vector<int>> &adj_list, vector<bool> &visited, vector<int> &match_to_right)
{
    int num_right = adj_list.size();
    for (auto v : adj_list[u])
    {
        if (!visited[v])
        {
            visited[v] = true;
            if (match_to_right[v] == -1 || bpm(match_to_right[v], adj_list, visited, match_to_right))
            {
                match_to_right[v] = u;
                return true;
            }
        }
    }
    return false;
}

vector<int> FindMatching(const vector<vector<int>> &adj_list)
{
    int num_ver = adj_list.size();
    vector<int> matching(num_ver, -1);
    vector<int> match_to_right(num_ver, -1);

    for (int u = 0; u < num_ver; u++)
    {
        vector<bool> visited(num_ver, false);
        bpm(u, adj_list, visited, match_to_right);
    }

    for (int v = 0; v < num_ver; v++)
    {
        if (match_to_right[v] != -1)
        {
            matching[match_to_right[v]] = v;
        }
    }
    return matching;
}

vector <int> vertex_cover_bipartite (const vector<vector<int>> &adj_list) {
    vector <int> matching = FindMatching(adj_list);
    vector <int> cover;
    for (int i = 0; i<matching.size(); i++) {
        if (matching[i] != -1) {
            cover.push_back(i);
        }
    }
    return cover;
}

int main()
{
    int num_ver;
    int num_edg;

    cin >> num_ver >> num_edg;

    vector<vector<int>> adj_list(num_ver, vector<int>());

    for (int i = 0; i < num_edg; i++)
    {
        int u, v;
        cin >> u >> v;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }
    vertex_cover_bipartite(adj_list);
}
