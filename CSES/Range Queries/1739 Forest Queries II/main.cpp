#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1
{
    const int maxN = 1000;
    const int treeMaxSize = 4*maxN*maxN + 1;
    int sumTree[treeMaxSize];
    bool grid[maxN + 1][maxN + 1];
    int N, Q, lowerIndex[treeMaxSize][2], higherIndex[treeMaxSize][2], indexToNode[maxN + 1][maxN + 1];

    int query(int x1, int y1, int x2, int y2, int node = 1)
    {
        if (x2 < lowerIndex[node][0] || y2 < lowerIndex[node][1] || x1 > higherIndex[node][0] || y1 > higherIndex[node][1])
        {
            return 0;
        }

        if (x1 <= lowerIndex[node][0] && y1 <= lowerIndex[node][1] && x2 >= higherIndex[node][0] && y2 >= higherIndex[node][1])
        {
            return sumTree[node];
        }

        return query(x1, y1, x2, y2, 2*node) + query(x1, y1, x2, y2, 2*node + 1);
    }

    void pull(int node)
    {
        sumTree[node] = sumTree[2*node] + sumTree[2*node + 1];
    }

    void init(int node = 1, int x1 = 1, int y1 = 1, int x2 = N, int y2 = N)
    {
        lowerIndex[node][0] = x1;
        lowerIndex[node][1] = y1;
        higherIndex[node][0] = x2;
        higherIndex[node][1] = y2;

        if (x1 == x2 && y1 == y2)
        {
            indexToNode[x1][y1] = node;

            sumTree[node] = grid[x1][y1];
            return;
        }

        bool divideByVertical = (x2 - x1) >= (y2 - y1);
        int m = divideByVertical ? (x1 + x2) / 2 : (y1 + y2) / 2;
        
        init(2*node, x1, y1, divideByVertical ? m : x2, divideByVertical ? y2 : m);
        init(2*node + 1, divideByVertical ? m + 1 : x1, divideByVertical ? y1 : m + 1, x2, y2);

        pull(node);
    }

    void update(int x, int y)
    {
        grid[x][y] = !grid[x][y];
        int node = indexToNode[x][y];

        sumTree[node] = grid[x][y];

        while (node >= 2)
        {
            node >>= 1;
            pull(node);
        }
    }

    void printTree()
    {
        //return;
        printf("\n");
        printf("sumTree=\n");
        for (int node = 1; node < 2*N*N; node++)
        {
            if ((node&(node-1)) == 0)
            {
                printf("\n");
            }
            printf("%d ", sumTree[node]);
        }
        printf("\n");
    }

    void solve() {
        scanf("%d%d", &N, &Q);

        for (int y = 1; y <= N; y++)
        {
            for (int x = 1; x <= N; x++)
            {
                char ch = 0;
                scanf(" %c ", &ch);

                if (ch == '*')
                {
                    grid[x][y] = 1;
                }
            }
        }
        

        init();

        //printTree();
        
        for (int i = 1; i <= Q; i++)
        {
            int t = 0;
            scanf("%d", &t);
            
            int x1 = 0, y1 = 0;
            scanf("%d%d", &y1, &x1);

            if (t == 1)
            {
                update(x1, y1);
            }
            else if (t == 2)
            {
                int x2 = 0, y2 = 0;
                scanf("%d%d", &y2, &x2);
                
                int sum = query(x1, y1, x2, y2);

                printf("%d\n", sum);
            }
        }
    }
}

namespace solve2
{
    const int maxN = 1000;
    int BIT[maxN + 1][maxN + 1], prefSum[maxN + 1][maxN + 1];
    bool grid[maxN + 1][maxN + 1];
    int N, Q;

    int query(int x, int y)
    {
        int res = 0;
        for (int i = y; i > 0; i -= i&-i)
        {
            for (int j = x; j > 0; j -= j&-j)
            {
                res += BIT[j][i];
            }
        }

        return res;
    }

    int query(int x1, int y1, int x2, int y2)
    {
        return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
    }

    void init()
    {
        for (int y = N; y > 0; y--)
        {
            for (int x = N; x > 0; x--)
            {
                BIT[x][y] = prefSum[x][y] - prefSum[x - (x&-x)][y] - prefSum[x][y - (y&-y)] + prefSum[x - (x&-x)][y - (y&-y)];
            }
        }
    }

    void update(int x, int y)
    {
        grid[x][y] = !grid[x][y];

        int add = grid[x][y] ? 1 : -1;

        for (int i = y; i <= N; i += i&-i)
        {
            for (int j = x; j <= N; j += j&-j)
            {
                BIT[j][i] += add;
            }
        }
    }

    // void printTree()
    // {
    //     //return;
    //     printf("\n");
    //     printf("sumTree=\n");
    //     for (int node = 1; node < 2*N*N; node++)
    //     {
    //         if ((node&(node-1)) == 0)
    //         {
    //             printf("\n");
    //         }
    //         printf("%d ", sumTree[node]);
    //     }
    //     printf("\n");
    // }

    void solve() {
        scanf("%d%d", &N, &Q);

        for (int y = 1; y <= N; y++)
        {
            for (int x = 1; x <= N; x++)
            {
                char ch = 0;
                scanf(" %c ", &ch);

                if (ch == '*')
                {
                    grid[x][y] = 1;
                }

                prefSum[x][y] = grid[x][y] + prefSum[x-1][y] + prefSum[x][y-1] - prefSum[x-1][y-1];
            }
        }

        init();

        //printTree();
        
        for (int i = 1; i <= Q; i++)
        {
            int t = 0;
            scanf("%d", &t);
            
            int x1 = 0, y1 = 0;
            scanf("%d%d", &y1, &x1);

            if (t == 1)
            {
                update(x1, y1);
            }
            else if (t == 2)
            {
                int x2 = 0, y2 = 0;
                scanf("%d%d", &y2, &x2);
                
                int sum = query(x1, y1, x2, y2);

                printf("%d\n", sum);
            }
        }
    }
}

