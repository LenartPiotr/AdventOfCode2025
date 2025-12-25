#include "include/utils.h"

int main() {
    vector<string> lines = readAllLines("data/day7.txt");
    
    int size = lines[0].length();

    // part 1

    set<int> tachyonBeamsIndices;
    for (int i=0; i<size; i++) {
        if (lines[0][i] == 'S') tachyonBeamsIndices.insert(i);
    }

    int splitCount = 0;

    set<int> newState;
    for (auto it = lines.begin() + 1; it != lines.end(); it++) {
        const string line = *it;
        newState.clear();
        for (int i : tachyonBeamsIndices) {
            if (line[i] == '.') {
                newState.insert(i);
            } else {
                splitCount++;
                newState.insert(i + 1);
                newState.insert(i - 1);
            }
        }
        swap(newState, tachyonBeamsIndices);
    }

    cout << splitCount << endl;

    // part 2

    map<int, bint> idx;
    map<int, bint> nextState2;

    for (int i=0; i<size; i++) {
        if (lines[0][i] == 'S') idx[i] = 1;
    }

    for (auto it = lines.begin() + 1; it != lines.end(); it++) {
        const string line = *it;
        nextState2.clear();
        for (auto const& [key, value] : idx) {
            if (line[key] == '.') {
                auto newEntry = nextState2.find(key);
                if (newEntry != nextState2.end()) {
                    newEntry->second += value;
                } else {
                    nextState2[key] = value;
                }
            } else {
                auto newEntry = nextState2.find(key + 1);
                if (newEntry != nextState2.end()) {
                    newEntry->second += value;
                } else {
                    nextState2[key + 1] = value;
                }

                newEntry = nextState2.find(key - 1);
                if (newEntry != nextState2.end()) {
                    newEntry->second += value;
                } else {
                    nextState2[key - 1] = value;
                }
            }
        }
        swap(nextState2, idx);
    }

    bint sum = 0;

    for (auto const& [_, value] : idx) {
        sum += value;
    }

    cout << sum << endl;

    return 0;
}