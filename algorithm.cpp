/*
Filename: algorithm.cpp
Author: Dhruv Somani
Permanent Repository: https://github.com/dhruvsomani/Sliding-Puzzle
*/

#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <ctype.h>
#include <assert.h>
//#include <unistd.h>

using namespace std;

vector<string> solve8Puzzle(string state);
vector<string> reconstructPath(map<string, string> cameFrom, string current);
vector<string> find8Neighbors(string state);
int calc8fScore(string state);
int to_decimal(char hexadecimal);

int main() {
    /*
    string state;
    getline(cin, state);
    cout << endl;
    */

    string state = "123740865";

    vector<string> solution = solve8Puzzle(state);
    cout << "Solution:" << endl;
    for (int index = 0; index < solution.size(); index++) cout << solution[index].substr(0, 3) << endl
                << solution[index].substr(3, 3) << endl
                << solution[index].substr(6, 3) << endl << endl;


    cout << "Length: " << solution.size() - 1;

    int t;
    cin >> t;

    return 0;
}


vector<string> solve8Puzzle(string state) {
    assert (state.length() == 9);

    vector<string> frontier;
    vector<string> visited;
    map<string, string> cameFrom;

    frontier.push_back(state);

    map<string, float> fScore;
    map<string, int> gScore;
    gScore[state] = 0;

    while (frontier.size() > 0) {

        int best_choice = 0;
        float minimum = 120;

        for (unsigned int index = 0; index < frontier.size(); index++) {
            if (fScore[frontier[index]] < minimum) {
                best_choice = index;
                minimum = fScore[frontier[index]];
            }

        }

        string curr_state = frontier[best_choice];
        frontier.erase(frontier.begin() + best_choice);
        visited.push_back(curr_state);

        if (curr_state == "123456780") {
            vector<string> path = reconstructPath(cameFrom, curr_state);

            cout << "Nodes Explored: " << fScore.size() << endl;

            return path;
        }

        vector<string> neighbors = find8Neighbors(curr_state);

        for (unsigned int index = 0; index < neighbors.size(); index++) {
            string neighbor = neighbors[index];
            if (find(visited.begin(), visited.end(), neighbor) != visited.end()) continue;

            if (find(frontier.begin(), frontier.end(), neighbor) == frontier.end())frontier.push_back(neighbor);
            else if ((gScore[curr_state] + 1) >= gScore[neighbor]) continue;

            // This path is the best until now. Record it!
            cameFrom[neighbor] = curr_state;
            gScore[neighbor] = gScore[curr_state] + 1;
            fScore[neighbor] = calc8fScore(neighbor) + gScore[neighbor];

        }

        // mapping >>>>>>>>>>>>>>>>>>>>>>>>>>>
        //for (std::map<string,float>::iterator it=fScore.begin(); it!=fScore.end(); ++it) {
        //    std::cout << it->first << " => " << it->second << '\n';}
        //cout << endl;
    }

    return vector<string>();

}

vector<string> reconstructPath(map<string, string> cameFrom, string current) {
    vector<string> totalPath;
    totalPath.push_back(current);

    while (cameFrom.find(current) != cameFrom.end()) {
        current = cameFrom[current];
        totalPath.insert(totalPath.begin(), current);
    }

    return totalPath;

}

int calc8fScore(string state) {
    int fScore = 0;
    string finalState = "123456780";

    for (int index = 1; index < 9; index++) {
        int req_loc = index - 1;
        int loc = state.find(finalState[index - 1]);

        fScore += abs(req_loc % 3 - loc % 3) + abs(static_cast<int>(req_loc/3) - static_cast<int>(loc/3));

        for (int smallIndex = (index - 1 - ((index - 1) % 3)); smallIndex < (index - 1 - ((index - 1) % 3)) + 3; smallIndex++) {
            if (smallIndex == index) continue;

            if ((smallIndex < index) & (state[smallIndex] != '0') & (state[smallIndex] > state[index - 1]) & (state[smallIndex] < (index - 1 - ((index - 1) % 3)) + 3)) fScore += 2;
            if ((smallIndex > index) & (state[smallIndex] != '0') & (state[smallIndex] < state[index - 1]) & (state[smallIndex] > (index - 1 - ((index - 1) % 3)))) fScore += 2;
        }
    }
    
    return fScore;
}

vector<string> find8Neighbors(string state) {

    vector<string> neighbors;
    int index = state.find('0');

    if (index % 3 < 2) {
        string temp_state = state;
        temp_state[index] = state[index + 1];
        temp_state[index + 1] = '0';
        neighbors.push_back(temp_state);
    }

    if (index % 3 > 0) {
        string temp_state = state;
        temp_state[index] = state[index - 1];
        temp_state[index - 1] = '0';
        neighbors.push_back(temp_state);
    }

    if (index > 2) {
        string temp_state = state;
        temp_state[index] = state[index - 3];
        temp_state[index - 3] = '0';
        neighbors.push_back(temp_state);
    }

    if (index < 6) {
        string temp_state = state;
        temp_state[index] = state[index + 3];
        temp_state[index + 3] = '0';
        neighbors.push_back(temp_state);
    }

    return neighbors;

}

int to_decimal(char hexadecimal) {
    int num;
    stringstream ss;
    ss << std::hex << hexadecimal;
    ss >> num;

    return num;

}
