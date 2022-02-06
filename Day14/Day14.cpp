#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <utility>
#include <set>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::unordered_map;
using std::ifstream;
using std::string;

constexpr bool USE_TEST = false;

typedef unordered_map<string, char> instr_t;
typedef unsigned long long decent_number_t;
typedef unordered_map<string, decent_number_t> pairs_t;

pairs_t pairs_from_string(const string& polytemp) {
    pairs_t pairs;

    for (int i = 0; i < polytemp.size() - 1; ++i) {
        string pair = polytemp.substr(i, 2);

        if (!pairs.contains(pair)) {
            pairs[pair] = 1;
        }
        else {
            pairs[pair]++;
        }
    }
    return pairs;
}


pairs_t template_cycle(const pairs_t& cur_pairs, const instr_t& instrs) {
    pairs_t new_pairs;

    for (const auto& [ipair, ilet] : instrs) {
        if (cur_pairs.contains(ipair)) {
            decent_number_t cur_pair_count = cur_pairs.at(ipair);
            string new_pair1{ ipair.at(0), ilet };
            string new_pair2{ ilet, ipair.at(1) };
            new_pairs[new_pair1] += cur_pair_count;
            new_pairs[new_pair2] += cur_pair_count;
        }
    }
    return new_pairs;

}

decent_number_t count_letters(pairs_t pairs, char let) {
    decent_number_t cnt = 0;
    for (const auto& [k, v] : pairs) {
        if (k.at(0) == let)
            cnt += v;
    }
    return cnt;
}

decent_number_t sln(const string& polytemp,
    const instr_t& instrs,
    const std::set<char>& all_chars,
    const int step_cnt) {

    const pairs_t pairs = pairs_from_string(polytemp);
    pairs_t generated_pair = template_cycle(pairs, instrs);

    for (int step = 0; step < (step_cnt - 1); ++step) {
        generated_pair = template_cycle(generated_pair, instrs);
    }

    vector<std::pair<char, decent_number_t>> counts;

    for (const char& c : all_chars) {
        counts.push_back(std::make_pair(c, count_letters(generated_pair, c)));
    }

    auto cmp = [](auto left, auto right) {return left.second < right.second; };
    auto [it_minc, it_maxc] = std::minmax_element(counts.begin(),
        counts.end(),
        cmp);
    auto minc = *it_minc; auto maxc = *it_maxc;
    decent_number_t res = maxc.second - minc.second;

    return res;
}

int main()
{
    ifstream input_file((USE_TEST) ? "test_input.txt" : "input.txt");
    std::set<char> all_chars;

    string polytemp;
    std::getline(input_file, polytemp);

    for (const char& c : polytemp) {
        all_chars.insert(c);
    }

    cout << polytemp << endl;
    string line;
    // idiotic empty line
    std::getline(input_file, line);
    instr_t instrs;

    while (std::getline(input_file, line)) {
        string letters = line.substr(0, 2);
        char last = line.at(line.size() - 1);
        all_chars.insert(last);
        instrs[letters] = last;
    }

    cout << "Part 1: " << sln(polytemp, instrs, all_chars, 10) << endl;
    cout << "Part 2: " << sln(polytemp, instrs, all_chars, 40) << endl;
    cout << "Add or subtract 1 to the solution depending on input" << endl;
}

