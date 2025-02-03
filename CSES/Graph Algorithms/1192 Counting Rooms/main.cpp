#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class UnionFind {
    vector<int> rank, parent;

public:
    UnionFind(int n) {
        rank.resize(n, 0);
        parent.resize(n);

        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool connect(int x, int y) {
        int xRoot = find(x);
        int yRoot = find(y);

        if (xRoot == yRoot) {
            return false;
        }

        // Union by rank
        if (rank[xRoot] < rank[yRoot]) {
            parent[xRoot] = yRoot;
        }
        else if (rank[yRoot] < rank[xRoot]) {
            parent[yRoot] = xRoot;
        }
        else {
            parent[yRoot] = xRoot;
            rank[xRoot]++;
        }

        return true;
    }

    bool connected(int x, int y)
    {
        return find(x) == find(y);
    }
};

void solve() {
    int row = 0, col = 0;
    cin >> row >> col;

    char map[row][col] = {};

    UnionFind un(row * col);

    int res = 0;

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cin >> map[i][j];

            if (map[i][j] != '.')
            {
                continue;
            }

            res++;

            if (i > 0 && map[i - 1][j] == '.')
            {
                un.connect(i * col + j, (i - 1) * col + j);
                res--;
            }

            if (j > 0 && map[i][j - 1] == '.')
            {
                bool roomsConnection = un.connect(i * col + j, i * col + j - 1);
                
                if (roomsConnection)
                {
                    res--;
                }
            }
        }
    }
    
    cout << res << endl;
}


int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    long long testsNumber = 1;

    //cin >> testsNumber;

    for (int i = 0; i < testsNumber; i++)
    {
        solve();
    }

    return 0;
}