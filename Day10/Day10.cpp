#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <utility>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::unordered_map;
using std::string;
using std::ifstream;
using std::pair;

const unordered_map<char, char> open_to_close = {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'},
    {'<', '>'}
};

const unordered_map<char, char> close_to_open = {
    {')', '('},
    {']', '['},
    {'}', '{'},
    {'>', '<'}
};


const unordered_map<char, int> sym_points = {
    {')', 3},
    {']', 57},
    {'}', 1197},
    {'>', 25137}
};

const unordered_map<char, int> autocomp_points = {
    {'(', 1},
    {'[', 2},
    {'{', 3},
    {'<', 4}
};

typedef unsigned long long disappointing_dirty_overflow_trick_by_aoc;

pair<disappointing_dirty_overflow_trick_by_aoc, bool> solve(const string& line) {
    
    vector<char> opening_chars;

    for (const char& c : line) {
        auto c_lookup = close_to_open.find(c);
        if (open_to_close.find(c) != open_to_close.end()) {
            opening_chars.push_back(c);
        }
        else {
            if (c_lookup->second != opening_chars.back()) {
                return std::make_pair(sym_points.find(c)->second, false);
            }
            else {
                opening_chars.pop_back();
            }
        }
    }
    disappointing_dirty_overflow_trick_by_aoc auto_comp_score = 0;
    for (auto it = opening_chars.rbegin(); it != opening_chars.rend(); ++it) {
        //char matching_close_char = open_to_close.find(*it)->second;
        int char_points = autocomp_points.find(*it)->second;
        auto_comp_score = ((5 * auto_comp_score) + char_points);
    }

    return std::make_pair(auto_comp_score, true);
}


int main() {
    
    ifstream input_file("input.txt");
    string line;
    disappointing_dirty_overflow_trick_by_aoc p1_total_score = 0;
    vector<disappointing_dirty_overflow_trick_by_aoc> p2_scores;

    while (input_file >> line) {
        pair<disappointing_dirty_overflow_trick_by_aoc,bool> res = solve(line);
        if (!res.second){
            p1_total_score += res.first;
        }
        else {
            p2_scores.push_back(res.first);
        }
    }
    std::sort(p2_scores.begin(), p2_scores.end());

    cout << "Part 1: " << p1_total_score << endl;
    cout << "Part 2: " << p2_scores[p2_scores.size() / 2] << endl;
    return 0;
}

