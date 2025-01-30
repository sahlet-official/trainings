#include <iostream>
#include <bits/stdc++.h>

using namespace std;

void backtracking(int& minDif, const std::vector<int>& apples, size_t index, long long sumWeight, long long curWeight1, long long curWeight2)
{
    long long curDif = abs(curWeight1 - curWeight2);

    if (index == apples.size())
    {
        minDif = min((long long)minDif, curDif);

        return;
    }

    bool dontContinue = (
        (
            max(curWeight1, curWeight2) -
            (
                min(curWeight1, curWeight2) + (sumWeight - (curWeight1 + curWeight2))
            )
        )
        >= minDif
    );

    if (dontContinue)
    {
        return;
    }

    backtracking(minDif, apples, index + 1, sumWeight, curWeight1 + apples[index], curWeight2);
    backtracking(minDif, apples, index + 1, sumWeight, curWeight1, curWeight2 + apples[index]);
}
 
void solve() {
    int n;
    cin >> n;

    std::vector<int> apples(n);

    int minDif = INT_MIN;

    long long sumWeight = 0;

    for (size_t i = 0u; i < apples.size(); i++)
    {
        int a;
        cin >> a;
        apples[i] = a;

        minDif = max(minDif, a);
        sumWeight += a;
    }

    backtracking(minDif, apples, 1u, sumWeight, apples[0], 0);

    cout << minDif;
}

void solve2() {
    int n;
    cin >> n;

    std::vector<int> apples(n);

    int minDif = INT_MIN;

    long long sumWeight = 0;

    for (size_t i = 0u; i < apples.size(); i++)
    {
        int a;
        cin >> a;
        apples[i] = a;

        minDif = max(minDif, a);
        sumWeight += a;
    }

    for (size_t i = 0; i < (1 << (n - 1)); i++)
    {
        long long curWeight1 = apples[0];
        long long curWeight2 = 0;

        for (int j = 0; j < n - 1; j++)
        {
            if (i & (1 << j))
            {
                curWeight1 += apples[j+1];
            }
            else
            {
                curWeight2 += apples[j+1];
            }

            bool dontContinue = (
                (
                    max(curWeight1, curWeight2) -
                    (
                        min(curWeight1, curWeight2) + (sumWeight - (curWeight1 + curWeight2))
                    )
                )
                >= minDif
            );

            if (dontContinue)
            {
                break;
            }
        }
        
        minDif = min((long long)minDif, abs(curWeight1 - curWeight2));
    }
    

    cout << minDif;
}


int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    long long testsNumber = 1;

    // cin >> testsNumber;

    for (int i = 0; i < testsNumber; i++)
    {
        solve();
    }

    return 0;
}