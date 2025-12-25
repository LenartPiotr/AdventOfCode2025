#include "include/utils.h"

int main() {
    vector<string> lines = readAllLines("data/day4.txt");

    Table<bool> t(lines.size(), lines[0].length());

    for (int y = 0; y < t.height(); y++) {
        for (int x = 0; x < t.width(); x++) {
            t[y][x] = lines[y][x] == '@';
        }
    }

    // part 1

    int sum = 0;

    for (int y = 0; y < t.height(); y++) {
        for (int x = 0; x < t.width(); x++) {
            int neigh = 0;
            if (!t[y][x]) continue;
            for (int dx = -1; dx <= 1; dx++)
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue;
                if (t.get(y + dy, x + dx, false)) {
                    neigh++;
                }
            }
            if (neigh < 4) sum++;
        }
    }

    cout << sum << endl;

    // part 2

    sum = 0;
    bool removed = true;
    while (removed) {
        removed = false;
        for (int y = 0; y < t.height(); y++) {
            for (int x = 0; x < t.width(); x++) {
                int neigh = 0;
                if (!t[y][x]) continue;
                for (int dx = -1; dx <= 1; dx++)
                for (int dy = -1; dy <= 1; dy++) {
                    if (dx == 0 && dy == 0) continue;
                    if (t.get(y + dy, x + dx, false)) {
                        neigh++;
                    }
                }
                if (neigh < 4) {
                    sum++;
                    removed = true;
                    t[y][x] = false;
                }
            }
        }
    }

    cout << sum << endl;

    return 0;
}