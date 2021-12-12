#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <sstream>
#include <algorithm>
#include <set>

using namespace std;
constexpr int BOARD_N_ROWS = 5;
constexpr int BOARD_N_COLS = 5;
typedef unsigned int uint;


vector<uint> split_line(string str, char splitchar)
{
	stringstream ss(str);
    vector<uint> vect;

    for (int i; ss >> i;) {
        vect.push_back(i);
        if (ss.peek() == splitchar)
            ss.ignore();
    }
    
    return vect;
}


bool board_has_won(const vector<vector<uint>>& board, const set<uint>& chosen_numbers)
{
    for (const vector<uint>& row : board) {
        bool all_present = row.size() != 0;

        for (const uint& value : row) {
            all_present = all_present && (chosen_numbers.find(value) != chosen_numbers.end());
        }
        if (all_present) {
            return true;
        }

    }

    for (int colnum = 0; colnum < BOARD_N_COLS; ++colnum) {
        bool all_present = true;

        for (int rownum = 0; rownum < BOARD_N_ROWS; ++ rownum) {
            uint value = board[colnum][rownum];
            all_present = all_present && (chosen_numbers.find(value) != chosen_numbers.end());
        }
        if (all_present) {
            return true;
        }
    }
    return false;
}

int part_n(const vector<vector<vector<uint>>> const & boards, const vector<uint> const & chosen_numbers, int n)
{
    set<uint> drawn_numbers;
    vector<vector<uint>> victorious_board;
    vector<int> victorious_boards;
    int latest_chosen_number = -1;

    for (int i = 0; i < chosen_numbers.size(); ++i) {
        drawn_numbers.insert(chosen_numbers[i]);
        if (i < 4) {
            continue;
        }
        for (int j = 0; j < boards.size(); ++j) { 
            const vector<vector<uint>>& board = boards[j];
            if (board_has_won(board, drawn_numbers)) {
                latest_chosen_number = chosen_numbers[i];
                if (n == 1) {
					victorious_board = board;
                    goto loopend;
                }
                else {
                    if (find(victorious_boards.begin(), victorious_boards.end(), j) == victorious_boards.end()) {
                        victorious_boards.push_back(j);
                    }

                    if (victorious_boards.size() == boards.size()) {
                        goto loopend;
                    }
                }
            }
        }
    }
    loopend:

    if (latest_chosen_number == - 1) {
		throw runtime_error("wtf");
    }

    if (n == 2) {
        victorious_board = boards[victorious_boards.back()];
    }


    uint sum_of_unmarked_numbers = 0;
    for (auto row : victorious_board) {
        for (auto value : row) {
            if (drawn_numbers.find(value) == drawn_numbers.end())
                sum_of_unmarked_numbers += value;
        }
    }
    
    return sum_of_unmarked_numbers * latest_chosen_number;
}


int main()
{
    vector<vector<vector<uint>>> boards(0, vector<vector<uint>>(BOARD_N_ROWS, vector<uint>(BOARD_N_COLS)));
    ifstream ifile("input.txt");
    string line;
    getline(ifile, line);
    vector<uint> chosen_numbers = split_line(line, ',');
    copy(chosen_numbers.begin(), chosen_numbers.end(), back_inserter(chosen_numbers));


    getline(ifile, line);
    vector<vector<uint>> curboard;

    int board_index = 0;


    while (getline(ifile, line)) {
        if (line == "") {
            boards.push_back(curboard);
            curboard = vector<vector<uint>>();
            continue;
        }
        
        vector<uint> row = split_line(line, ' ');
        curboard.push_back(row);
    }



    cout << "Part 1: " << part_n(boards, chosen_numbers, 1) << endl;
    cout << "Part 2: " << part_n(boards, chosen_numbers, 2) << endl;


}

