#include "include/utils.h"

int main() {
    vector<string> lines = readAllLines("data/day3.txt");

    // part 1

    bint sum = 0;
    for (auto& l : lines) {
        int len = l.length();
        char max1 = 0;
        int max1i = 0;
        for (int i = 0; i < len - 1; i++) {
            if (l[i] > max1) {
                max1 = l[i];
                max1i = i;
            }
        }
        char max2 = 0;
        for (int i = max1i + 1; i < len; i++) {
            if (l[i] > max2) max2 = l[i];
        }
        int addon = (max1 - '0') * 10 + max2 - '0';
        sum += addon;
    }
    cout << sum << endl;

    // part 2

    sum = 0;

    for (auto& l : lines) {
        bint addon = 0;
        int lastFoundIndex = -1;
        int len = l.length();
        int digits = 12;
        for (int digit = 1; digit <= digits; digit++) {
            char max1 = 0;
            int max_len = len - digits + digit;
            for (int i = lastFoundIndex + 1; i < max_len; i++) {
                if (l[i] > max1) {
                    max1 = l[i];
                    lastFoundIndex = i;
                    if (max1 == '9') break;
                }
            }
            addon *= 10;
            addon += max1 - '0';
        }
        sum += addon;
    }

    cout << sum << endl;

    return 0;
}