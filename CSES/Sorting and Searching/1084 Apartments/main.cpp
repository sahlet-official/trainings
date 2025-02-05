#include <iostream>
#include <bits/stdc++.h>

using namespace std;
 
void solve() {
    int n = 0, m = 0, k = 0;
    cin >> n >> m >> k;

    std::vector<int> a(n), b(m);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    for (int i = 0; i < m; i++)
    {
        cin >> b[i];
    }
    
    int res = 0;

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    for (int i = 0, j = 0; i < n && j < m;)
    {
        if (b[j] < a[i])
        {
            if (b[j] >= a[i] - k)
            {
                res++;
                i++;
            }

            j++;
        }
        else
        {
            if (b[j] <= a[i] + k)
            {
                res++;
                j++;
            }

            i++;
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