#include <iostream>
#include <regex>
#include <string>
#include <utility>
#include <fstream>
#include <algorithm>

using namespace std;


int get_overlap(vector<vector<int>>& grid) {

    int overlap_cnt = 0;

    for (const auto& row : grid) {
        for (int num : row) {
            if (num > 1) {
                overlap_cnt++;
            }
        }
    }

    return overlap_cnt;
}


int part_n(const vector<pair<pair<int, int>, pair<int, int>>>& inputs, int n, int max_x, int max_y) {

    vector<vector<int>> grid(max_y + 1, vector<int>(max_x + 1));
    
    for (auto instr_line : inputs) {
        int x1 = instr_line.first.first;
        int y1 = instr_line.first.second;
        int x2 = instr_line.second.first;
        int y2 = instr_line.second.second;

        if (n == 1) {
            if (x1 == x2) {
                int start = min({ y1, y2 });
                int end = max({ y1, y2 });

                for (int i = start; i <= end; ++i) {
                    grid[i][x1] ++;
                }
            }
            else if (y1 == y2) {
                int start = min({ x1, x2 });
                int end = max({ x1, x2 });
                for (int j = start; j <= end; ++j) {
                    grid[y1][j] ++;
                }
            }
        }
        else if (n == 2) {
            int xpos = x1;
            int ypos = y1;

            while ((xpos != x2) || (ypos != y2)) {
                grid[ypos][xpos]++;
                if (xpos != x2) {
                    if (x1 > x2) {
                        xpos--;
                    }
                    else {
                        xpos++;
                    }
                }

                if (ypos != y2) {
                    if (y1 > y2) {
                        ypos--;
                    }
                    else {
                        ypos++;
                    }
                }
            }
            grid[y2][x2]++;
        }
        else {
            throw runtime_error("wtf");
        }

    }

    return get_overlap(grid);

}

int main()
{
    ifstream ifl("input.txt");
    string line;
    int max_x = 0;
    int max_y = 0;
    vector<pair<pair<int, int>, pair<int, int>>> input_lines;


    while (getline(ifl, line)) {
        //cout << line << endl;
        size_t first_comma_index = line.find(",");
        size_t second_comma_index = line.find(",", first_comma_index + 1);
        size_t splitter_index = line.find(" -> ");

        int x1 = stoi(line.substr(0, first_comma_index));
        int y1 = stoi(line.substr(first_comma_index + 1, splitter_index));
        int x2 = stoi(line.substr(splitter_index + 4, second_comma_index));
        int y2 = stoi(line.substr(second_comma_index + 1, line.size()));


        max_x = max({max_x, x1, x2});
        max_y = max({ max_y, y1, y2 });
        input_lines.push_back(make_pair(make_pair(x1, y1), make_pair(x2, y2)));
    }

    vector<vector<int>> grid(max_y + 1, vector<int>(max_x + 1));

    cout << grid.size() << endl;
    cout << grid[0].size() << endl;


    cout << "Part 1: " << part_n(input_lines, 1, max_x, max_y) << endl;
    cout << "Part 2: " << part_n(input_lines, 2, max_x, max_y) << endl;
}

