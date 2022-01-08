#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <set>
#include <chrono>
#include <unordered_map>
#include <iterator>
#include <boost/algorithm/string.hpp>


using namespace boost::algorithm;
using namespace std;
typedef unsigned long long ulong;
typedef vector<pair<vector<string>, vector<string>>> display_info;


display_info parse_info(ifstream& input_file)
{
    string line;
    display_info info;

    while (getline(input_file, line)) {
        vector<string> parts;
        vector<string> signals;
        vector<string> outputs;

        boost::split(parts, line, [](char c) {return c == '|'; });

        string left = parts[0];
        string right = parts[1];
        
        trim_right(left);
        trim_left(right);

        boost::split(signals, left, [](char c) {return c == ' '; });
        boost::split(outputs, right, [](char c) {return c == ' '; });
        info.push_back(make_pair(signals, outputs));
    }
    
    return info;
}

int part_1(display_info& info) {
    int total = 0;
    const vector<int> sizes{ 2, 3, 4, 7 };
    for (const auto& info_line : info) {
        for (const string& word : info_line.second) {
            int word_size = word.size();
            total += any_of(sizes.begin(), sizes.end(), [word_size](int i) {return i == word_size; });
        }
    }
    return total;
}

int part_2(display_info& info) {

    int ans = 0;
    for (const auto& info_line : info) {
        
        unordered_map<int, set<char>> d;

        for (const string& sig : info_line.first) {
            int l = sig.size();
            if (l == 2 || l == 4) {
                set<char> s(sig.begin(), sig.end());
                d[l] = s;
            }
        }

        //string n ("");
        int n = 0;
        for (const string& output : info_line.second) {
            int l = output.size();
            n *= 10;

            if (l == 2) n += 1;
            else if (l == 4) n += 4;
            else if (l == 3) n += 7;
            else if (l == 7) n += 8;
            else if (l == 5 || l == 6) {
                set<char> s(output.begin(), output.end());
                vector<char> s_2_inter;
                vector<char> s_4_inter;
                std::set_intersection(s.begin(), s.end(), d[2].begin(), d[2].end(), back_inserter(s_2_inter));
                std::set_intersection(s.begin(), s.end(), d[4].begin(), d[4].end(), back_inserter(s_4_inter));
                if (l == 5) {
                    if (s_2_inter.size() == 2) n += 3;
                    else if (s_4_inter.size() == 2) n += 2;
                    else n += 5;
                }
                else {
                    if (s_2_inter.size() == 1) n += 6;
                    else if (s_4_inter.size() == 4) n += 9;
                    else n += 0;
                }
            }
            else {
                n = n / 10;
            }
        }
        ans += n;
    }
    return ans;
}


int main()
{
    auto start = chrono::high_resolution_clock::now();
    ifstream input_file("input.txt");
    display_info info = parse_info(input_file);
    cout << part_1(info) << endl;
    cout << part_2(info) << endl;

    auto end = chrono::high_resolution_clock::now();
    auto elapsed = end - start;
    cout << "Elapsed: " << elapsed.count() << endl;
}
