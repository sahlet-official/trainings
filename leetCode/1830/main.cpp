#include <iostream>
#include <bits/stdc++.h>

using namespace std;

long long MOD = 1e9 + 7;

inline long long modMult(long long a, long long b)
{
    return ((a % MOD) * (b % MOD)) % MOD;
}

inline long long modSum(long long a, long long b)
{
    return ((a % MOD) + (b % MOD) + MOD) % MOD;
}

inline long long modPow(long long a, long long b)
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

inline long long modInverse(long long a)
{
    return modPow(a, MOD - 2);
}

inline long long modDivide(long long a, long long b)
{
    a %= MOD;
    b %= MOD;
    if (a % b == 0) {
        return a / b;
    }

    return modMult(a, modInverse(b));
}

class Solution {
    public:
    int makeStringSorted(string s)
    {
        std::vector<int> counts(26);

        long long rangeL = 0, rangeR = 1;

        int i = 0;
        int divider = 1;
        for (char ch: s) {
            counts[ch - 'a'] += 1;
            
            divider = (counts[ch - 'a'] % MOD) * (divider % MOD) % MOD;
            
            i++;
            rangeR = (i % MOD) * (rangeR % MOD) % MOD;
        }
        
        rangeR = modDivide(rangeR, divider);

        for(int i = 0; i < s.size() - 1; i++)
        {
            int space = ((rangeR % MOD) - (rangeL % MOD) + MOD) % MOD;
            int step = modDivide(space, s.size() - i);
            
            int j = 0;
            while (j < s[i] - 'a')
            {
                rangeL = modSum(rangeL, modMult(counts[j], step));
                j++;
            }

            rangeR = modSum(rangeL, modMult(counts[j], step));

            counts[j]--;
        }

        return rangeL;
    }
};

bool equal(const vector<int>& v1, const vector<int>& v2)
{
    if (v1.size() != v2.size())
    {
        return false;
    }

    for (size_t i = 0; i < v1.size(); i++)
    {
        if (v1[i] != v2[i])
        {
            return false;
        }
    }
    
    return true;
}

bool equal(int i1, int i2)
{
    return i1 == i2;
}

