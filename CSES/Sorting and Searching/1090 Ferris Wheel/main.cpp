#include <iostream>
#include <bits/stdc++.h>

using namespace std;
 
void solve() {
    int n = 0, x = 0;
    cin >> n >> x;

    std::vector<int> childrenW;
    childrenW.reserve(n);

    for (int i = 0; i < n; i++)
    {
        int weight = 0;
        cin >> weight;
        
        childrenW.emplace_back(weight);
    }

    sort(childrenW.begin(), childrenW.end());

    int res = 0;

    int i = 0, j = childrenW.size() - 1;

    while (i < j)
    {
        if (childrenW[i] > x / 2)
        {
            res += j - i + 1;
            i = j + 1;
            break;
        }

        int pairIndex = upper_bound(childrenW.begin() + i + 1, childrenW.begin() + j + 1, x - childrenW[i]) - childrenW.begin();
        
        bool didNotFind = pairIndex == j + 1;

        if (didNotFind)
        {
            res++;
            i++;
            j--;
            continue;
        }

        // pairIndex == j && pairIndex > i + 1
        // pairIndex == j && pairIndex == i + 1
        // pairIndex < j && pairIndex > i + 1
        // pairIndex < j && pairIndex == i + 1

        pairIndex--;

        res += j - pairIndex;
        res++;
        j = pairIndex - 1;
        i++;
    }

    if (i == j)
    {
        res++;
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