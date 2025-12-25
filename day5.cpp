#include "include/utils.h"

#include <algorithm>

struct range {
    bint min_v;
    bint max_v;
};

inline bool overlap(const range &r1, const range &r2) {
    return r1.max_v >= r2.min_v && r1.min_v <= r2.max_v;
}

void merge_ranges(const vector<range>::iterator &merge_target, vector<range> &all) {
    if (merge_target == all.end()) return;

    auto it = merge_target + 1;

    while (it != all.end()) {
        if (!overlap(*merge_target, *it)) break;

        merge_target->min_v = min(merge_target->min_v, it->min_v);
        merge_target->max_v = max(merge_target->max_v, it->max_v);
        it = all.erase(it);
    }
}

void insert_range_into_pool(vector<range> &all, const range &new_range) {
    if (all.size() == 0) {
        all.push_back(new_range);
        return;
    }
    for (auto it = all.begin(); it != all.end(); it++) {
        if (new_range.min_v <= it->max_v) {
            vector<range>::iterator new_it = all.insert(it, new_range);
            merge_ranges(new_it, all);
            return;
        }
    }
    all.push_back(new_range);
}

int main() {
    vector<string> lines = readAllLines("data/day5.txt");

    vector<range> ranges;
    vector<bint> ingredients;
    bool process_ingredients = false;

    for (auto& l : lines) {
        if (process_ingredients) {
            ingredients.push_back(stoll(l));
            continue;
        }
        if (l.length() == 0) {
            process_ingredients = true;
            continue;
        }

        vector<string> parts = split(l, '-');
        range r;
        r.min_v = stoll(parts[0]);
        r.max_v = stoll(parts[1]);
        insert_range_into_pool(ranges, r);
    }

    sort(ingredients.begin(), ingredients.end());

    // part 1

    bint sum = 0;

    auto range_it = ranges.begin();

    for (auto& ing : ingredients) {
        while (range_it != ranges.end() && ing > range_it->max_v) {
            range_it++;
        }

        if (range_it != ranges.end() && ing >= range_it->min_v) {
            sum++;
        }
    }

    cout << sum << endl;

    // part 2

    sum = 0;

    for (auto& r : ranges) {
        sum += r.max_v - r.min_v + 1;
    }

    cout << sum << endl;

    return 0;
}