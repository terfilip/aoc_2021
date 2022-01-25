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


constexpr bool USE_TEST = true;

typedef unordered_map<string, char> instr_t;
typedef unsigned long long decent_number_t;



void template_cycle(string& polytemp, instr_t& instrs) {
    
    size_t start_sz = polytemp.size();
    for (int i = 0; i < (start_sz - 1); ++i) {
        string cur_two_lets = polytemp.substr(i, 2);
        if (instrs.find(cur_two_lets) != instrs.end()) {
            polytemp.insert(i + 1, 1, instrs[cur_two_lets]);
            ++i;
            ++start_sz;
        }
    }
    //cout << polytemp << endl; 
}

int sln(const string& polytemp, instr_t& instrs, const std::set<char>& all_chars, const int step_cnt) {
    string p1s = polytemp;

    for (int i = 0; i < step_cnt; ++i) {
        //cout << "\tStep " << i << endl;
        template_cycle(p1s, instrs);
    }
    decent_number_t min_val = 0xffffffffffffffff;
    decent_number_t max_val = 0;


    for (const char& c : all_chars) {
        decent_number_t cnt = std::count(p1s.begin(), p1s.end(), c);
        if (cnt > max_val) max_val = cnt;
        if (cnt < min_val) min_val = cnt;
        cout << "\t\t[" << c << "]= " << cnt << endl;
        cout << endl;
    }

    return max_val - min_val;
}


int main()
{
    ifstream input_file("input.txt"); //((USE_TEST) ? "test_input.txt" : "input.txt");
    std::set<char> all_chars;
    
    string polytemp;
    std::getline(input_file, polytemp); 

    for (const char& c: polytemp) {
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

    for (int i = 0; i< 16; ++i)
        cout << i << " cycles ans " << sln(polytemp, instrs, all_chars, i) << endl;

}

