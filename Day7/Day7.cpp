#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <limits>
#include <algorithm>


std::vector<int> split_line(std::string str, char splitchar)
{
    std::stringstream ss(str);
    std::vector<int> vect;

    for (int i; ss >> i;) {
        vect.push_back(i);
        if (ss.peek() == splitchar)
            ss.ignore();
    }

    return vect;
}

int part_1(const std::vector<int>& poss)
{
    int min_pos = *std::min_element(poss.begin(), poss.end());
    int max_pos = *std::max_element(poss.begin(), poss.end());

    int cost = std::numeric_limits<int>::max();

    for (int i = min_pos; i <= max_pos; ++i) {
        int cur_cost = 0;
        for (int p : poss) cur_cost += std::abs(i - p);
		cost = std::min(cur_cost, cost);
    }

    return cost;
}

int part_2(const std::vector<int>& poss)
{
    int min_pos = *std::min_element(poss.begin(), poss.end());
    int max_pos = *std::max_element(poss.begin(), poss.end());
    int cost = std::numeric_limits<int>::max();

    for (int i = min_pos; i <= max_pos; ++i) {
		int cur_cost = 0;
        for (int p : poss) {
            int n = std::abs(p - i);
            cur_cost += (n * (n + 1)) / 2;
        }
		cost = std::min(cur_cost, cost);
    }

    return cost;

}


int main()
{
    std::cout << "Hello World!\n";
    std::string test_line = "16,1,2,0,4,2,7,1,2,14";
    std::ifstream input_file("input.txt");
    std::string line;
    input_file >> line;

    std::vector<int> positions = split_line(line, ',');
    std::cout << part_1(positions) << std::endl;
    std::cout << part_2(positions) << std::endl;
}

