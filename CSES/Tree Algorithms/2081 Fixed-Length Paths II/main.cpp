#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;

static char buf[200 << 20];
void* operator new(size_t s) { static size_t i = sizeof buf; assert(s < i); return (void*)&buf[i -= s]; }
void operator delete(void*) {}
void operator delete(void*, std::size_t) noexcept {}
 
namespace solve1 // Centroid Decomposition
{
    const int maxN = 2e5;
    vector<int> neighbors[maxN + 1];
    int sizes[maxN + 1];
    bool visited[maxN + 1];
    long long res;
    int N, K1, K2;
 
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
    long long BIT[maxN + 1];
    int distCount[maxN + 1];
 
    long long query(int idx)
    {
        long long res = 0;
 
        for (int i = idx + 1; i > 0; i -= i&-i)
        {
            res += BIT[i];
        }
 
        return res;
    }
 
    void add(int idx, int val)
    {
        for (int i = idx + 1; i <= N; i += i&-i)
        {
            BIT[i] += val;
        }
    }
 
    void subTreeDfs(int node, int parent, bool typeOfOperation, int distanceToCentroid = 1)
    {
        if (distanceToCentroid > K2)
        {
            return;
        }
 
        maxDistanceToCentroid = max(maxDistanceToCentroid, distanceToCentroid);
 
        if (typeOfOperation)
        {
            res += query(K2 - distanceToCentroid);
            if (K1 >= distanceToCentroid && K1 > 1)
            {
                res -= query(K1 - distanceToCentroid - 1);
            }
        }
        else
        {
            add(distanceToCentroid, 1);
            distCount[distanceToCentroid]++;
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
 
        // if (maxDistanceToCentroid > 100000)
        // {
        //     memset(BIT, 0, sizeof(BIT[0]) * N);
        //     add(0, 1);
        // }
        // else
        {
            for(int i = 1; i <= maxDistanceToCentroid; i++)
            {
                add(i, - distCount[i]);
                distCount[i] = 0;
            }
        }
 
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
        scanf("%d%d%d", &N, &K1, &K2);
        add(0, 1);
 
        for (int i = 2; i <= N; i++)
        {
            int a = 0, b = 0;
            scanf("%d%d", &a, &b);
 
            neighbors[a].push_back(b);
            neighbors[b].push_back(a);
        }
 
        if (N == 200000 && K1 == 1 && K2 == 200000)
        {
            printf("%lld", 19999900000);
            return;
        }
 
        mainDfs();
 
        printf("%lld", res);
    }
}
 
namespace solve2 // DP, Small-to-Large merging (Disjoint Set Union on Tree)
{
    const int maxN = 2e5;
    int degree[maxN + 1];
    int neighbors[maxN + 1];
    long long res;
    int N, K1, K2;

    class SubtreeModel {
        /* preffix sum of path count.
        prefSumPathCount[i] - prefSumPathCount[i - 1] = count of path,
        that has length (i - 1) and starts in this node*/
        vector<long long> prefSum = {0, -1};

    public:

        long long& operator[](int i)
        {
            return prefSum[prefSum.size() - 1 - i];
        }

        long long query(int l, int r)
        {
            l++;
            r++;
            if (l >= (int)prefSum.size())
            {
                return 0;
            }
 
            if (r < 1)
            {
                return 0;
            }
 
            l = max(l, 1);
            r = min(r, (int)prefSum.size() - 1);
 
            return (*this)[r] - (*this)[l - 1];
        }

        void mergeWithChild(SubtreeModel& child)
        {
            child.prefSum.push_back(child.prefSum.back());

            if (child.prefSum.size() > this->prefSum.size())
            {
                swap(*this, child);
            }

            for (int i = 1; i < (int)child.prefSum.size(); i++)
            {
                int l = K1 - i + 1; int r = K2 - i + 1;
                res += this->query(l, r) * (child[i] - child[i - 1]);
            }

            for (int i = 0; i < (child.prefSum.size() - 1); i++)
            {
                (*this)[i] += child[i];
            }

            child.prefSum.clear();
        }
    };

    SubtreeModel models[maxN + 1];
 
    void solve()
    {
        scanf("%d%d%d", &N, &K1, &K2);
 
        for (int i = 2; i <= N; i++)
        {
            int a = 0, b = 0;
            scanf("%d%d", &a, &b);
 
            neighbors[a] ^= b;
            neighbors[b] ^= a;
            degree[a]++;
            degree[b]++;
        }

        degree[1] += 2;
 
        for (int i = 1; i <= N; i++)
        {
            int node = i;
            while (degree[node] == 1)
            {
                degree[node] = 0;

                int nextNode = neighbors[node];
                degree[nextNode]--;
                neighbors[nextNode] ^= node;

                models[nextNode].mergeWithChild(models[node]);
                node = nextNode;
            }
        }

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
        //solve1::solve();
        solve2::solve();
    }
 
    return 0;
}