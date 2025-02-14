#include <iostream>
#include <bits/stdc++.h>

using namespace std;
 
void solve() {
    int n = 0;
    scanf("%d", &n);

    vector<pair<int, int>> movies;
    movies.reserve(n);

    for (int i = 0; i < n; i++)
    {
        int a = 0, b = 0;
        scanf("%d%d", &a, &b);
        
        movies.emplace_back(a, b);
    }

    auto compare = [](const pair<int, int>& l, const pair<int, int>& r) -> bool
    {
        return l.second == r.second ? l.first > r.first : l.second < r.second;
    };

    sort(movies.begin(), movies.end(), compare);

    int lastEnd = 0;
    int res = 0;

    for (size_t i = 0; i < movies.size(); i++)
    {
        if (lastEnd <= movies[i].first)
        {
            res++;
            lastEnd = movies[i].second;
        }
    }

    printf("%d", res);
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