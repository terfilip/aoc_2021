#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <utility>

using std::cout;
using std::endl;
using std::vector;
using std::ifstream;

typedef vector<vector<short>> grid_t;

void octo_flash(grid_t& grid, int i, int j, const std::set<std::pair<int,int>>& flashed_this_cycle) {
    grid[i][j] = 0;

    for (int ii=-1; ii<2; ii++)
        for (int jj = -1; jj < 2; jj++) {
            int iii = i+ii;
            int jjj = j+jj;
            if ((iii < grid.size()) &&
                (jjj < grid[0].size()) &&
                (iii >= 0) &&
                (jjj >= 0) &&
                ((ii != 0) || (jj != 0)) &&
                (   flashed_this_cycle.find(std::make_pair(iii,jjj)) == 
                    flashed_this_cycle.end())   ) {
                grid[iii][jjj]++;
            }
        }
}

void print_grid(const grid_t& grid) {
    for (const auto& line : grid) {
        for (const auto& item: line) {
            cout << item;
        }
        cout << endl;
    }
    cout <<endl << endl;
}

int step(grid_t& grid) {

    int flash_cnt = 0;
    int current_flash_cnt = 0;
    std::set<std::pair<int, int>> flashed_this_cycle;

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            grid[i][j]++;
        }
    }
    
    do {
        current_flash_cnt = 0;
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[i].size(); ++j) {
                if (grid[i][j] > 9) {
                    auto coords = std::make_pair(i,j);
                    flashed_this_cycle.insert(coords);
                    octo_flash(grid, i, j, flashed_this_cycle);
                    current_flash_cnt++;
                }
            }
        }
        flash_cnt += current_flash_cnt;
    } while (current_flash_cnt > 0);
        

    return flash_cnt;
}

int main()
{
    ifstream input_file("input.txt");
    grid_t grid;
    vector<short> gridline;
    char c;
    int flash_cnt = 0;

    while (input_file.get(c)) {
        if (c == '\n') {
            grid.push_back(gridline);
            gridline.clear();
        }
        else {
            gridline.push_back(c - '0');
        }
    }
    grid.push_back(gridline);
    grid_t p2g;
    std::copy(grid.begin(), grid.end(), std::back_inserter(p2g));

    for (int i = 0; i < 100; ++i) {
        flash_cnt += step(grid);
    }
    cout << "Part 1: " << flash_cnt << endl;
    
    flash_cnt = 0;
    int i;
    for (i = 0; flash_cnt != 100 ; ++i) {
        flash_cnt = step(p2g);
    }
    cout << "Part 2: " << i << endl;
}

