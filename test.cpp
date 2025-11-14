#include "utils.hpp"
using namespace std;

int main() {
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

    vector <int> cover = Utils::vertex_cover_bipartite(adj_list);

    for (auto vetx : cover) {
        cout << vetx << " ";
    }
    cout << endl;

}