#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Solution {
    std::vector<std::vector<int>> memory;
public:

    int factor(int n)
    {
        if (n == 0)
        {
            return 1;
        }

        return n * factor(n - 1);
    }

    int combinations(int n, int m)
    {
        return factor(n) / (factor(n - m) * factor(m));
    }

    int poorPigsSub(int pigs, int t) {
        if (pigs == 0)
        {
            return 1;
        }

        // if (pigs == 1)
        // {
        //     return t + 1;
        // }

        if (t == 0)
        {
            return 1;
        }

        if (t == 1 && pigs == 1)
        {
            int maxBack = 2;
            // int maxBack = pow(1 + 1, pigs);
            return maxBack;
        }

        if (memory[pigs][t])
        {
            return memory[pigs][t];
        }

        int res = 0;

        for (int i = 0; i <= pigs; i++)
        {
            res += combinations(pigs, i) * poorPigsSub(pigs - i, t - 1);
        }

        memory[pigs][t] = res;

        return res;
    }

    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        if (memory.empty())
        {
            memory.resize(1000);
            for (auto &v : memory)
            {
                v.resize(1000);
            }
        }

        if (buckets == 1)
        {
            return 0;
        }
        
        int t = minutesToTest / minutesToDie;

        int pigs = 0;
        int maxBuckets = 1;
        while (maxBuckets < buckets)
        {
            pigs += 1;
            maxBuckets = poorPigsSub(pigs, t);
        }

        return pigs;
    }
};

void solve(std::istream& in, std::ostream& out)
{
    Solution s;

    out << s.poorPigs(4, 15, 15) - 2 << std::endl;
    out << s.poorPigs(4, 15, 30) - 2 << std::endl;
    out << s.poorPigs(5, 1, 1) - 3 << std::endl;
    out << s.poorPigs(5, 1, 2) - 2 << std::endl;
    out << s.poorPigs(5, 1, 3) - 2 << std::endl;
    out << s.poorPigs(6, 1, 1) - 3 << std::endl;
    out << s.poorPigs(6, 1, 2) - 2 << std::endl;
    out << s.poorPigs(6, 1, 3) - 2 << std::endl;
    out << s.poorPigs(1000, 1, 4) - 5 << std::endl;
    out << s.poorPigs(1000, 12, 60) - 4 << std::endl;
    out << s.poorPigs(5, 15, 60) - 1 << std::endl;
    out << s.poorPigs(25, 15, 60) - 2 << std::endl;
    out << s.poorPigs(8, 10, 10) - 3 << std::endl;
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


/* const int msize = 1001;
int memory [msize][msize];

class Solution {

public:
    Solution()
    {
        for (int i = 0; i < msize; i++)
        {
            for (int j = 0; j < msize; j++)
            {
                memory[i][j] = 0;
            }
        }
    }

    int poorPigs(int buckets, int t) {
        if (t == 0)
        {
            return -1;
        }

        int maxPigs = buckets == 1 ? 0 : buckets == 2 ? 1 : (buckets / 3) * 2 + (buckets % 3) / 2;

        if (t == 1)
        {
            return maxPigs;
        }

        if (memory[buckets][t])
        {
            return memory[buckets][t];
        }

        int res = maxPigs;

        for (int i = 1; i < maxPigs; i++)
        {
            if (i == 1)
            {
                //dead
                int nextBuckets1 = (buckets - 1) / 2;
                int subRes1 = poorPigs(nextBuckets1, t - 1);

                //alive
                int nextBuckets2 = buckets - (buckets - 1) / 2;
                int subRes2 = poorPigs(nextBuckets2, t - 1);

                int subRes = std::max(subRes1 + 1, subRes2);
                
                if (res < subRes)
                {
                    break;
                }

                res = subRes;
            } else if (i >= buckets / 2)
            {
                int subRes = std::max(i, 2);
                
                if (res < subRes)
                {
                    break;
                }

                res = subRes;

            }
            else
            {
                int bucketsToOnePig = buckets / i;
                int rest = buckets % i;

                //alive
                int nextBuckets1 = rest;
                int subRes1 = poorPigs(nextBuckets1, t - 1);

                //dead 1
                int nextBuckets2 = bucketsToOnePig;
                int subRes2 = poorPigs(nextBuckets2, t - 1);

                int subRes = std::max(i, std::max(subRes1, subRes2 + 1));
                
                if (res < subRes)
                {
                    break;
                }

                res = subRes;

            }
        }

        memory[buckets][t] = res;

        return res;
    }

    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        int t = minutesToTest / minutesToDie;

        return poorPigs(buckets, t);
    }
}; */

/* class Solution {
    std::vector<std::vector<int>> memory;
public:

    bool poorPigsSub(int pigs, int buckets, int t) {
        if (t == 0)
        {
            return false;
        }

        int maxPigs = buckets == 1 ? 0 : buckets == 2 ? 1 : (buckets / 3) * 2 + (buckets % 3) / 2;

        if (pigs >= maxPigs)
        {
            return true;
        }

        if (t == 1)
        {
            return false;
        }

        int bucketsToOnePig = buckets * (pigs - 1) / (pigs * pigs);
        // int bucketsToOnePig = buckets * pigs / (pigs * pigs + pigs + 1);
        int rest = buckets - bucketsToOnePig * pigs;

        int width = 200;

        while (true) {

            //all alive
            int nextBuckets1 = rest;
            int subRes1 = poorPigsSub(pigs, nextBuckets1, t - 1);

            //dead 1
            int nextBuckets2 = bucketsToOnePig;
            int subRes2 = poorPigsSub(pigs - 1, nextBuckets2, t - 1);

            bool res = subRes1 && subRes2;

            if (res)
            {
                return true;
            }

            if (subRes1)
            {
                
            }
            else if (subRes2)
            {
                
            }
            else
            {
                return false;
            }
        }
    } */