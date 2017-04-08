#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

vector<string> solvePuzzle(string state);
vector<string> reconstructPath(map<string, string> cameFrom, string current);
vector<string> findNeighbors(string state);
float calcfScore(string state);
bool isSolved(string state, string finalState);

int main() {

    // For Testing Purposes, otherwise we don't need this function
    string state;
    getline(cin, state);

    vector<string> solution = solvePuzzle(state);
    cout << "Solution:" << endl;
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

        int best_choice = 0;
        float minimum = 100;

        for (int index = 0; index < frontier.size(); index++) {
            if (fScore[frontier[index]] > minimum) best_choice = index;
        }

        string curr_state = frontier[best_choice];
        frontier.erase(frontier.begin() + best_choice);
        visited.push_back(curr_state);

        // DEBUGGING
        /*
        cout << endl << curr_state << endl;// << "Visited: ";
        //for (int index = 0; index < visited.size(); index++) cout << visited[index];
        cout << endl << "Frontier: ";
        for (int index = 0; index < frontier.size(); index++) cout << frontier[index];
        cout << endl;
        */

        if (curr_state == "12345678 ") {
            vector<string> path = reconstructPath(cameFrom, curr_state);
            return path;
        }


        vector<string> neighbors = findNeighbors(curr_state);

        for (unsigned int index = 0; index < neighbors.size(); index++) {

            string neighbor = neighbors[index];
            //cout << neighbor;
            if (find(visited.begin(), visited.end(), neighbor) != visited.end()) {
                    //cout << " terminated in visited." << endl;
                    continue;
            }

            if (find(frontier.begin(), frontier.end(), neighbor) == frontier.end()) {
                //cout << " " << "State not yet Visited. State inserted in Frontier." << endl;
                frontier.push_back(neighbor);

            } else if ((gScore[curr_state] + 1) >= gScore[neighbor]) {
                    //cout << " terminated due to idiotic reasons." << endl;
                    continue;
            }

            // This path is the best until now. Record it!
            cameFrom[neighbor] = curr_state;
            fScore[neighbor] = calcfScore(neighbor);
            gScore[neighbor] = gScore[curr_state] + 1;

        }


        // mapping >>>>>>>>>>>>>>>>>>>>>>>>>>>
        //for (std::map<string,float>::iterator it=fScore.begin(); it!=fScore.end(); ++it) {
        //    std::cout << it->first << " => " << it->second << '\n';}

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


float calcfScore(string state) {

    float fScore = 0;
    string final = "12345678 ";

    for (int index = 1; index < 9; index++) {
        
        int loc = state.find(final[(index-1)%9]);

        fScore += abs((index)%3 - loc%3) + abs(static_cast<int>((index - 1 - 2)/3) - static_cast<int>((loc - 1)/3));

    }

    return fScore;

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

    if (index > 2) {
        string temp_state = state;
        temp_state[index] = state[index - 3];
        temp_state[index - 3] = ' ';
        neighbors.push_back(temp_state);
    }

    if (index < 6) {
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
