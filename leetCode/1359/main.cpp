#include <iostream>
#include <bits/stdc++.h>

using namespace std;

long long MOD = 1e9 + 7;

long long modMult(long long a, long long b)
{
    return ((a % MOD) * (b % MOD)) % MOD;
}

long long modSum(long long a, long long b)
{
    return ((a % MOD) + (b % MOD) + MOD) % MOD;
}


// std::vector<long long> resStorage(501, 0);

class Solution {
public:
    int countOrders(int n) {
        if (n == 1)
        {
            return 1;
        }

        int res = 1;

        for (int i = 2; i <= n; i++)
        {
            int multiplier1 = res;
            int multiplier2 = (((i-1)*2 + 1) * ((i-1)*2 + 1 + 1)) / 2;

            res = modMult(multiplier1, multiplier2);
        }
        
        return res;
    }
};


void solve(std::istream& in, std::ostream& out)
{
    Solution s;
    out << s.countOrders(1) - 1 << std::endl;
    out << s.countOrders(2) - 6 << std::endl;
    out << s.countOrders(3) - 90 << std::endl;
}

int main()
{
    std::ios::sync_with_stdio(false);
    //std::cout << "hello dude";

    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    // solve(std::cin, std::cout);
    // solve(std::cin, fout);
    solve(fin, std::cout);
    // solve(fin, fout);
    

    return 0;
}