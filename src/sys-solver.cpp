#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <limits>
#include <iomanip> 

using namespace std;

int check_convergence(unordered_map<string, double> previous, unordered_map<string, double> current, double tolerance){
    double max_diff = 0;

    for(const auto& pair : previous){
        string key = pair.first;
        double prev_value = pair.second;
        double curr_value = current[key];
        double diff = abs(curr_value - prev_value);
        if(diff > max_diff){
            max_diff = diff;
        }
    }
    return max_diff <= tolerance ? 0 : 1;
}

int main(int argc, char* argv[]) {
    string filename = argv[1];
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return 1;
    } else {
        cout << "==============================" << endl;
        cout << "solving :" << filename << endl;
    }
    string line;

    unordered_map<string, double> cityToIndex;
    unordered_map<string, double> cityToAmount;
    unordered_map<string, double> cityToAmount_previous;
    vector<string> indexToCity;
    vector<tuple<string, string, double>> connections;

    while (getline(file, line)) {
        stringstream ss(line);
        string city1, city2;
        int value;

        ss >> city1;
        if (ss >> city2) {
            if (ss >> value) {
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
                    cityToAmount[city1] = stoi(city2);
                    connections.emplace_back(city1, city1, stoi(city2));
            }
        }
    }

    int N = cityToIndex.size();
    vector<vector<double>> matrix(N, vector<double>(N, 0)); 

    for (const auto& [from, to, value] : connections) {
        int i = cityToIndex[to];
        int j = cityToIndex[from];
        matrix[i][j] = value;
    }


    for(int max_it = 0; max_it < stoi(argv[2]); max_it++){
        cityToAmount_previous = cityToAmount;
        for(int i = 0; i < N; i++){
            double accumm = 0;
            for(int j = 0; j < N; j++){
                if(i == j){
                    accumm += matrix[i][j];
                } else {
                    accumm += cityToAmount[indexToCity[j]] * (double(matrix[i][j])/100);
                }
            }
            cityToAmount[indexToCity[i]] = accumm;
        }
        if(!check_convergence(cityToAmount_previous, cityToAmount, 1e-6)){
            break;
        }
    }

    double max_people = numeric_limits<double>::lowest();
    double min_people = numeric_limits<double>::max();
    string max_city, min_city;

    for (const auto& pair : cityToAmount) {
        if (pair.second > max_people) {
            max_people = pair.second;
            max_city = pair.first;
        }
        if (pair.second < min_people) {
            min_people = pair.second;
            min_city = pair.first;
        }
    }

    cout << fixed << setprecision(5);
    cout << "City with the most amount of arrivals : " << max_city << " -> " << max_people << endl;
    cout << "City with the least amount of arrivals: " << min_city << " -> " << min_people << endl;

    return 0;
}
