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
    

    // to find matchng from left to right
    static vector<int> find_matching(const vector<vector<int>> &graph, const vector<int> &left, const vector<int> &right) {

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
    
}