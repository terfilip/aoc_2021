#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using std::vector;
using std::cout;
using std::ifstream;
using std::string;
using std::endl;

typedef vector<vector<short>> grid; 

vector<short> get_neighbours(const grid& grid, int i, int j) {
    
    vector<short> neighbours;
    if ((i + 1) < grid.size())
        neighbours.push_back(grid[i + 1][j]);

    if ((i - 1) >= 0)
        neighbours.push_back(grid[i - 1][j]);

    if ((j - 1) >= 0)
        neighbours.push_back(grid[i][j - 1]);

    if ((j + 1) < grid[0].size())
        neighbours.push_back(grid[i][j + 1]);

    return neighbours;
}

int part_1(const grid& grid) {
    int risk_level_sum = 0;

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            short value = grid[i][j];
            vector<short> neighbours = get_neighbours(grid, i, j);

            bool all_greater = true;
            for (const auto& neigh : neighbours) {
                if (value >= neigh) {
                    all_greater = false;
                    break;
                }
            }

            if (all_greater)
                risk_level_sum += (value + 1);
        }
    }

    return risk_level_sum;
}

int find_basin_size(const grid& grid, int i, int j, vector<vector<bool>>& visited) {

    int basin_size;

    if (visited[i][j]) {
        basin_size = 0;
    }
    else {
        basin_size = 1;
        visited[i][j] = true;
    }

    if (((i + 1) < grid.size()) && (grid[i + 1][j] < 9) && (grid[i + 1][j] > grid[i][j]))
        basin_size += find_basin_size(grid, i + 1, j, visited);

    if (((i - 1) >= 0) && (grid[i - 1][j] < 9) && (grid[i - 1][j] > grid[i][j]))
        basin_size += find_basin_size(grid, i - 1, j, visited);

    if (((j - 1) >= 0) && (grid[i][j - 1] < 9) && (grid[i][j - 1] > grid[i][j]))
        basin_size += find_basin_size(grid, i, j - 1, visited);

    if (((j + 1) < grid[0].size()) && (grid[i][j + 1] < 9) && (grid[i][j + 1] > grid[i][j]))
        basin_size += find_basin_size(grid, i, j + 1, visited);

    return basin_size;

}


int part_2(const grid& grid) {

    vector<int> basin_sizes;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            short value = grid[i][j];
            vector<short> neighbours = get_neighbours(grid, i, j);

            bool all_greater = true;
            for (const auto& neigh : neighbours) {
                if (value >= neigh) {
                    all_greater = false;
                    break;
                }
            }

            if (all_greater) {
                vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size()));
                int basin_size = find_basin_size(grid, i, j, visited);
                basin_sizes.push_back(basin_size);
            }
        }
    }

    std::sort(basin_sizes.begin(), basin_sizes.end(), std::greater<>());
    cout << endl;
    return basin_sizes[0] * basin_sizes[1] * basin_sizes[2];
}


int main()
{
    ifstream file("input.txt");
    grid grid;    

    char c;
    vector<short> digit_line;
    while (file.get(c)) {
        if (c == '\n') {
            grid.push_back(digit_line);
            digit_line.clear();
        }
        else {
            digit_line.push_back(c - '0');
        }
    }
    grid.push_back(digit_line);
    cout << "Part 1: " << part_1(grid) << endl;
    cout << "Part 2: " << part_2(grid) << endl;
}
