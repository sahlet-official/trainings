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

long long modPow(long long a, long long b)
{
    long long res = 1;
    while(b)
    {
        if (b % 2)
        {
            res = modMult(res, a);
        }

        b /= 2;
        a = modMult(a, a);
    }

    return res;
}

long long modInverse(long long a)
{
    return modPow(a, MOD - 2);
}

long long modDivide(long long a, long long b)
{
    return modMult(a, modInverse(b));
}


class Solution {
    struct Node
    {
        int num = 1;
        int permutations = 1;
        int numNodesInThisTree = 1;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
    };

    std::unique_ptr<Node> root;
public:

    void insertNumber(std::unique_ptr<Node>& node, int num)
    {
        if (!node)
        {
            node = std::make_unique<Node>();
            node->num = num;
            return;
        }

        if (num == node->num)
        {
            return;
        }

        if (num > node->num)
        {
            insertNumber(node->right, num);
        }
        else
        {
            insertNumber(node->left, num);
        }

        node->numNodesInThisTree++;
    }

    static const int permutationMemorySize = 1001;
    std::vector<std::vector<int>> permutationMemory;

    int permutations(int n, int m)
    {
        if (m == 0)
        {
            return 1;
        }

        if (n == 0)
        {
            return 1;
        }

        if (m == 1)
        {
            return n + 1;
        }

        if (n == 1)
        {
            return m + 1;
        }

        if (permutationMemory[n][m])
        {
            return permutationMemory[n][m];
        }

        int res = 1; // all n in 0 hole

        for (int i = 1; i <= n; i++)
        {
            int subRes = permutations(i, m - 1);
            res = modSum(res, subRes);
        }

        permutationMemory[n][m] = permutationMemory[m][n] = res;

        return res;
    }

    void calculatePermutations(std::unique_ptr<Node>& node)
    {
        node->permutations = 1;
        
        if (!node->left && !node->right)
        {
            return;
        }

        if (node->left && node->right)
        {
            calculatePermutations(node->left);
            calculatePermutations(node->right);

            int perm = permutations(node->left->numNodesInThisTree, node->right->numNodesInThisTree);
            
            perm = modMult(perm, node->left->permutations);
            perm = modMult(perm, node->right->permutations);
            
            node->permutations = perm;

            return;
        }

        auto& next = node->left ? node->left : node->right;

        if (next)
        {
            calculatePermutations(next);

            node->permutations = next->permutations;
        }
    }

    int numOfWays(vector<int>& nums) {
        root.release();

        if (permutationMemory.empty())
        {
            permutationMemory.resize(permutationMemorySize);
            for(int i = 0; i < permutationMemorySize; i++)
            {
                permutationMemory[i].resize(permutationMemorySize);
            }

            for (int i = 0; i < permutationMemorySize; i++)
            {
                permutationMemory[0][i] = 1;
                permutationMemory[i][0] = 1;
            }

            int halfSize = permutationMemorySize / 2;
            for (int m = 1; m < permutationMemorySize; m++)
            {
                for (int n = 1; n <= halfSize; n++)
                {
                    int res = modSum(permutationMemory[n - 1][m], permutationMemory[n][m - 1]);

                    // for (int i = 0; i <= n; i++)
                    // {
                    //     res = modSum(res, permutationMemory[i][m - 1]);
                    // }
                    permutationMemory[n][m] = permutationMemory[m][n] = res;
                }
            }   
        }

        for(int num : nums)
        {
            insertNumber(root, num);
        }

        calculatePermutations(root);

        return modSum(root->permutations, -1);
    }
};