void solve(std::istream& in, std::ostream& out)
{
    Solution s;
    vector<vector<int>> v;

    //v = {{2,6},{5,1},{73,660}};
    out << equal(s.makeStringSorted("cba"), 5) << std::endl;
    out << equal(s.makeStringSorted(
        "kkuevcziftolveebyuinxgqwnqxghxelciquycmctgkuboxvsxyunxevrrzludgdievetadtagdchkyxbkipudyolrronsnronmmrbemwaojqdptcjfqevqythnyfamhasxpgqxgjlulmxgymiluzlwtrvjietipnnwksptlrviedwkyfwpflqqcpjdnejrnhmdfkbohsonipqxdmardjiddxghzwdzvvznhvvxcnqgvytmrnpumvtamhlfeqhynhnqxsvrbomvoycdhywixnvpqvdpkxniflmzwxfjpkoffnlvdhzfsqjaxwbfiwdewfepoedzhccpkgsemkhamyispadazewbefamleygaudzqhbbxlaanzrqtpydoamwgmgornffgzucezohpthqjvdabkmtynsrswpvmdapapjluvwqfqulmsceveipgnwvaupboercxvzlrnunwlgvtvmvminveyigixqepnuiqffuimyxgsevpoystkvcyafrrgdsbwfueijszdcomygiisqbdjykokeubwsydqeweahxtqfohafewwkbraonscnxuycceafzhuirfejaorrjopbjkkdgbrwraihjzwunjpjwpjicrwgknlasgapqexyukdgvtzigdmsehmlo"
        "pmeojynfoswbhbiebdlkvizzmvuzzzwqejaqpqnoysfzuwjaihgkclieiidkeacdocdnzwbyqttajctcxnolrmogtglvgakvuapiyfriuqumhcjeoawnicsyxbughoxwasephelvstygvzgqihcaurwerelzcozeptgyivckugllthwczlgxepibguksicztxssftdqjrlhdgdrzyeofrtvbbxqhbsovdiwjonnzwvlxsqykrzmolpywwzsdsghxkcuctcjtxuvejbvojlphzsndnwwuufjrzcgrlqvjvynmziandlrkaqoekutjexehdguwfkeenlfqsywswdwsctldggxhhcxilfthitbbjexpcphrjmkpblnihrdommzpyuajmftyrukijthvljjrmjskfjnmrtkfcheozchkznswmckytjycbprvllquavqarobmdqyajtubdxirnmwqneraxxeoqidcyveiszyawoolwyvcjsavxbvdijtujvdqkwulbgtduwghyhwlgokannkdegbggwvmyzpzpdunolrdaerzxndurveomzmbsalycrybhtlwmjagkkumldvskccdluqmamxiietxxhutsniiwfrictqgjohpqvbrtybojdxomegnyyqoyshjyyprodvajyumsoyyoheykpvprvoutofrlbtxmabcpgszsvczwsmvnqdpbkrfhtdzrgtggzvgwitdbatwmgzjpxzrsijvicnndysruaadcnpakrmjojcecpgkwfmrzcuadklupmvphtisnfbraviqvgeztmthcmawbxvnbjbtfoisbvcnaeyauklsbsvppnpajeporwajkwjkawqxmjqtvfiekvpyssdaeeckenhyjvwpuluuxnlabdtwicljzfdmrljfryrzhmvicvqfwlhomdzpfywfxcjlbifcioupzsjycfrdaypzuoxpsmjpjixhbfnuhxoodageqgufcdbfpkkvhmrwlwifbhgvohfvncwwnzgxqkjohzclhjnxnabboafvsztpfsjvrgvwrkdpkpzdyebznrfwmhsmvfykzejyfvhkfhkclxrhcpnjrpmeoavlkvwbmmxyamiliyjqymkowmzftxgvfuizvgtmnscpfsrmlwmcfusdmaneecbywjeuunuclvvtdbrahsiclpgdhfabfsxlhexvuoxyoswchpgwsmrkeezrgpezxpbzlhqhlibstkrntzolxvscvbcmqsbhvzohzplpphqhbypnfrgaufxpzucbuouekzdkcfyueavginzruqryvykohqxmzlalyuxhtbcirfdhtbssvojhtvanbwgvkmwjnffncxfrpnnwlnxeoqohtmytlfxsunncwvikncfvyaeybrdbrnxqqwlkrrqrtfpbdtmlsrxfobvntxwyycalfsywydexqydchsqrndioqazdjletfwzwjlfpibybqtigokbhzqnunsfbsgyhjstdturrfaxyjazywzythvbpsesoxkugnwaccctnzqktkcemrcghstujevrdibgajjzzstjbfyewdtvbhyaeyinnpvppemnmjndhdiyuvwulavrssigqjaaqtufcpfgfdnzfxlmhweybdbynebkitpvwmrpjesujpyubtyzdvgwuwfqhnyjllbjthgwgczmuvonvcobqwmbrioyhxlfyxmvnirjtthxktlihfxjwzleehcexcutndspzlgxzxdszcqmyeetxvygmmftjhpymeoffdrzyaxewkhovxgkvxrfpaxwjxmcdiodpuexoiynzabmrijonolzfaopghdosjsxarauruxcfcpghwfnkqsshbkhxdecrojkxeqhvmkfnpzulabebqxbxkvslijdrgvegnchktbvquyxcrkbiifwwfoorkcrvddqpylefxfkfbvppqjhqfdovukmouvuuavwicnqkxihydfijbpphpppaqvruvxvgjybmulctubtjlmbgsoqqplrvvqnhwunryukmjcjreujujtncgmouakvylofdfuapzzdetvjsbumktbouxeiiuwvbazfmnbsyhiutbdddhwuwvuhqwywbqoichezbofxzhpjsnzxnfyhnxxrddjdhrbsycigisgmvtkhfukeofqkoopazsabipzpomqixxbmcekorvhzrowjxuoifupollfrmqkdjjhwysbloshwrbpddhuoscpcayqrxbqelunx"
        ), 134266381) << std::endl;
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