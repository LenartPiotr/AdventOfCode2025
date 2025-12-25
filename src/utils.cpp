#include "../include/utils.h"

vector<string> readAllLines(const string& fname) {
    vector<string> lines;
    ifstream file(fname);

    if (!file.is_open()) {
        cerr << "Błąd: Nie można otworzyć pliku " << fname << endl;
        return lines; 
    }

    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }

    file.close();
    return lines;
}


vector<string> split(const string& text, char separator) {
    vector<string> parts;
    string single;
    stringstream ss(text);

    while (getline(ss, single, separator)) {
        parts.push_back(single);
    }

    return parts;
}