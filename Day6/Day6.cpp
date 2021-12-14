// Day6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <unordered_map>


typedef unsigned long long ulong;

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


ulong fish_sim(const std::vector<int>& fish_sizes, const int n_days) 
{
    std::unordered_map<int, ulong> fish_dict;

    //Fish Initializer Begin
    for (auto fshsz : fish_sizes) fish_dict[fshsz]++;

    for (int i = 0; i <= 8; ++i)
        if (fish_dict.find(i) == fish_dict.end())
            fish_dict[i] = 0ULL;
    //Fish Initializer End

    for (int i = 0; i < n_days; ++i) {
		ulong fish_to_spawn = fish_dict[0];

        for (int j = 1; j <= 8; ++j) {
            fish_dict[j - 1] = fish_dict[j];
        }
        fish_dict[6] += fish_to_spawn;
        fish_dict[8] = fish_to_spawn;
    }

    ulong fish_sum = 0;
    for (const auto& f : fish_dict) fish_sum += f.second;
    
    return fish_sum;

}


int main()
{
    std::cout << "Hello World!\n";
    std::string test_line = "3,4,3,1,2";
    std::ifstream ifile("input.txt");
    std::string line;

    ifile >> line;
    
    std::vector<int> fish_sizes = split_line(line, ',');

    std::cout << fish_sim(fish_sizes, 80) << std::endl;
    std::cout << fish_sim(fish_sizes, 256) << std::endl;
}
