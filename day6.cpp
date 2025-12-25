#include "include/utils.h"

int main() {
    vector<string> lines = readAllLines("data/day6.txt");
    vector<vector<bint>> numbers;
    vector<char> operators;
    for (size_t i=0; i<lines.size() - 1; i++) {
        vector<string> parts = split(lines[i], ' ');
        vector<bint> nums;
        for (string& part : parts) {
            if (part.length() == 0) continue;
            nums.push_back(stoll(part));
        }
        numbers.push_back(nums);
    }
    for (char c : lines[lines.size() - 1]) {
        if (c != ' ') operators.push_back(c);
    }

    int size = operators.size();

    // part 1

    bint sum = 0;
    for (int i = 0; i < size; i++) {
        if (operators[i] == '+') {
            bint part = 0;
            for (auto& row : numbers) part += row[i];
            sum += part;
        } else if (operators[i] == '*') {
            bint part = 1;
            for (auto& row : numbers) part *= row[i];
            sum += part;
        }
    }

    cout << sum << endl;

    // part 2

    sum = 0;

    vector<stringstream> ss_transp;
    ss_transp.resize(lines[0].size());
    for (auto& row : lines) {
        auto it = ss_transp.rbegin();
        for (auto& c: row) {
            (*it) << c;
            it++;
        }
    }

    stringstream ss_empty_row;
    for (size_t i=0; i<lines.size(); i++) {
        ss_empty_row << " ";
    }
    string empty_row = ss_empty_row.str();

    vector<bint> parts;
    char lastSign = '+';
    for (auto& ss : ss_transp) {
        string row = ss.str();
        if (row != empty_row) {
            parts.push_back(stoll(row));
            lastSign = *row.rbegin();
        } else {
            bint result = 0;
            if (lastSign == '+') {
                result = 0;
                for (auto& part : parts) result += part;
            } else if (lastSign == '*') {
                result = 1;
                for (auto& part : parts) result *= part;
            } else {
                cerr << "Emm... What it is a sign? " << lastSign << endl;
            }
            sum += result;
            parts.clear();
        }
    }

    bint result = 0;
    if (lastSign == '+') {
        result = 0;
        for (auto& part : parts) result += part;
    } else if (lastSign == '*') {
        result = 1;
        for (auto& part : parts) result *= part;
    } else {
        cerr << "Emm... What it is a sign? " << lastSign << endl;
    }
    sum += result;

    cout << sum << endl;

    return 0;
}