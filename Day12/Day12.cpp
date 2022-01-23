#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <queue>
#include <stack>
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
using std::shared_ptr;

typedef unordered_map<string, set<string>> graph_t;

constexpr bool DEBUG_MODE = false;


bool str_islower(const string& str) {
    return std::all_of(str.begin(),
                        str.end(),
                        [](const char c) {return std::islower(c); });
}

class Path {

    public:
        string back_node;
        string double_occ_cave;
        unordered_map<string, int> lower_cave_counts;
        vector<string> debug_vector;

        Path(string back_node) {
            this->back_node = back_node;
            this->lower_cave_counts = {};
            this->double_occ_cave = "";

            if (DEBUG_MODE)
                this->debug_vector.push_back(back_node);

            if (str_islower(back_node))
                this->lower_cave_counts[back_node]++;
        }
        Path(const shared_ptr<Path> other) {
            this->back_node = other->back_node;
            this->double_occ_cave = other->double_occ_cave;
            this->lower_cave_counts = other->lower_cave_counts;

            if (DEBUG_MODE)
                std::copy(other->debug_vector.begin(), other->debug_vector.end(), std::back_inserter(this->debug_vector));
        }
        bool add_next_node(string next_node, bool isp2) {
            this->back_node = next_node;
            bool next_is_lower_cave = str_islower(next_node);

            if (DEBUG_MODE)
                this->debug_vector.push_back(next_node);

            if (!next_is_lower_cave) return true;

            if (this->lower_cave_counts.find(next_node) == this->lower_cave_counts.end()) {
                this->lower_cave_counts[next_node] = 1;
                return true;
            }
            this->lower_cave_counts[next_node]++;
            int lcc = this->lower_cave_counts[next_node];

            if (lcc <= 1) {
                return true;
            }
            else if (!isp2) {
                return false;
            }
            else if (isp2) {
                if ((next_node == "start") || (next_node == "end")) {
                    return false;
                }
                else if ((lcc == 2) && (this->double_occ_cave == "")) {
                    this->double_occ_cave = next_node;
                    return true;
                }
                else if ((lcc == 2) &&(this ->double_occ_cave != next_node)) {return false;}
                else {
                    return false;
                }
            }
             
            
        }
};


void print_graph(graph_t graph) {
    cout << "GRAPH :: " << endl;
    for (const auto& [src, nodes] : graph) {
        cout << src << "->" << endl;
        for (const auto& item : nodes) {
            cout << "\t\t"<< item << endl;
        }
    }
}

void vecprint(vector<string> things) {
    cout<< "Vector:    " << endl;
    for (const auto& thing : things) {
        cout << thing << " ";
    }
    cout << endl;
}


int solve(graph_t& graph, bool p2) {
    
    std::queue<unique_ptr<Path>> node_q;
    string root = "start";
    string sink = "end";
    int path_ctr = 0;

    unique_ptr<Path> first = std::make_unique<Path>(root);
    node_q.push(std::move(first));

    while (!node_q.empty()) {
        shared_ptr<Path> path = std::move(node_q.front());
        string node = path->back_node;
        node_q.pop();

        if (node == sink) {
            if (DEBUG_MODE)
                vecprint(path->debug_vector);
            path_ctr++;
        }

        for (const string adj : graph[node]) {
            unique_ptr<Path> next_path = std::make_unique<Path>(path);
            bool next_is_valid = next_path->add_next_node(adj, p2);
            if (next_is_valid) {
                node_q.push(std::move(next_path));
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

    cout << "Part 1: " << solve(graph, false) << endl;
    cout << "Part 2: " << solve(graph, true) << endl;
}

