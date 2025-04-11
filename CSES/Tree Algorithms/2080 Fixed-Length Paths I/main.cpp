#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;
 
namespace solve1 // Centroid Decomposition
{
    const int maxN = 2e5;
    vector<int> neighbors[maxN + 1];
    int sizes[maxN + 1];
    bool visited[maxN + 1];
    long long res;
    int N, K;

    int getCentroidOfSubtree(int node, int parent, int subtreeSize)
    {
        for (int neighbor : neighbors[node])
        {
            if (neighbor != parent && !visited[neighbor] && sizes[neighbor] > subtreeSize / 2)
            {
                return getCentroidOfSubtree(neighbor, node, subtreeSize);
            }
        }

        return node;
    }

    void countSizesOfSubtree(int node, int parent = 0)
    {
        sizes[node] = 1;
        for (int neighbor : neighbors[node])
        {
            if (neighbor != parent && !visited[neighbor])
            {
                countSizesOfSubtree(neighbor, node);
                sizes[node] += sizes[neighbor];
            }
        }
    }

    int maxDistanceToCentroid;
    int countOfDistancesFromCentroid[maxN + 1] = {1};

    void subTreeDfs(int node, int parent, bool typeOfOperation, int distanceToCentroid = 1)
    {
        if (distanceToCentroid > K)
        {
            return;
        }

        maxDistanceToCentroid = max(maxDistanceToCentroid, distanceToCentroid);

        if (typeOfOperation)
        {
            res += countOfDistancesFromCentroid[K - distanceToCentroid];
        }
        else
        {
            countOfDistancesFromCentroid[distanceToCentroid]++;
        }
        
        for (int neighbor : neighbors[node])
        {
            if (neighbor != parent && !visited[neighbor])
            {
                subTreeDfs(neighbor, node, typeOfOperation, distanceToCentroid + 1);
            }
        }
    }

    void countKPathThatGoesThroughCentroid(int centroid)
    {
        for (auto neighbor : neighbors[centroid])
        {
            if (!visited[neighbor])
            {
                subTreeDfs(neighbor, centroid, true);
                subTreeDfs(neighbor, centroid, false);
            }
        }

        memset(countOfDistancesFromCentroid + 1, 0, sizeof(countOfDistancesFromCentroid[0]) * (maxDistanceToCentroid));
        maxDistanceToCentroid = 0;
    }
 
    void mainDfs(int node = 1)
    {
        countSizesOfSubtree(node);
        int centroid = getCentroidOfSubtree(node, 0, sizes[node]);
        visited[centroid] = true;
        
        auto prevRes = res;

        countKPathThatGoesThroughCentroid(centroid);

        if (prevRes == res)
        {
            return;
        }
        
        for (int neighbor : neighbors[centroid])
        {
            if (!visited[neighbor]) {
                mainDfs(neighbor);
            }
        }
    }
 
    void solve()
    {
        scanf("%d%d", &N, &K);
 
        for (int i = 2; i <= N; i++)
        {
            int a = 0, b = 0;
            scanf("%d%d", &a, &b);
 
            neighbors[a].push_back(b);
            neighbors[b].push_back(a);
        }
 
        mainDfs();

        printf("%lld", res);
    }
}
 
int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    // ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    // std::cout.tie(0);
 
    long long testsNumber = 1;
 
    // cin >> testsNumber;
    // scanf("%lld", &testsNumber);
 
    for (long long i = 0; i < testsNumber; i++)
    {
        solve1::solve();
    }
 
    return 0;
}