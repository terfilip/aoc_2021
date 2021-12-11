#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using std::ifstream; using std::cout; using std::endl;
using std::vector;

typedef struct p1result{
    vector<int> numbers;
    int n_increases;
} p1result;

p1result part_1()
{

    ifstream input_file("input.txt");
    vector<int> numbers;

    int prev_number = -1; int number = 0; int n_increases = 0;

    while (input_file >> number) {
        if (prev_number < number && prev_number != -1) n_increases++;
        prev_number = number;
        numbers.push_back(number);
    }
    
    return p1result {numbers, n_increases};
}


int part_2(vector<int> numbers)
{
    int prev_win = std::numeric_limits<int>::max();
    int cur_win = 0;
    int n_increases = 0;
    for (int i = 2; i < numbers.size(); i++) {
        cur_win = numbers[i] + numbers[i - 1] + numbers[i - 2];
        if (cur_win > prev_win) n_increases++;
        prev_win = cur_win;
    }

    return n_increases;
}



int main() {
    p1result p1res = part_1();
    cout << "Part 1: " << p1res.n_increases << endl;
    cout << "Part 2: " << part_2(p1res.numbers) << endl;
}
