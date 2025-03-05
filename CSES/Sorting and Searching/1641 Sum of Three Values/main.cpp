#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;

const int maxN = 5000;
int n, x;
pair<int, int> values[maxN + 1];
 
void solve() {
    scanf("%d%d", &n, &x);

    unordered_map<int, vector<int>> s;

    s.reserve(4 * maxN);
 
    for (int i = 1; i <= n; i++)
    {
        int val = 0;
        scanf("%d", &val);

        s[val].push_back(i);
    }

    for (auto iter1 = s.begin(); iter1 != s.end(); iter1++)
    {
        for (auto iter2 = iter1; iter2 != s.end(); iter2++)
        {
            if (iter1 == iter2)
            {
                if (iter1->second.size() < 2)
                {
                    continue;
                }
            }

            int thirdVal = x - iter1->first - iter2->first;

            auto iter3 = s.find(thirdVal);

            if (iter3 == s.end())
            {
                continue;
            }

            int id1 = iter1->second[0];
            int id2 = iter2 == iter1 ? iter2->second[1] : iter2->second[0];

            int id3 = 0;

            if (iter3 == iter1 && iter3 == iter2)
            {
                if (iter3->second.size() > 2)
                {
                    id3 = iter3->second.back();
                }
                else
                {
                    continue;
                }
            }
            else if (iter3 == iter1 || iter3 == iter2)
            {
                if (iter3->second.size() > 1)
                {
                    id3 = iter3->second.back();
                }
                else
                {
                    continue;
                }
            }
            else
            {
                id3 = iter3->second.front();
            }

            printf("%d %d %d", id1, id2, id3);
            return;
        }
    }
    

    printf("IMPOSSIBLE");
}

void solve2() {
    scanf("%d%d", &n, &x);
 
    for (int i = 1; i <= n; i++)
    {
        int val = 0;
        scanf("%d", &val);

        values[i] = {val, i};
    }

    sort(values + 1, values + n + 1);

    for (int i = 1; i <= n; i++)
    {
        int sum = x - values[i].first;
        
        int l = i + 1;
        int r = n;
        
        for (; l < r; l++)
        {
            int target = sum - values[l].first;

            while(l < r && target < values[r].first)
            {
                r--;
            }

            if (l < r && target == values[r].first)
            {
                printf("%d %d %d", values[i].second, values[l].second, values[r].second);
                return;
            }
        }
        
    }

    printf("IMPOSSIBLE");
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
        solve2();
    }
 
    return 0;
}