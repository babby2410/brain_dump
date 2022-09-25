//
// Created by Anil Bhargav Paindla on 10/09/22.
//


//Hi Anil.

//Snake and ladder.
/*
2d matrix
Snakes
Ladders

0 to 100.
*/

// 2 maps -> unordered_map<int, int> snakeEnds & ladderEnds.

bool canWin(int idx, unordered_set<int> &snakeStarts, unordered_set<int> &ladderStarts) {
    if (cyclicStarts.find(idx) != cyclicStarts.end())
        return false;

    if (idx > 100)
        return false;

    if (idx == 100) {
        return true;
    }

    if (snakeStarts.find(idx) != snakeStarts.end()) {
        return canWin(snakeEnds[idx], snakeStarts, ladderStarts);
    }

    if (ladderStarts.find(idx) != ladderStarts.end()) {
        return canWin(ladderEnds[idx], snakeStarts, ladderStarts);
    }

    for (int i = 1; i <= 6; i++) {
        if (canWin(idx + i, snakeStarts, ladderStarts))
            return true;
    }

    return false;
}

long long minStepsToWin(int idx, unordered_set<int> &snakeStarts, unordered_set<int> &ladderStarts, vector<int> &cache) {
    if (cyclicStarts.find(idx) != cyclicStarts.end())
        return INT_MAX;

    if (idx > 100)
        return INT_MAX;

    if (idx == 100) {
        return 1;
    }

    if (snakeStarts.find(idx) != snakeStarts.end()) {
        return minStepsToWin(snakeEnds[idx], snakeStarts, ladderStarts);
    }

    if (ladderStarts.find(idx) != ladderStarts.end()) {
        return minStepsToWin(ladderEnds[idx], snakeStarts, ladderStarts);
    }

    if (cache[idx] != -1)
        return cache[idx];

    long long minSteps = INT_MAX, curSteps;
    for (int i = 1; i <= 6; i++) {
        curSteps = 1 + minStepsToWin(idx + i, snakeStarts, ladderStarts);
        minSteps = min(curSteps, minSteps);
    }

    return cache[idx] = minSteps;
}


vector<pair<int, int>> snakes;
vector<pair<int, int>> ladders;

unordered_map<int, set<int>> G;

void buildGraph(vector<pair<int, int>> &snakes, vector<pair<int, int>> &ladders) {
    for (auto &snake: snakes) {
        int snakeStart = snake[0];
        int snakeEnd = snake[1];
        if(G.find(snakeStart) == G.end())
            G[snakeStart] = vector<int>{};
        G[snakeStart].insert(snakeEnd);

        for (int i = 1; i <= 6; i++) {
            int check = snakeEnd + i;
            if (snakeStarts.find(check) != snakeStarts.end()) {
                G[snakeEnd].insert(check);
            }

            if (ladderStarts.find(check) != ladderStarts.end()) {
                G[snakeEnd].insert(check);
            }
        }
    }

    // Same logic above for all ladders.
}

unordered_set<int> cyclicStarts;

void fillCyclicStarts(unordered_map<int, set<int>> &G) {
    for (auto &entry: G) {
        if (isCyclic(entry.first, G))
            cyclicStarts.insert(entry.first);
    }
}

bool isCyclic(int idx, unordered_map<int, set<int>> &G) {
    vector<int> visited(100, 0);
    vector<int> recStack(100, 0);

    return isCyclicUtil(idx, G, visited, recStack);
}

bool isCyclicUtil(int idx, unordered_map<int, set<int>> &G, vector<int> &visited, vector<int> &recStack) {
    visited[idx] = 1;
    recStack[idx] = 1;

    for (auto &neighbor: G[idx]) {
        if (!visited[neighbor] && isCyclicUtil(neighbor, G, visited, recStack))
            return true;
        if (recStack[neighbor])
            return true;
    }

    recStack[idx] = 0;
    return false;
}

// Dry runs
10
Snakes : 6 to 1, 8 to 5
Ladders : 2 to 4 and 1 to 6

0 -> 1 -> 2 -> 4 -> 5 -> 6
-> 7 -> 8
-> 8
-> 9 -> 10
-> 10
