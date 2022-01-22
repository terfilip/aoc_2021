#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <queue>
#include <set>
#include <cstring>
#include <algorithm>

using std::cout;
using std::ifstream;
using std::endl;
using std::string;
using std::unordered_map;
using std::vector;
using std::set;
using std::unique_ptr;

typedef unordered_map<string, set<string>> graph_t;

void print_graph(graph_t graph) {
    cout << "GRAPH :: " << endl;
    for (const auto& [src, nodes] : graph) {
        cout << src << "->" << endl;
        for (const auto& item : nodes) {
            cout << "\t\t"<< item << endl;
        }
    }
}


bool islower_cave(const string& str) {
    return ((str != "end") &&
            (str != "start") &&
            std::all_of(str.begin(),
                        str.end(),
                        [](const char c) {return std::islower(c); }));
}

bool path_is_valid(const unique_ptr<vector<string>>& path, const int low_cave_thresh) {
    int low_cave_count = 0;
    bool has_one_start = std::count(path->begin(), path->end(), "start") == 1;
    bool valid_end = std::count(path->begin(), path->end(), "end") <=1;
    if ((!has_one_start) || (!valid_end))
        return false;

    for (const auto& item : *path) {
        if (islower_cave(item)) {
            unsigned long long itemcnt = std::count(path->begin(), path->end(), item);
            if (itemcnt > low_cave_thresh) {
                return false;
            }
        }
        low_cave_count += islower_cave(item);
    }

    return true;
}


int solve(graph_t& graph, const int low_cave_thresh) {
    
    std::queue<unique_ptr<vector<string>>> node_q;
    string root = "start";
    string sink = "end";
    int path_ctr = 0;

    unique_ptr<vector<string>> cur_path_to_sink = std::make_unique<vector<string>>();
    cur_path_to_sink->push_back(root);
    node_q.push(std::move(cur_path_to_sink));

    while (!node_q.empty()) {
        unique_ptr<vector<string>> path = std::move(node_q.front());
        string node = path->back();
        node_q.pop();

        if (node == sink) {

            //if (path_is_valid(path)) {
                path_ctr++;
                /*
                for (const auto& thing : path) {
                    cout << thing << " ";
                }
                cout << endl;
                */
            //}
        }

        for (const string& adj : graph[node]) {
            if (adj != "start") {
                unique_ptr<vector<string>> new_path = std::make_unique<vector<string>>();
                std::copy(path->begin(), path->end(), std::back_inserter(*new_path));
                new_path->push_back(adj);
                if (path_is_valid(new_path, low_cave_thresh)) {
                    node_q.push(std::move(new_path));
                }
            }
        }
    }

    return path_ctr;

}

void graph_insert(graph_t& graph, string& src, string& dst) {
    if (graph.find(src) != graph.end()) {
        graph[src].insert(dst);
    }
    else {
        set<string> v {dst};
        graph[src] = v;
    }
}


int main()
{
    ifstream input_file("input.txt");
    string line;
    graph_t graph;

    while (std::getline(input_file, line)) {
        size_t dashpos = line.find("-");
        string src = line.substr(0, dashpos);
        string dst = line.substr(dashpos + 1, line.size());
        graph_insert(graph, src, dst);
        graph_insert(graph, dst, src);
    }

    //print_graph(graph);
    cout << "Part 1: " << solve(graph, 1) << endl;
}
