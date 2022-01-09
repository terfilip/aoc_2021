#include <iostream>
#include <fstream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::ifstream;

typedef vector<vector<short>> grid;

int octo_flash(grid& grid, int i, int j) {

}


int step(grid& grid) {

    int flash_cnt = 0;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            
        }
    }

}

int main()
{
    ifstream input_file("input.txt");
    grid grid;
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

    
    for (int i = 0; i < 100; ++i) {
        flash_cnt += step(grid);
    }
    
    cout << "Part 1: " << flash_cnt << endl;
    
}

