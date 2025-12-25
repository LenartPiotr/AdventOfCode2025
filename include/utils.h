#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <map>

#define bint long long int

using namespace std;

vector<string> readAllLines(const string&);
vector<string> split(const string& text, char separator);

template <typename T>
class Table {
    T** arr;
    int w;
    int h;
public:
    Table(int width, int height) : w(width), h(height) {
        arr = new T*[height];
        for (int i = 0; i < h; i++) arr[i] = new T[width];
    }
    ~Table() {
        for (int i = 0; i < h; i++) delete[] arr[i];
        delete[] arr;
    }
    inline T* operator[] (int index) {
        return arr[index];
    }
    inline bool in_range(int iy, int ix) {
        return 0 <= ix && ix < w && 0 <= iy && iy < h;
    }
    inline T get(int iy, int ix, int def) {
        if (in_range(iy, ix)) return arr[iy][ix];
        return def;
    }
    inline const int& width() { return w; }
    inline const int& height() { return h; }
};