void solve(std::istream& in, std::ostream& out)
{
    Solution s;
    vector<int> v;

    v = {2,1,3};
    out << s.numOfWays(v) - 1 << std::endl;
    v = {3,4,5,1,2};
    out << s.numOfWays(v) - 5 << std::endl;
    v = {1,2,3};
    out << s.numOfWays(v) - 0 << std::endl;
    v = {10,23,12,18,4,29,2,8,41,31,25,21,14,35,26,5,19,43,22,37,9,20,44,28,1,39,30,38,36,6,13,16,27,17,34,7,15,3,11,24,42,33,40,32};
    out << s.numOfWays(v) - 0 << std::endl;
    v = {718,767,634,113,799,795,620,130,632,763,272,114,24,434,144,194,2,262,367,792,203,953,48,711,153,368,170,212,219,73,45,504,345,467,769,40,321,943,141,454,618,885,662,70,39,49,123,186,132,563,588,663,358,973,193,950,562,134,167,859,813,143,222,925,329,384,866,502,179,83,580,678,269,731,78,375,306,810,689,604,669,317,648,64,626,533,341,544,681,921,489,242,292,969,929,927,871,808,856,556,611,66,912,482,558,603,557,42,497,88,97,59,158,705,198,672,607,724,541,757,41,765,152,255,979,279,480,659,775,754,642,395,523,481,154,51,532,841,229,187,422,418,996,628,524,665,441,356,800,171,824,166,977,602,288,847,830,918,831,463,675,182,289,7,933,398,137,469,677,101,978,999,479,473,744,537,15,133,246,893,297,360,962,92,30,599,610,1000,853,629,259,664,574,271,451,81,487,640,496,623,679,488,870,660,437,993,512,428,511,586,615,478,155,624,458,692,477,729,303,706,976,281,178,168,971,940,872,606,553,818,318,721,759,224,326,812,947,521,17,438,915,310,129,654,103,838,111,889,201,394,858,840,346,857,756,244,957,639,595,298,403,424,551,483,854,470,396,23,291,614,703,188,376,69,405,328,452,942,174,827,391,296,263,159,774,350,964,415,667,762,900,19,686,468,522,359,485,789,407,835,320,68,196,184,261,21,254,58,500,707,709,55,333,104,876,416,258,277,798,60,275,612,386,225,972,234,886,169,14,270,570,284,13,616,994,671,90,897,617,456,924,339,904,540,56,309,967,773,476,72,948,163,80,935,200,982,630,94,3,251,38,997,36,12,851,457,161,374,430,241,816,785,713,180,863,910,684,388,928,747,404,510,226,700,286,31,218,590,231,363,106,472,939,290,608,110,631,966,420,99,542,443,471,195,855,354,1,202,165,414,400,794,555,173,25,917,316,566,475,837,125,801,891,609,265,861,690,175,160,750,503,597,450,666,673,465,820,85,370,860,914,498,102,319,633,295,282,412,448,852,313,951,119,208,734,802,61,353,127,311,788,529,683,565,26,843,572,909,736,364,954,495,546,46,109,84,923,862,164,245,107,466,661,238,826,715,823,162,680,124,655,745,561,373,105,751,884,850,594,145,980,362,805,147,419,250,293,442,849,447,844,644,693,581,848,995,842,821,727,116,613,985,605,592,431,460,807,902,371,474,118,435,776,768,791,539,758,907,9,879,545,958,349,382,397,120,784,797,10,554,913,484,499,937,571,204,82,338,37,494,676,399,509,432,89,355,327,778,71,786,357,930,832,528,380,764,538,782,128,322,449,517,585,760,755,894,646,445,273,719,575,548,944,901,806,57,899,464,493,737,780,369,649,335,436,63,868,149,6,625,621,920,401,650,926,983,199,600,520,491,938,221,946,887,336,568,181,582,793,696,833,527,100,984,392,440,992,340,576,344,895,312,740,975,177,619,589,986,274,210,156,845,377,429,257,651,52,427,267,8,337,708,453,236,142,916,960,95,819,790,283,209,135,191,513,783,211,150,366,381,720,949,725,888,828,308,11,228,264,140,550,647,54,223,314,567,945,50,873,746,515,877,43,126,507,779,383,331,301,413,86,122,559,361,896,825,287,22,883,867,536,305,710,408,461,243,712,157,535,564,393,410,16,237,643,743,809,315,247,890,53,79,990,232,20,814,35,252,688,702,365,518,865,216,869,206,771,32,864,516,249,444,27,76,834,417,421,351,961,748,230,280,981,579,591,697,28,47,694,217,796,593,714,543,596,741,29,455,787,490,906,653,687,75,839,525,766,347,965,390,93,423,730,970,240,770,96,342,601,716,207,695,722,256,146,952,425,278,963,674,815,5,227,670,302,641,372,426,530,108,903,733,846,138,131,33,260,233,732,505,932,880,343,905,761,402,519,637,121,486,569,348,534,98,185,968,777,699,922,378,668,959,148,268,213,989,657,645,294,753,658,526,735,514,573,691,307,919,334,65,739,439,387,974,508,325,911,91,560,34,115,176,18,531,742,988,506,701,385,74,406,67,172,190,583,235,656,836,772,803,189,908,955,332,552,704,726,547,723,987,433,379,299,409,352,936,501,276,998,882,253,4,459,598,636,112,738,752,492,991,875,622,878,304,941,87,682,934,197,892,685,214,239,330,749,136,215,151,898,139,652,183,956,804,584,577,874,220,117,205,62,881,549,324,638,717,822,817,77,300,931,811,578,192,389,248,728,462,635,587,323,411,266,627,44,829,698,446,285,781};
    out << s.numOfWays(v) - 0 << std::endl;

    // v = {1, 1};
    // out << s.getProbability(v) << std::endl;
    // v = {2, 1, 1};
    // out << s.getProbability(v) << std::endl;
    // v = {1, 2, 1, 2};
    // out << s.getProbability(v) << std::endl;
    // v = {3, 2, 1};
    // out << s.getProbability(v) << std::endl;
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