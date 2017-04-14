/*
Filename: algorithm.cpp
Author: Dhruv Somani and Khush Jain
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

using namespace std;

vector<string> solve8Puzzle(string state);
vector<string> solve15Puzzle(string state);
vector<string> reconstructPath(map<string, string> cameFrom, string current);
vector<string> find8Neighbors(string state);
vector<string> find15Neighbors(string state);
float calc8fScore(string state);
float calc15fScore(string state);
string to_string(int i);

int main() {

    string state;
    getline(cin, state);
    cout << endl;

    vector<string> solution = solve15Puzzle(state);
    cout << "Solution:" << endl;
    for (int index = 0; index < solution.size(); index++) cout << solution[index].substr(0, 4) << endl
                << solution[index].substr(4, 4) << endl
                << solution[index].substr(8, 4) << endl
                << solution[index].substr(12, 4) << endl << endl;

    cout << "Length: " << solution.size() - 1;


    return 0;
}


vector<string> solve8Puzzle(string state)
{

    assert (state.length() == 9);

    vector<string> frontier;
    vector<string> visited;
    map<string, string> cameFrom;

    frontier.push_back(state);

    map<string, float> fScore;
    map<string, int> gScore;
    gScore[state] = 0;

    while (frontier.size() > 0)
    {

        int best_choice = 0;
        float minimum = 120;

        for (int index = 0; index < frontier.size(); index++)
        {
            if (fScore[frontier[index]] < minimum)
            {
                best_choice = index;
                minimum = fScore[frontier[index]];
            }

        }

        string curr_state = frontier[best_choice];
        frontier.erase(frontier.begin() + best_choice);
        visited.push_back(curr_state);

        // DEBUGGING

        /*
        cout << endl << curr_state << endl;// << "Visited: ";
        for (int index = 0; index < visited.size(); index++) cout << visited[index];
        cout << endl << "Frontier: ";
        for (int index = 0; index < frontier.size(); index++) cout << frontier[index] << " ";
        cout << endl;
        */

        if (curr_state == "123456780")
        {
            vector<string> path = reconstructPath(cameFrom, curr_state);

            cout << "No. of fScore's Taken: " << fScore.size() << endl;

            return path;
        }

        vector<string> neighbors = find8Neighbors(curr_state);

        for (unsigned int index = 0; index < neighbors.size(); index++)
        {

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

vector<string> solve15Puzzle(string state)
{
    assert (state.length() == 16);

    for (int i = 0; i < state.length(); i++) state[i] = toupper(static_cast<int>(state[i])); // Capitalizing the string

    vector<string> frontier;
    vector<string> visited;
    map<string, string> cameFrom;

    frontier.push_back(state);

    map<string, float> fScore;
    map<string, int> gScore;
    gScore[state] = 0;

    while (frontier.size() > 0)
    {

        int best_choice = 0;
        float minimum = 400;

        for (int index = 0; index < frontier.size(); index++)
        {
            if (fScore[frontier[index]] < minimum)
            {
                best_choice = index;
                minimum = fScore[frontier[index]];
            }

        }

        string curr_state = frontier[best_choice];
        frontier.erase(frontier.begin() + best_choice);
        visited.push_back(curr_state);

        // DEBUGGING

        /*
        cout << endl << curr_state << endl;// << "Visited: ";
        for (int index = 0; index < visited.size(); index++) cout << visited[index];
        cout << endl << "Frontier: ";
        for (int index = 0; index < frontier.size(); index++) cout << frontier[index] << " ";
        cout << endl;
        */

        if (curr_state == "123456789ABCDEF0")
        {
            vector<string> path = reconstructPath(cameFrom, curr_state);

            cout << "No. of fScore's Taken: " << fScore.size() << endl;

            return path;
        }

        vector<string> neighbors = find15Neighbors(curr_state);

        for (unsigned int index = 0; index < neighbors.size(); index++)
        {

            string neighbor = neighbors[index];
            if (find(visited.begin(), visited.end(), neighbor) != visited.end()) continue;

            if (find(frontier.begin(), frontier.end(), neighbor) == frontier.end()) frontier.push_back(neighbor);
            else if ((gScore[curr_state] + 1) >= gScore[neighbor]) continue;

            // This path is the best until now. Record it!
            cameFrom[neighbor] = curr_state;
            gScore[neighbor] = gScore[curr_state] + 1;
            fScore[neighbor] = calc15fScore(neighbor) + gScore[neighbor];

        }

        // mapping >>>>>>>>>>>>>>>>>>>>>>>>>>>
        //for (std::map<string,float>::iterator it=fScore.begin(); it!=fScore.end(); ++it) {
        //    std::cout << it->first << " => " << it->second << '\n';}
        //cout << endl;
    }

    return vector<string>();

}

vector<string> reconstructPath(map<string, string> cameFrom, string current)
{

    vector<string> totalPath;
    totalPath.push_back(current);

    while (cameFrom.find(current) != cameFrom.end())
    {

        current = cameFrom[current];
        totalPath.insert(totalPath.begin(), current);
    }

    return totalPath;

}


float calc8fScore(string state)
{

    float fScore = 0;
    string finalState = "123456780";

    for (int index = 1; index < 9; index++)
    {
        int req_loc = finalState.find(to_string(index));
        int loc = state.find(to_string(index));

        fScore += abs(req_loc % 3 - loc % 3) + abs(static_cast<int>(req_loc/3) - static_cast<int>(loc/3));

        for (int smallIndex = (index - 1 - ((index - 1) % 3)); smallIndex < (index - 1 - ((index - 1) % 3)) + 3; smallIndex++)
        {

            if (smallIndex == index) continue;

            if ((smallIndex < index) & (state[smallIndex] > state[index]) & (state[smallIndex] < (index - 1 - ((index - 1) % 3)) + 3)) fScore += 2;
            if ((smallIndex > index) & (state[smallIndex] < state[index]) & (state[smallIndex] > (index - 1 - ((index - 1) % 3)))) fScore += 2;

        }

    }

    return fScore;

}

float calc15fScore(string state)
{

    float fScore = 0;
    string finalState = "123456789ABCDEF0";

    for (int index = 1; index < 16; index++)
    {
        int req_loc = finalState.find(finalState[index - 1]);
        int loc = state.find(finalState[index - 1]);

        fScore += abs(req_loc % 4 - loc % 4) + abs(static_cast<int>(req_loc/4) - static_cast<int>(loc/4));

        /*
        for (int smallIndex = (index - 1 - ((index - 1) % 4)); smallIndex < (index - 1 - ((index - 1) % 4)) + 4; smallIndex++)
        {

            if (smallIndex == index) continue;

            if ((smallIndex < index) & (state[smallIndex] > state[index]) & (state[smallIndex] < (index - 1 - ((index - 1) % 4)) + 4)) fScore += 2;
            if ((smallIndex > index) & (state[smallIndex] < state[index]) & (state[smallIndex] > (index - 1 - ((index - 1) % 4)))) fScore += 2;

        }
        */

    }

    return fScore;

}

vector<string> find8Neighbors(string state)
{

    vector<string> neighbors;
    int index = state.find('0');

    if (index % 3 < 2)
    {
        string temp_state = state;
        temp_state[index] = state[index + 1];
        temp_state[index + 1] = '0';
        neighbors.push_back(temp_state);
    }

    if (index % 3 > 0)
    {
        string temp_state = state;
        temp_state[index] = state[index - 1];
        temp_state[index - 1] = '0';
        neighbors.push_back(temp_state);
    }

    if (index > 2)
    {
        string temp_state = state;
        temp_state[index] = state[index - 3];
        temp_state[index - 3] = '0';
        neighbors.push_back(temp_state);
    }

    if (index < 6)
    {
        string temp_state = state;
        temp_state[index] = state[index + 3];
        temp_state[index + 3] = '0';
        neighbors.push_back(temp_state);
    }

    return neighbors;

}

vector<string> find15Neighbors(string state)
{

    vector<string> neighbors;
    int index = state.find('0');

    if (index % 4 < 3)
    {
        string temp_state = state;
        temp_state[index] = state[index + 1];
        temp_state[index + 1] = '0';
        neighbors.push_back(temp_state);
    }

    if (index % 4 > 0)
    {
        string temp_state = state;
        temp_state[index] = state[index - 1];
        temp_state[index - 1] = '0';
        neighbors.push_back(temp_state);
    }

    if (index > 3)
    {
        string temp_state = state;
        temp_state[index] = state[index - 4];
        temp_state[index - 4] = '0';
        neighbors.push_back(temp_state);
    }

    if (index < 12)
    {
        string temp_state = state;
        temp_state[index] = state[index + 4];
        temp_state[index + 4] = '0';
        neighbors.push_back(temp_state);
    }

    return neighbors;

}

string to_string(int i)
{
    stringstream ss;
    ss << i;
    return ss.str();
}
