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
    static void build_left_adj(const vector<vector<int>> &graph, const vector<int> &left, const vector<int> &right, vector<vector<int>> &adj_left, vector<int> &right_indices);
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
                        cols[neigh] = col;
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

        // map back to original ids
        vector<int> match_left_org(graph.size(), -1);
        for (int i = 0; i < L; i++)
        {
            if (matchL[i] != -1)
            {
                int u_org = left[i];
                int v_org = right[matchL[i]];
                match_left_org[u_org] = v_org;
            }
        }
        return match_left_org;
    }

    // finding the minimum vertex cover from the given bipartite matching  (König's theorem)
    static vector<int> minimum_vertex_cover(const vector<vector<int>> &graph, vector<int> &left, vector<int> &right, vector<int> &matching)
    {
        vector<vector<int>> adj_left;
        vector<int> right_indices;
        build_left_adj(graph, left, right, adj_left, right_indices);

        int L = (int)left.size();
        int R = (int)right.size();
        vector<int> matchR(R, -1), matchL(L, -1);

        for (int i = 0; i < L; i++)
        {
            int u_org = left[i];
            int v_org = matching[u_org];

            if (v_org != -1)
            {
                int v_id = right_indices[v_org];

                if (v_id != -1)
                {
                    matchL[i] = v_id;
                    matchR[v_id] = i;
                }
            }
        }
        // Start DFS from unmatched left vertices using alternating (non-matching then matching) edges
        vector<bool> visL(L, 0), visR(R, 0);
        stack<int> st;

        for (int i = 0; i < L; i++)
        {
            if (matchL[i] == -1)
            {
                st.push(i);
                visL[i] = 1;
            }
        }

        while (!st.empty())
        {
            int u = st.top();
            st.pop();
            for (int v_id : adj_left[u])
            {
                // we traverse only edges not in matching from left -> right
                if (matchL[u] == v_id)
                    continue; // traverse only non matched edges
                if (!visR[v_id])
                {
                    visR[v_id] = 1;
                    // from right, follow the matching edge (if present) back to left
                    if (matchR[v_id] != -1 && !visL[matchR[v_id]])
                    {
                        visL[matchR[v_id]] = 1;
                        st.push(matchR[v_id]);
                    }
                }
            }
        }
        // Min vertex cover = (all left vertices NOT visited) U (all right vertices visited)
        vector<int> cover;
        for (int i = 0; i < L; ++i)
        {
            if (!visL[i])
                cover.push_back(left[i]); // original id
        }
        for (int j = 0; j < R; ++j)
        {
            if (visR[j])
                cover.push_back(right[j]); // original id
        }
        return cover;
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
        // compute min vertex cover using the matching
        vector<int> cover = minimum_vertex_cover(graph, left, right, matching);
        return cover;
    }

    // If left and right subgraphs are provided by the user itself
    static vector<int> vertex_cover_bipartite_LR_present(const vector<vector<int>> &graph, vector<int> left, vector<int> right)
    {
        int n = (int)graph.size();

        // --- Basic validation: indices in range ---
        for (int u : left)
        {
            if (u < 0 || u >= n)
            {
                cout << "Invalid vertex in left: " << u << "\n";
                return {};
            }
        }
        for (int u : right)
        {
            if (u < 0 || u >= n)
            {
                cout << "Invalid vertex in right: " << u << "\n";
                return {};
            }
        }

        // --- Check duplicates inside left/right and build membership sets ---
        unordered_set<int> setL, setR;
        for (int u : left)
        {
            if (!setL.insert(u).second)
            {
                cout << "Duplicate vertex in left: " << u << "\n";
                return {};
            }
        }
        for (int u : right)
        {
            if (!setR.insert(u).second)
            {
                cout << "Duplicate vertex in right: " << u << "\n";
                return {};
            }
        }

        // --- Check overlap between left and right ---
        for (int u : left)
        {
            if (setR.count(u))
            {
                cout << "Vertex " << u << " appears in both left and right sets.\n";
                return {};
            }
        }

        // --- Check for internal edges within left or within right ---
        // If any edge (u,v) exists with both endpoints in left or both in right -> invalid partition
        for (int u : left)
        {
            for (int v : graph[u])
            {
                if (setL.count(v))
                {
                    cout << "Invalid partition: edge " << u << " - " << v << " is inside left set.\n";
                    return {};
                }
            }
        }
        for (int u : right)
        {
            for (int v : graph[u])
            {
                if (setR.count(v))
                {
                    cout << "Invalid partition: edge " << u << " - " << v << " is inside right set.\n";
                    return {};
                }
            }
        }

        // --- Good partition: compute maximum matching and minimum vertex cover ---
        vector<int> matching = find_matching(graph, left, right);
        vector<int> cover = minimum_vertex_cover(graph, left, right, matching);
        return cover;
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
                    adj_left[i].push_back(rv);
            }
        }
    }
}