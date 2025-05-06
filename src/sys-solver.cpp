#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <limits>

using namespace std;

int main() {
    ifstream file("cases/caso10.txt");
    string line;

    unordered_map<string, int> cityToIndex;
    unordered_map<string, int> cityToAmount;
    vector<string> indexToCity;
    vector<tuple<string, string, int>> connections;

    // First pass: collect cities and values
    while (getline(file, line)) {
        stringstream ss(line);
        string city1, city2;
        int value;

        ss >> city1;
        if (ss >> city2) {
            if (ss >> value) {
                // This line has a connection (3 entries)
                connections.emplace_back(city1, city2, value);
                if (cityToIndex.find(city1) == cityToIndex.end()) {
                    cityToIndex[city1] = cityToIndex.size();
                    indexToCity.push_back(city1);
                }
                if (cityToIndex.find(city2) == cityToIndex.end()) {
                    cityToIndex[city2] = cityToIndex.size();
                    indexToCity.push_back(city2);
                }
            } else {
                // This line has a city and its value (2 entries)
                if (cityToIndex.find(city1) == cityToIndex.end()) {
                    cityToIndex[city1] = cityToIndex.size();
                    cityToAmount[city1] = stoi(city2);
                    indexToCity.push_back(city1);
                }
            }
        }
    }

    int N = cityToIndex.size();
    vector<vector<int>> matrix(N, vector<int>(N, 0)); // or INT_MAX if you prefer

    // Populate the matrix with the connections
    for (const auto& [from, to, value] : connections) {
        int i = cityToIndex[from];
        int j = cityToIndex[to];
        matrix[i][j] = value;
    }



    return 0;
}
