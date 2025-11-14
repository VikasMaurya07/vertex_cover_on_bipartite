#include "../include/utils.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

// compare: true if stock1 < stock2 componentwise (strictly)
bool compare(const vector<int> &stock1, const vector<int> &stock2)
{
    if (stock1.size() != stock2.size()) return false;
    for (size_t i = 0; i < stock1.size(); ++i)
        if (stock1[i] >= stock2[i])
            return false;
    return true;
}

// returns groups (each group is a chain of stock indices)
vector<vector<int>> MinCharts(const vector<vector<int>> &stock_data)
{
    int n = (int)stock_data.size();
    if (n == 0) return {};

    // Build bipartite adjacency: left 0..n-1, right n..2n-1 (original ids)
    vector<vector<int>> adj(2 * n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            if (compare(stock_data[i], stock_data[j])) {
                // edge left(i) -> right(j) represented as index (n + j)
                adj[i].push_back(n + j);
            }
        }
    }

    // Build left and right lists of original ids (for Utils API)
    vector<int> left, right;
    left.reserve(n); right.reserve(n);
    for (int i = 0; i < n; ++i) {
        left.push_back(i);
        right.push_back(n + i); // note right vertices are stored as original ids offset by n
    }

    // Use utils to find matching: match_left_org[u_left_orig] = v_right_orig (or -1)
    vector<int> match_left_org = Utils::find_matching(adj, left, right);
    // match_left_org is sized 2n (graph.size()), entries for left-original indices (0..n-1) give matched right-original id (n+j) or -1

    // Build successor mapping succ[u] = v where u -> v in chain (using original stock ids 0..n-1)
    // For left original id u (0..n-1), match_left_org[u] either -1 or equals (n + v)
    vector<int> succ(n, -1);
    vector<int> pred(n, -1); // reverse link to find starts
    int matching_size = 0;
    for (int u = 0; u < n; ++u) {
        int v_orig = match_left_org[u]; // this should be either -1 or n+v
        if (v_orig != -1) {
            int v = v_orig - n;
            if (v >= 0 && v < n) {
                succ[u] = v;
                pred[v] = u;
                ++matching_size;
            }
        }
    }

    // Number of chains = n - matching_size

    // Build chains by starting at nodes with no predecessor (pred == -1)
    vector<vector<int>> chains;
    vector<char> used(n, 0);
    for (int u = 0; u < n; ++u) {
        if (pred[u] == -1) { // start of a chain
            int cur = u;
            vector<int> chain;
            while (cur != -1 && !used[cur]) {
                chain.push_back(cur);
                used[cur] = 1;
                cur = succ[cur];
            }
            if (!chain.empty())
                chains.push_back(move(chain));
        }
    }

    // In case of cycles or leftover nodes (shouldn't happen in strict partial order),
    // add any remaining unused nodes as singleton chains.
    for (int u = 0; u < n; ++u) {
        if (!used[u]) {
            chains.push_back(vector<int>{u});
        }
    }

    // Debug print (optional): Uncomment for verification
    // cout << "n=" << n << " matching_size=" << matching_size << " min_chains=" << (n - matching_size) << "\n";

    return chains;
}

vector<vector<int>> MinCharts(const vector<vector<int>> &stock_data);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        int num_stocks, num_points;
        if (!(cin >> num_stocks >> num_points)) break;

        // read one test case: num_stocks lines, each with num_points integers
        vector<vector<int>> stock_data(num_stocks, vector<int>(num_points));
        for (int i = 0; i < num_stocks; ++i) {
            for (int j = 0; j < num_points; ++j) {
                cin >> stock_data[i][j];
            }
        }

        // compute groups (chains)
        vector<vector<int>> groups = MinCharts(stock_data);

        // Emit machine-readable block for Python
        // Header
        cout << "PRINT_CASE " << num_stocks << " " << num_points << "\n";

        // Print stock rows: one row per stock with space-separated values
        for (int i = 0; i < num_stocks; ++i) {
            for (int j = 0; j < num_points; ++j) {
                if (j) cout << ' ';
                cout << stock_data[i][j];
            }
            cout << "\n";
        }

        // Print groups
        cout << "PRINT_GROUPS " << groups.size();
        for (auto &g : groups) {
            cout << " | " << g.size();
            for (int v : g) cout << " " << v;
        }
        cout << "\n";
    }

    return 0;
}
