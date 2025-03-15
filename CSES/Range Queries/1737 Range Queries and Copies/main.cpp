#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1
{
    const int maxN = 2e5;
    
    struct NodeData
    {
        int lNodeId = 0;
        int rNodeId = 0;
        int lBound = 0, rBound = 0;
        long long sum = 0;
    };

    NodeData Storage[50*maxN];

    int N, Q;
    int arrayNumber = 0;
    int nodeCount = 1;
    int arrayToRootNode[maxN + 1];

    void pull(int nodeId)
    {
        auto val = Storage[Storage[nodeId].lNodeId].sum + Storage[Storage[nodeId].rNodeId].sum;
        Storage[nodeId].sum = Storage[Storage[nodeId].lNodeId].sum + Storage[Storage[nodeId].rNodeId].sum;
    }

    long long querySumNode(int l, int r, int nodeId)
    {
        NodeData& data = Storage[nodeId];

        if (r < data.lBound || l > data.rBound)
        {
            return 0;
        }

        if (l <= data.lBound && r >= data.rBound)
        {
            return data.sum;
        }

        return querySumNode(l, r, data.lNodeId) + querySumNode(l, r, data.rNodeId);
    }

    long long querySumArray(int l, int r, int arrayId)
    {
        return querySumNode(l, r, arrayToRootNode[arrayId]);
    }

    int createNode()
    {
        nodeCount++;
        return nodeCount;
    }

    int copyNode(int srcNode)
    {
        nodeCount++;
        Storage[nodeCount] = Storage[srcNode];
        return nodeCount;
    }

    void createArray(int parentArrayId)
    {
        arrayNumber++;
        arrayToRootNode[arrayNumber] = copyNode(arrayToRootNode[parentArrayId]);
    }

    void init(int nodeId = 1, int l = 1, int r = N)
    {
        Storage[nodeId].lBound = l;
        Storage[nodeId].rBound = r;

        if (l == r)
        {
            int val = 0;
            scanf("%d", &val);

            Storage[nodeId].sum = val;
            return;
        }

        int m = (l + r) / 2;

        Storage[nodeId].lNodeId = createNode();
        Storage[nodeId].rNodeId = createNode();

        init(Storage[nodeId].lNodeId, l, m);
        init(Storage[nodeId].rNodeId, m + 1, r);

        pull(nodeId);
    }

    void updateNode(int idx, int val, int nodeId)
    {
        NodeData& data = Storage[nodeId];

        if (data.lBound == data.rBound)
        {
            data.sum = val;
            return;
        }

        bool toLeft = idx <= Storage[data.lNodeId].rBound;
        int childNodeId = toLeft ? data.lNodeId : data.rNodeId;

        int newChildId = copyNode(childNodeId);

        if (toLeft)
        {
            data.lNodeId = newChildId;
            updateNode(idx, val, newChildId);
        }
        else
        {
            data.rNodeId = newChildId;
            updateNode(idx, val, newChildId);
        }

        pull(nodeId);
    }

    void update(int idx, int val, int arrayId)
    {
        updateNode(idx, val, arrayToRootNode[arrayId]);
    }

    // void printTree()
    // {
    //     //return;

    //     int treeWidth = 1;
    //     while (treeWidth < N) treeWidth <<= 1;

    //     for (int node = 1; node < 2*treeWidth; node++)
    //     {
    //         if ((node&(node-1)) == 0)
    //         {
    //             printf("\n");
    //         }
    //         printf("%lld ", sumTree[node]);
    //     }
    //     printf("\n");
    // }

    void solve() {
        scanf("%d%d", &N, &Q);

        init();

        arrayToRootNode[0] = 1;
        createArray(0);

        //printTree();
        
        for (int i = 1; i <= Q; i++)
        {
            int t = 0, arrayId = 0;
            scanf("%d%d", &t, &arrayId);

            if (t == 1)
            {
                int idx = 0, val = 0;
                scanf("%d%d", &idx, &val);
                update(idx, val, arrayId);
            }
            else if (t == 2)
            {
                int l = 0, r = 0;
                scanf("%d%d", &l, &r);
                long long res = querySumArray(l, r, arrayId);
                printf("%lld\n", res);
            }
            else if (t == 3)
            {
                createArray(arrayId);
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
        solve1::solve();
    }

    return 0;
}