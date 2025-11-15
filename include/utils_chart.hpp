#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <unordered_set>
#include <stack>
#include <functional>

using namespace std;

namespace Utils_Chart
{
    // Build successor mapping succ[u] = v where u -> v in chain (using original stock ids 0..n-1)
    // For left original id u (0..n-1), match_left_org[u] either -1 or equals (n + v)
    static vector<vector<int>> build_chain(int stock_size, vector<int> &matching)
    {
        vector<int> succ(stock_size, -1);
        vector<int> pred(stock_size, -1);
        int match_size = 0;
        for (int u = 0; u < stock_size; u++)
        {
            int v_org = matching[u];
            if (v_org != -1)
            {
                int v = v_org - stock_size;
                if (v >= 0 && v < stock_size)
                {
                    succ[u] = v;
                    pred[v] = u;
                    match_size++;
                }
            }
        }

        int num_chains = stock_size - match_size;

        // Build chart chains by starting at nodes with no predecessor (pred == -1)

        vector<vector<int>> chains;
        vector<bool> used(stock_size, false);
        for (int u = 0; u < stock_size; u++)
        {
            if (pred[u] == -1)
            { // start of a chain
                int curr = u;
                vector<int> chain;
                while (curr != -1 && !used[curr])
                {
                    chain.push_back(curr);
                    used[curr] = true;
                    curr = succ[curr];
                }
                if (!chain.empty())
                {
                    chains.push_back(move(chain));
                }
            }
        }

        // In case of cycles or leftover nodes (shouldn't happen in strict partial order),
        // add any remaining unused nodes as singleton chains.
        for (int u = 0; u < stock_size; ++u)
        {
            if (!used[u])
            {
                chains.push_back(vector<int>{u});
            }
        }

        if (chains.size() != num_chains) {
            return {};
        }

        else {
            return chains;
        }
    }

};