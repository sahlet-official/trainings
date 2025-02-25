#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;

const int maxN = 2 * 1e5;
multiset<int> passageLengths;
map<int, int> lightsToPassageLength;
 
void solve() {
    int n = 0, x = 0;
    scanf("%d%d", &x, &n);

    passageLengths.insert(x);

    lightsToPassageLength[0] = x;

    for (int i = 1; i <= n; i++)
    {
        int light = 0;
        scanf("%d", &light);

        auto iter = lightsToPassageLength.lower_bound(light);
        iter--;
        
        int prevLength = iter->second;
        int updatedLength = light - iter->first;
        int newLength = iter->second - updatedLength;
        
        iter->second = updatedLength;

        lightsToPassageLength.emplace_hint(iter, light, newLength);

        passageLengths.erase(passageLengths.find(prevLength));
        passageLengths.insert({ updatedLength, newLength });

        printf("%d ", *--passageLengths.end());
    }
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