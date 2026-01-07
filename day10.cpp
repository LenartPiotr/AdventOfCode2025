#include "include/utils.h"

#include <algorithm>

struct MachineIn {
    vector<bool> indicatorLightDiagram;
    vector<vector<int>> schematics;
    vector<int> joltageRequirements;
};

ostream& operator<< (ostream &os, const MachineIn& m) {
    os << "[";
    for (const auto& c : m.indicatorLightDiagram) os << (c ? "#" : ".");
    os << "]";
    for (const auto& schem : m.schematics) {
        os << " (";
        for (const auto& num : schem) os << num << ",";
        os << ")";
    }
    os << " {";
    for (const auto& num : m.joltageRequirements) os << num << ",";
    os << "}";
    return os;
}

MachineIn parseLine(string line) {
    MachineIn config;
    vector<string> parts = split(line, ' ');
    for (auto& p : parts) p = p.substr(1, p.size() - 2);

    for (auto& c : parts[0]) config.indicatorLightDiagram.push_back(c == '#');

    for (size_t i = 1; i < parts.size() - 1; i++) {
        vector<int> schem;
        for (auto& str_num : split(parts[i], ',')) schem.push_back(stoi(str_num));
        config.schematics.push_back(schem);
    }

    for (auto& str_num : split(*parts.rbegin(), ',')) config.joltageRequirements.push_back(stoi(str_num));

    return config;
}

// part 1

struct MachineBitmask {
    int state;
    vector<int> schematics;
};

MachineBitmask convertToBitmask(const MachineIn& input) {
    MachineBitmask output;
    output.state = 0;

    for (size_t i = 0; i < input.indicatorLightDiagram.size(); ++i) {
        if (input.indicatorLightDiagram[i]) {
            output.state |= (1 << i);
        }
    }
    
    output.schematics.reserve(input.schematics.size());
    
    for (const auto& internalVec : input.schematics) {
        int bitmask = 0;
        for (int bitIndex : internalVec) {
            bitmask |= (1 << bitIndex);
        }
        output.schematics.push_back(bitmask);
    }

    return output;
}

int countSetBits(int n) {
    int count = 0;
    while (n > 0) {
        count += (n & 1);
        n >>= 1;
    }
    return count;
}

int countSetTrueInVector(const vector<bool>& v) {
    int count = 0;
    for (size_t i = 0; i < v.size(); i++) {
        if (v[i]) count++;
    }
    return count;
}

struct Data {
    int state;
    vector<bool> usedSchematics;
};

int solvePart1(const MachineIn& in) {
    queue<Data> q ({{
        0,
        vector<bool>(in.schematics.size(), false),
    }});

    MachineBitmask inBit = convertToBitmask(in);

    while (!q.empty()) {
        Data data = q.front();
        q.pop();
        for (size_t i = 0; i < in.schematics.size(); i++) {
            if (data.usedSchematics[i]) continue;
            Data d2 = data;
            d2.state ^= inBit.schematics[i];
            d2.usedSchematics[i] = true;
            if (d2.state == inBit.state) return countSetTrueInVector(d2.usedSchematics);
            q.push(d2);
        }
    }
    return -1000;
}

int main() {
    vector<string> lines = readAllLines("data/day10.txt");
    vector<MachineIn> machines;
    for (const auto& l : lines) machines.push_back(parseLine(l));
    
    // part 1

    bint sum = 0;
    for (const auto& m : machines) sum += solvePart1(m);
    cout << sum;

    return 0;
}