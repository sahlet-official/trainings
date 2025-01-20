#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:

    std::pair<int, int> min(const std::pair<int, int>& l, const std::pair<int, int>& r)
    {
        if (l.second - l.first < r.second - r.first)
        {
            return l;
        }

        if (l.second - l.first > r.second - r.first)
        {
            return r;
        }

        return l.first < r.first ? l : r;
    }

    vector<int> smallestRange(vector<vector<int>>& nums) {
        std::map<int, std::set<int>> memory;

        int minA = 1e5;
        int maxB = -1e5;

        for (int i = 0; i < nums.size(); i++) {
            for (int j = 0; j < nums[i].size(); j++)
            {
                memory[nums[i][j]].insert(i);

                minA = std::min(minA, nums[i][j]);
                maxB = std::max(maxB, nums[i][j]);
            }
        }

        std::pair<int, int> minRange = { minA, maxB };
        std::pair<int, int> curRange = { minA, minA };
        std::map<int, int> arrsInCurRange;

        auto iterA = memory.begin();
        auto iterB = memory.begin();
        bool finished = false;
        bool movingA = false;

        for (int arrId : iterB->second)
        {
            arrsInCurRange[arrId]++;
        }

        if (arrsInCurRange.size() == nums.size())
        {
            minRange = curRange;
            finished = true;
        }
        
        while (!finished)
        {
            if (movingA)
            {
                for (int arrId : iterA->second)
                {
                    auto iter = arrsInCurRange.find(arrId);
                    iter->second--;
                    
                    if (iter->second == 0)
                    {
                        arrsInCurRange.erase(iter);
                    }
                }
                iterA++;
                curRange.first = iterA->first;

                if (arrsInCurRange.size() < nums.size())
                {
                    movingA = false;
                }
                else if (arrsInCurRange.size() == nums.size())
                {
                    minRange = min(minRange, curRange);
                }
            }
            else
            {
                iterB++;
                if (iterB == memory.end())
                {
                    finished = true;
                    break;
                }

                curRange.second = iterB->first;
                for (int arrId : iterB->second)
                {
                    arrsInCurRange[arrId]++;
                }

                if (arrsInCurRange.size() == nums.size())
                {
                    minRange = min(minRange, curRange);
                    movingA = true;
                }
            }
        }

        return { minRange.first, minRange.second };
    }
};

void solve(std::istream& in, std::ostream& out)
{
    Solution s;
    std::vector<std::vector<int>> v = {{4,10,15,24,26},{0,9,12,20},{5,18,22,30}};
    auto res = s.smallestRange(v);
    out << res[0] << " " << res[1];
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