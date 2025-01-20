#include <iostream>
#include <bits/stdc++.h>

const int MOD = 1e9 + 7;

long long multMod(long long a, long long b)
{
    return ((a % MOD) * (b % MOD)) % MOD;
}

long long revers(long long value){
    long long res = 1, tmp = value;
    
    int m = int(MOD - 2);
    
    while(m)
    {
        if(m % 2){
            res = (res * tmp) % MOD;
            --m;
        }
        m >>= 1;
        tmp = (tmp * tmp) % MOD;
    }
    return res;
}

int factor(int n)
{
    int res = 1;
    for (size_t i = 1; i <= n; i++)
    {
        res = multMod(res, i);
    }
    
    return res;
}

int solve(std::string s) {
    std::unordered_map<char, int> counts;
    counts.reserve(300);

    for (char ch : s)
    {
        counts[ch]++;
    }

    auto mainFactor = factor(s.size() / 2);

    int chFactor = 1;

    for (auto& pair : counts)
    {
        chFactor = multMod(factor(pair.second / 2), chFactor);
    }

    int res = multMod(mainFactor, revers(chFactor));

    return res;
}

#include <fstream>

int main()
{
    //std::ios::sync_with_stdio(false);

    std::ifstream f("input.txt");
    
    std::string s;
    getline(f, s);
    f.close();

    int result = solve(s);

    std::cout << result << "\n";
    

    return 0;
}