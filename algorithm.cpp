#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <vector>
#include <map>

using namespace std;

vector<string> solvePuzzle(string state);
vector<string> reconstructPath(map<string, string> cameFrom, string current);
vector<string> findNeighbors(string state);
bool isSolved(string state, string finalState);

int main() {

    // For Testing Purposes, otherwise we don't need this function
    string state;
    getline(cin, state);

    vector<string> neighbors = findNeighbors(state);
    for (int index = 0; index < neighbors.size(); index++) cout << neighbors[index] << endl;

    vector<string> solution = solvePuzzle(state);
    for (int index = 0; index < solution.size(); index++) cout << solution[index] << endl;

    return 0;
}


vector<string> solvePuzzle(string state) {

    vector<string> frontier;
    vector<string> visited;
    map<string, string> cameFrom;

    frontier.push_back(state);

    map<string, float> fScore;
    map<string, int> gScore;
    gScore[state] = 0;

    while (frontier.size() > 0) {

        string curr_state = frontier.front();
        frontier.erase(frontier.begin() + 1);

        cout << curr_state << endl;
        for (int index = 0; index < visited.size(); index++) cout << visited[index];
        cout << endl;

        string final = "12345678 ";

        if (curr_state == final) {
            vector<string> path = reconstructPath(cameFrom, curr_state);
            return path;
        }

        visited.push_back(curr_state);
        vector<string> neighbors = findNeighbors(state);

        for (unsigned int index = 0; index < neighbors.size(); index++) {
            string neighbor = neighbors[index];
            if (find(visited.begin(), visited.end(), neighbor) != visited.end()) continue;
            if(gScore[neighbor] > gScore[curr_state] + 1) continue;

            if (find(frontier.begin(), frontier.end(), neighbor) == frontier.end()) {
                cout << "Yeah it did";
                frontier.push_back(neighbor);

                // This path is the best until now. Record it!
                cameFrom[neighbor] = curr_state;
                gScore[neighbor] = gScore[curr_state] + 1;

            }

        }

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


vector<string> findNeighbors(string state) {

    vector<string> neighbors;
    int index = state.find(' ');

    if (index % 3 < 2) {
        string temp_state = state;
        temp_state[index] = state[index + 1];
        temp_state[index + 1] = ' ';
        neighbors.push_back(temp_state);
    }

    if (index % 3 > 0) {
        string temp_state = state;
        temp_state[index] = state[index - 1];
        temp_state[index - 1] = ' ';
        neighbors.push_back(temp_state);
    }

    if (index > 3) {
        string temp_state = state;
        temp_state[index] = state[index - 3];
        temp_state[index - 3] = ' ';
        neighbors.push_back(temp_state);
    }

    if (index < 7) {
        string temp_state = state;
        temp_state[index] = state[index + 3];
        temp_state[index + 3] = ' ';
        neighbors.push_back(temp_state);
    }

    return neighbors;

}

bool isSolved(string state, string finalState) {

    if (state == finalState) return true;
    else return false;

}
