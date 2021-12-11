// Day2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>

using namespace std;

typedef vector<pair<string, int>> instructions;


instructions read_input() {
    ifstream input_file("input.txt");
    string instr;
    int n;
    instructions instrs;

    while (input_file >> instr) {
        input_file >> n;
        instrs.push_back(make_pair(instr, n));
    }
    return instrs;
}


int part_1(instructions instrs)
{
    int horpos = 0; int depth = 0;
    pair<string, int> cur_ins;

    for (instructions::iterator it = instrs.begin(); it != instrs.end(); ++it) {
        cur_ins = *it;

        if (cur_ins.first == "forward") {
            horpos += cur_ins.second;
        }
        else if (cur_ins.first == "up") {
            depth -= cur_ins.second;
        }
        else if (cur_ins.first == "down") {
            depth += cur_ins.second;
        }
        else {
            throw invalid_argument("WTF???");
        }
    }

    return horpos * depth;
}


int part_2(instructions instrs)
{
    int horpos = 0;
    int depth = 0;
    int aim = 0;
    pair<string, int> cur_ins;

    for (instructions::iterator it = instrs.begin(); it != instrs.end(); ++it) {
        cur_ins = *it;

        if (cur_ins.first == "forward") {
            horpos += cur_ins.second;
            depth += (aim * cur_ins.second);
        }
        else if (cur_ins.first == "up") {
            aim -= cur_ins.second;
        }
        else if (cur_ins.first == "down") {
            aim += cur_ins.second;
        }
        else {
            throw invalid_argument("WTF???");
        }
    }

    return horpos * depth;
}


int main()
{
    instructions instrs = read_input();
    cout << part_1(instrs) << endl;
    cout << part_2(instrs) << endl;
}

