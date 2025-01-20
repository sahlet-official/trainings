#include <bits/stdc++.h>
#include <cmath>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'solve' function below.
 *
 * The function is expected to return a DOUBLE.
 * The function accepts 2D_INTEGER_ARRAY coordinates as parameter.
 */

double solve(vector<vector<int>> coordinates) {
    int maxx = 0;
    int maxy = 0;
    int minx = 0;
    int miny = 0;
    
    for (auto& pair : coordinates)
    {
        maxx = std::max(maxx, pair[0]);
        minx = std::min(minx, pair[0]);
        maxy = std::max(maxy, pair[1]);
        miny = std::min(miny, pair[1]);
    }
    
    double distance1 = maxx - minx;
    double distance2 = maxy - miny;
    
    int maxabsx = std::max(maxx, std::abs(minx));
    int maxabsy = std::max(maxy, std::abs(miny));
    double distance3 = 0;
    
    if (!(maxabsx == 0 || maxabsy == 0))
    {
        distance3 = std::pow(std::pow((double)maxabsx, 2) + std::pow((double)maxabsy, 2), 0.5);
    }
    
    return std::max(std::max((double)distance1, (double)distance2), distance3);
}

int main()
{

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<vector<int>> coordinates(n);

    for (int i = 0; i < n; i++) {
        coordinates[i].resize(2);

        string coordinates_row_temp_temp;
        getline(cin, coordinates_row_temp_temp);

        vector<string> coordinates_row_temp = split(rtrim(coordinates_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int coordinates_row_item = stoi(coordinates_row_temp[j]);

            coordinates[i][j] = coordinates_row_item;
        }
    }

    double result = solve(coordinates);

    std::cout << std::fixed << std::setprecision(10);

    std::cout << result << "\n";

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
