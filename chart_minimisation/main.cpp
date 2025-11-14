#include "../include/utils.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

int MinCharts(const vector<vector<int>> &stock_data)
{
    int num_stocks = stock_data.size();
    vector<vector<int>> adj_list(2 * num_stocks);

    // Build graph: edge from i to j if stock i is strictly less than stock j
    for (int i = 0; i < num_stocks; i++)
    {
        for (int j = 0; j < num_stocks; j++)
        {
            if (i != j && compare(stock_data[i], stock_data[j]))
            {
                adj_list[i].push_back(num_stocks + j);
            }
        }
    }

    vector <int> Left(num_stocks);
    vector <int> Right(num_stocks);

    for (int i = 0; i<num_stocks; i++) {
        Left.push_back(i);
        Right.push_back(i+num_stocks);
    }

    vector <int> cover = Utils::vertex_cover_bipartite_LR_present(adj_list, Left, Right);
}

bool compare(const vector<int> &stock1, const vector<int> &stock2)
{
    for (int i = 0; i < stock1.size(); ++i)
        if (stock1[i] >= stock2[i])
            return false;
    return true;
}

int main()
{
    int num_stocks, num_points;

    cin >> num_stocks >> num_points;

    vector<vector<int>> stock_data(num_stocks, vector<int>(num_points));
    for (int i = 0; i < num_stocks; ++i)
        for (int j = 0; j < num_points; ++j)
        {
            cin >> stock_data[i][j];
        }
    
    MinCharts(stock_data);
}