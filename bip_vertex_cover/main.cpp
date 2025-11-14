#include "../include/utils.hpp"
using namespace std;

int main() {
    while (true) {
        int num_ver, num_edg;

        // break on EOF
        if (!(cin >> num_ver >> num_edg)) break;

        if (num_ver == 0) {
            cout << "PRINT_GRAPH 0 0\n";
            cout << "PRINT_COVER 0\n";
            continue;
        }

        vector<vector<int>> adj_list(num_ver);
        vector<pair<int,int>> edges;

        for (int i = 0; i < num_edg; i++) {
            int u, v;
            cin >> u >> v;
            adj_list[u].push_back(v);
            adj_list[v].push_back(u);
            edges.push_back({u, v});
        }

        // print graph info for Python
        cout << "PRINT_GRAPH " << num_ver << " " << num_edg << "\n";
        for (auto &e : edges) {
            cout << e.first << " " << e.second << "\n";
        }

        vector<int> cover = Utils::vertex_cover_bipartite(adj_list);

        // print cover for Python
        cout << "PRINT_COVER " << cover.size();
        for (int v : cover) cout << " " << v;
        cout << "\n";
    }

    return 0;
}
