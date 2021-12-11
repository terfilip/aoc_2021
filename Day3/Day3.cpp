#include <iostream>
#include <fstream>
#include <numeric>
#include <assert.h>
#include <vector>
#include <limits>

using namespace std;
const int N_DIGITS = 12;
const int MAXINTVAL = numeric_limits<int>::max();
constexpr int N_ROWS = 1000;
const int N_HALF_ROWS = 500;
typedef unsigned int uint;


int most_common_bit(const vector<vector<uint>>& numbers,
                    int colnum,
                    const vector<uint>& indices)
{
    int zero_cnt = 0;
    int one_cnt = 0;

    for (const uint index : indices) {
        if (numbers[index][colnum] == 0) {
            zero_cnt++;
        }
        else {
            one_cnt++;
        }
    }

    if (zero_cnt > one_cnt) {
        return 0;
    }
    else {
        return 1;
    }
    
}


unique_ptr<vector<uint>> indices_of_bit(const vector<vector<uint>>& numbers,
                                        int colnum,
                                        const unique_ptr<vector<uint>>& indices,
                                        uint bitval)
{
    unique_ptr<vector<uint>> new_indices = make_unique<vector<uint>>();

    for (auto index : (*indices)) {
        if (numbers[index][colnum] == bitval) {
            (*new_indices).push_back(index);
        }
    }

    return new_indices;
}


int get_num_of_interest(const vector<vector<uint>>& numbers, int thingie)
{
    unique_ptr<vector<uint>> indices = make_unique<vector<uint>>(N_ROWS);
    iota(( * indices).begin(), (*indices).end(), 0);

    for (int colnum = 0; colnum < N_DIGITS; ++colnum) {
        int mcb = most_common_bit(numbers, colnum, (*indices)) ^ thingie;
        unique_ptr<vector<uint>> next_indices = indices_of_bit(numbers, colnum, indices, mcb);
		if ((*next_indices).size() == 1) {
            break;
        }
        indices = move(next_indices);
    }
    
    int ans = 0;
    int rownum = (*indices)[0];
    for (int i = 0; i < N_DIGITS; i++) {
        ans += numbers[rownum][i];
        ans <<= 1;
    }
    ans >>= 1;
    return ans;
}

int part_2(const vector<vector<uint>>& numbers)
{
    int ogr = get_num_of_interest(numbers, 0);
    int cosr = get_num_of_interest(numbers, 1);
    return ogr * cosr;
}

int main()
{
    std::cout << "Hello World!\n";

    ifstream input_file("input.txt");
    int digits[N_DIGITS] = { 0 };
    vector<vector<uint>> numbers(N_ROWS, vector<uint>(N_DIGITS));

    char byte = 0;
    int ctr = 0;
    int rowctr = 0;


    while (input_file.get(byte)) {

        
        if (byte == '\n') {
            ctr = 0;
            rowctr++;
            continue;
        }

        int value = byte - '0';
        digits[ctr] += value;
        numbers[rowctr][ctr] = value;
		++ctr;
    }

    int gam = 0;
    int eps = 0;

    for (int ndig : digits) {
        gam += (ndig > N_HALF_ROWS);
        eps += (ndig <= N_HALF_ROWS);
        gam <<= 1;
        eps <<= 1;
    }
    gam >>= 1;
    eps >>= 1;
    cout << "Part 1: " << gam * eps << endl;
    cout << "Part 2: " << part_2(numbers) << endl;    
}

