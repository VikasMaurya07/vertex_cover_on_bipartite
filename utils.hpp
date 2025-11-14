#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <unordered_set>
#include <stack>
#include <functional>

using namespace std;

namespace Utils
{
    class if_Bipartite
    {
    public:
        // to check if a graph is bip and return the two groups
        // We try 2-coloring on graph
        static tuple<bool, vector<int>, vector<int>> partition(const vector<vector<int>> &graph)
        {
            int n = (int)graph.size();
            vector<int> cols(n, 0); // 0 = unvisited, 1 = left, 2 = right

            // recursive dfs function
            std::function<bool(int)> dfs = [&](int curr) -> bool
            {
                int col = cols[curr] == 1 ? 2 : 1;
                for (int neigh : graph[curr])
                {
                    if (cols[neigh] == 0)
                    {
                        if (!dfs(neigh))
                            return false;
                    }
                    else if (cols[neigh] == cols[curr])
                    {
                        return false;
                    }
                }
                return true;
            };

            for (int i = 0; i < n; i++)
            {
                if (cols[i] == 0)
                {
                    cols[i] = 1; // start this component with color 1
                    if (!dfs(i))
                    {
                        return {false, {}, {}};
                    }
                }
            }

            // build left and right groups
            vector<int> left, right;
            for (int i = 0; i < n; i++)
            {
                if (cols[i] == 1)
                    left.push_back(i);
                else if (cols[i] == 2)
                    right.push_back(i);
            }
            return {true, left, right};
        }
    };

    // Kuhn's algorithm (bipartite matching) on adj_left where left indices are 0..L-1 and right indices are 0..R-1
    static void kuhn_match(const vector<vector<int>> &adj_left, vector<int> &matchR, vector<int> &matchL)
    {
        int L = (int)adj_left.size();
        int R = (int)matchR.size();

        function<bool(int, vector<char> &)> dfs = [&](int u, vector<char> &seen) -> bool
        {
            for (int v : adj_left[u])
            {
                if (seen[v])
                    continue;
                seen[v] = 1;
                if (matchR[v] == -1 || dfs(matchR[v], seen))
                {
                    matchR[v] = u;
                    matchL[u] = v;
                    return true;
                }
            }
            return false;
        };

        for (int u = 0; u < L; ++u)
        {
            vector<char> seen(R, 0);
            dfs(u, seen);
        }
    }

    // to find matchng from left to right
    static vector<int> find_matching(const vector<vector<int>> &graph, const vector<int> &left, const vector<int> &right)
    {
        vector<vector<int>> adj_left;
        vector<int> right_indices;
        build_left_adj(graph, left, right, adj_left, right_indices);

        int L = (int)left.size();
        int R = (int)right.size();
        vector<int> matchR(R, -1), matchL(L, -1);
        kuhn_match(adj_left, matchR, matchL); // provides matching
    }

    // Public API, computing min vertex if graph is bipartite
    static vector<int> vertex_cover_bipartite(const vector<vector<int>> &graph)
    {
        auto [is_bip, left, right] = if_Bipartite ::partition(graph);
        if (!is_bip)
        {
            cout << "Graph is not Bipartite\n";
            return {};
        }

        // compute maximum matching (left->right)
        vector<int> matching = find_matching(graph, left, right);
    }

    ///-------------------------------Helper Functions ------------------------------------------//
    static void build_left_adj(const vector<vector<int>> &graph, const vector<int> &left, const vector<int> &right, vector<vector<int>> &adj_left, vector<int> &right_indices)
    {
        int L = (int)left.size();
        int R = (int)right.size();
        adj_left.assign(L, {});
        right_indices.assign(graph.size(), -1);

        for (int j = 0; j < R; j++)
        {
            right_indices[right[j]] = j;
        }

        for (int i = 0; i < L; i++)
        {
            int u = left[i];
            for (int v : graph[u])
            {
                int rv = -1;
                if (v >= 0 && v < (int)right_indices.size())
                    rv = right_indices[v];
                if (rv != -1)
                    adj_left[u].push_back(rv);
            }
        }
    }
}