#include "include/utils.h"

struct range {
    bint min_v;
    bint max_v;
    string min_s;
    string max_s;
};

struct range_d {
    bint min_v;
    bint max_v;
    string min_s;
    string max_s;
    int digits;
};

range parse_range(string text) {
    vector<string> parts = split(text, '-');
    range r;
    r.min_s = parts[0];
    r.max_s = parts[1];
    r.min_v = stoll(parts[0]);
    r.max_v = stoll(parts[1]);
    return r;
}

inline bool in_range(bint num, range r) {
    return r.min_v <= num && num <= r.max_v;
}

inline bool in_range(bint num, range_d r) {
    return r.min_v <= num && num <= r.max_v;
}

bint multiply_values(bint value, int digits, int times) {
    int multiplier = 1;
    for (int i = 0; i < digits; i++) multiplier *= 10;
    bint result = 0;
    for (int i = 0; i < times; i++) {
        result *= multiplier;
        result += value;
    }
    return result;
}

int digits_count(bint value) {
    int digits = 0;
    while (value > 0) {
        value /= 10;
        digits++;
    }
    return digits;
}

int powi(int base, int power) {
    int result = 1;
    while (power-- > 0) {
        result *= base;
    }
    return result;
}

bint powl(bint base, int power) {
    bint result = 1;
    while (power-- > 0) {
        result *= base;
    }
    return result;
}

vector<range_d> ranges_same_digits(range r) {
    int min_digits = digits_count(r.min_v);
    int max_digits = digits_count(r.max_v);
    if (min_digits == max_digits) {
        range_d rr;
        rr.min_s = r.min_s;
        rr.max_s = r.max_s;
        rr.min_v = r.min_v;
        rr.max_v = r.max_v;
        rr.digits = min_digits;
        return vector<range_d> { rr };
    }
    vector<range_d> result;
    for (int d = min_digits; d <= max_digits; d++) {
        stringstream ss1, ss2;
        bint min_value = d == min_digits ? r.min_v : multiply_values(9, 1, d - 1) + 1;
        bint max_value = d == max_digits ? r.max_v : multiply_values(9, 1, d);
        range_d new_r;
        new_r.min_v = min_value;
        new_r.max_v = max_value;
        ss1 << min_value;
        ss2 << max_value;
        new_r.min_s = ss1.str();
        new_r.max_s = ss2.str();
        new_r.digits = d;
        result.push_back(new_r);
    }
    return result;
}

int main() {
    string line = readAllLines("data/day2.txt")[0];
    vector<string> s_ranges = split(line, ',');
    vector<range> ranges;
    for (auto& s : s_ranges) {
        ranges.push_back(parse_range(s));
    }

    // part 1

    bint sum = 0;
    for (auto& r : ranges) {
        string strat_s = r.min_s.substr(0, r.min_s.length() / 2);
        bint current = strat_s.length() > 9 ? stoll(strat_s) : 1;
        bint double_current;
        int digits;
        do {
            digits = digits_count(current);
            double_current = multiply_values(current, digits, 2);
            if (in_range(double_current, r)) sum += double_current;
            current++;
        } while (double_current < r.max_v);
    }

    cout << sum << endl;

    // part 2

    sum = 0;
    
    vector<range_d> ranges_d;
    for (auto& r : ranges) {
        for (auto& rr : ranges_same_digits(r)) ranges_d.push_back(rr);
    }

    for (auto& r : ranges_d) {
        set<bint> toSum;
        int min_digits = 1;
        int max_digits = r.digits / 2;
        for (int digits = min_digits; digits <= max_digits; digits++) {
            if (r.digits % digits != 0) continue;
            int times = r.digits / digits;
            bint p = stoll(r.min_s.substr(0, digits));
            bint q = stoll(r.max_s.substr(0, digits));

            int _10_d = powi(10, digits);

            bint multiplier = 0;
            for (int t = 0; t < times; t++) {
                multiplier += powl(_10_d, t);
            }

            for (int v = p; v <= q; v++) {
                bint addon = 0;
                addon = v * multiplier;
                if (!in_range(addon, r)) continue;
                toSum.insert(addon);
            }
        }

        for (auto& addon : toSum) {
            sum += addon;
        }
    }

    cout << sum << endl;

    return 0;
}