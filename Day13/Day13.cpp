#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>

using std::string;
using std::cout; 
using std::endl;
using std::vector;
using std::ifstream;

typedef vector<vector<bool>> paper_t;
constexpr bool USE_TEST = false;


template<typename T, typename U>
void print_pairs(const vector<std::pair<T, U>>& vec) {

    for (const auto& [first, second] : vec) {
        cout << first << " - " << second << endl;
    }
    cout << endl;

}

void print_grid(const paper_t& grid) {
    for (const auto& line : grid) {
        for (const auto& item : line) {
            char thingie = item ? '#' : '.';
            cout << thingie;
        }
        cout << endl;
    }
    cout << endl;
}


void print_grid_lim(const paper_t& grid, int xlim, int ylim) {
    for (int i = 0; i < ylim; i++) {
        for (int j =0 ; j < xlim; j++) {
            bool item = grid[i][j];
            char thingie = item ? '#' : '.';
            cout << thingie;
        }
        cout << endl;
    }
    cout << endl;
}

int count_dots(const paper_t& grid, size_t ylim, size_t xlim) {
    int sum = 0;

    for (int i = 0; i < ylim; i++) {
        for (int j = 0; j < xlim; j++) {
            sum += grid[i][j];
        }
    }

    return sum;
}


void fold_x(paper_t& grid, size_t fold_xpos, size_t ylim) {
    for (size_t i = 0; i < ylim; i++) {
        for (size_t j = 0; j < fold_xpos; j++) {
            bool mirror_value = grid[i][(2 * fold_xpos) - j];
            grid[i][j] = grid[i][j] || mirror_value;
        }
    }
}

void fold_y(paper_t& grid, size_t xlim, size_t fold_ypos) {

    for (size_t i = 0; i < fold_ypos; i++) {
        for (size_t j = 0; j < xlim; j++) {
            bool mirror_value = grid[(2 * fold_ypos) - i][j];
            grid[i][j] = grid[i][j] || mirror_value;
        }
    }

}


int main()
{
    ifstream ifile ( USE_TEST ? "test_input.txt" : "input.txt");
    string line;
    vector<std::pair<int,int>> dot_coords;
    vector<std::pair<char,int>> fold_instrs;
    bool folds = false;
    int maxx = 0; int maxy = 0;

    while (std::getline(ifile, line)) {
        if (line == ""){
             folds = true;
             continue;
         }

        if (!folds) {
            size_t comma = line.find(",");
            int xc = std::stoi(line.substr(0, comma));
            int yc = std::stoi(line.substr(comma + 1, line.size()));
            maxx = std::max(xc, maxx);
            maxy = std::max(yc, maxy);
            dot_coords.push_back(std::make_pair(xc, yc));
        }
        else {
            size_t eqix = line.find("=");
            char axis = line[eqix - 1];
            int coord = std::stoi(line.substr(eqix + 1, line.size()));
            fold_instrs.push_back(std::make_pair(axis, coord));
        }
    }

    // +10 bottom due to instruction going over half of grid
    paper_t paper (maxy + 10, vector<bool>(maxx + 1, false));
    auto first_instr = fold_instrs[0];
    size_t p1;

    cout << paper.size() <<  "  " << paper[0].size() << endl;
    for (const auto& [x, y] : dot_coords) {
        paper[y][x] = true;
    }
    paper_t paper_p2;
    std::copy(paper.begin(), paper.end(), std::back_inserter(paper_p2));
    cout << endl;

    if (USE_TEST)
        print_grid(paper);

    if (first_instr.first == 'x') {
        fold_x(paper, fold_instrs[0].second, paper.size());
        p1 = count_dots(paper, paper.size(), fold_instrs[0].second);
        cout << "Part 1: " << p1 << endl;
    }
    else if (first_instr.first == 'y') {
        fold_y(paper, paper[0].size(), fold_instrs[0].second );
        p1 = count_dots(paper, fold_instrs[0].second, paper[0].size());
        cout << "Part 1: " << p1 << endl;
    }
    else {
        throw "wtf";
    }

    if (USE_TEST)
        print_grid(paper_p2);

    size_t xlim = paper_p2[0].size();
    size_t ylim = paper_p2.size();

    for (const auto& instr : fold_instrs) {
        if (instr.first == 'x') {
            xlim = instr.second;
            fold_x(paper_p2, xlim, ylim);
        }
        else if (instr.first == 'y') {
            ylim = instr.second;
            fold_y(paper_p2, xlim, ylim);
        }
        else {
            throw "wtf";
        }
    }
    cout << "Part 2: " << endl;
    print_grid_lim(paper_p2, xlim, ylim);
}