namespace solve3
{
    const int maxN = 1000;
    const int treeMaxSize = 4*maxN + 1;
    int sumTree[treeMaxSize][treeMaxSize];
    bool grid[maxN + 1][maxN + 1];
    int N, Q, boundaries[treeMaxSize][2], indexToNode[maxN + 1];

    int query(int x1, int y1, int x2, int y2, int nodeRow = 1, int nodeColumn = 1, bool insideRowRange = false)
    {
        if (x2 < boundaries[nodeRow][0] || x1 > boundaries[nodeRow][1] || y2 < boundaries[nodeColumn][0] || y1 > boundaries[nodeColumn][1])
        {
            return 0;
        }

        insideRowRange = insideRowRange ? true : (x1 <= boundaries[nodeRow][0] && x2 >= boundaries[nodeRow][1]);
        bool insideColumnRange = y1 <= boundaries[nodeColumn][0] && y2 >= boundaries[nodeColumn][1];

        if (insideRowRange)
        {
            if (insideColumnRange)
            {
                return sumTree[nodeRow][nodeColumn];
            }

            return query(x1, y1, x2, y2, nodeRow, 2*nodeColumn) + query(x1, y1, x2, y2, nodeRow, 2*nodeColumn + 1, true);
        }

        return query(x1, y1, x2, y2, 2*nodeRow, nodeColumn) + query(x1, y1, x2, y2, 2*nodeRow + 1, nodeColumn, false);
    }

    void pullRow(int nodeRow, int nodeColumn)
    {
        sumTree[nodeRow][nodeColumn] = sumTree[2*nodeRow][nodeColumn] + sumTree[2*nodeRow + 1][nodeColumn];
    }

    void pullColumn(int nodeRow, int nodeColumn)
    {
        sumTree[nodeRow][nodeColumn] = sumTree[nodeRow][2*nodeColumn] + sumTree[nodeRow][2*nodeColumn + 1];
    }

    void initBoundaries(int node = 1, int l = 1, int r = N)
    {
        boundaries[node][0] = l;
        boundaries[node][1] = r;

        if (l == r)
        {
            indexToNode[l] = node;
            return;
        }

        int m = (l + r) / 2;

        initBoundaries(2*node, l, m);
        initBoundaries(2*node + 1, m + 1, r);
    }

    void initColumn(int nodeRow, int nodeColumn = 1)
    {
        if (boundaries[nodeColumn][0] == boundaries[nodeColumn][1])
        {
            if (boundaries[nodeRow][0] == boundaries[nodeRow][1])
            {
                sumTree[nodeRow][nodeColumn] = grid[boundaries[nodeRow][0]][boundaries[nodeColumn][1]];
                return;
            }

            pullRow(nodeRow, nodeColumn);
            return;
        }

        initColumn(nodeRow, 2*nodeColumn);
        initColumn(nodeRow, 2*nodeColumn + 1);
        
        pullColumn(nodeRow, nodeColumn);
    }

    void initRow(int nodeRow = 1)
    {
        if (boundaries[nodeRow][0] == boundaries[nodeRow][1])
        {
            initColumn(nodeRow);
            return;
        }
        
        initRow(2*nodeRow);
        initRow(2*nodeRow + 1);

        initColumn(nodeRow);
    }

    void init()
    {
        initBoundaries();
        initRow();
    }

    void update(int x, int y)
    {
        grid[x][y] = !grid[x][y];
        int nodeRow = indexToNode[x];
        int nodeColumn = indexToNode[y];

        sumTree[nodeRow][nodeColumn] = grid[x][y];

        while (nodeColumn >= 2)
        {
            nodeColumn >>= 1;
            pullColumn(nodeRow, nodeColumn);
        }

        while (nodeRow >= 2)
        {
            nodeRow >>= 1;
            nodeColumn = indexToNode[y];
            
            pullRow(nodeRow, nodeColumn);

            while (nodeColumn >= 2)
            {
                nodeColumn >>= 1;
                pullColumn(nodeRow, nodeColumn);
            }
        }
    }

    void printTree()
    {
        //return;
        printf("\n");
        printf("sumTree=\n");
        for (int node = 1; node < 2*N*N; node++)
        {
            if ((node&(node-1)) == 0)
            {
                printf("\n");
            }
            printf("%d ", sumTree[node]);
        }
        printf("\n");
    }

    void solve() {
        scanf("%d%d", &N, &Q);

        for (int y = 1; y <= N; y++)
        {
            for (int x = 1; x <= N; x++)
            {
                char ch = 0;
                scanf(" %c ", &ch);

                if (ch == '*')
                {
                    grid[x][y] = 1;
                }
            }
        }
        

        init();

        //printTree();
        
        for (int i = 1; i <= Q; i++)
        {
            int t = 0;
            scanf("%d", &t);
            
            int x1 = 0, y1 = 0;
            scanf("%d%d", &y1, &x1);

            if (t == 1)
            {
                update(x1, y1);
            }
            else if (t == 2)
            {
                int x2 = 0, y2 = 0;
                scanf("%d%d", &y2, &x2);
                
                int sum = query(x1, y1, x2, y2);

                printf("%d\n", sum);
            }
        }
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // std::ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    long long testsNumber = 1;

    //cin >> testsNumber;

    for (int i = 0; i < testsNumber; i++)
    {
        //solve1::solve();
        solve2::solve();
        //solve3::solve();
    }

    return 0;
}