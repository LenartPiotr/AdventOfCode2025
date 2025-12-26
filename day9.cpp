#include "include/utils.h"

#include <algorithm>

struct Point {
    bint x, y;
};

Point operator+ (const Point& p1, const Point& p2) {
    return Point {p1.x + p2.x, p1.y + p2.y};
}

struct Rect {
    bint x1, x2, y1, y2;
    bint area;
};

ostream& operator<< (ostream& out, Point point) {
    out << "(" << point.x << ", " << point.y << ")";
    return out;
}

ostream& operator<< (ostream& out, Rect r) {
    out << "[(" << r.x1 << ", " << r.y1 << ") x (" << r.x2 << ", " << r.y2 << ") = " << r.area << "]";
    return out;
}

inline bool belongToRect(const Point& p, const Rect& l) {
    return l.x1 <= p.x && p.x <= l.x2 && l.y1 <= p.y && p.y <= l.y2;
}

inline bint area(const Point& p1, const Point& p2) {
    return (abs(p1.x - p2.x) + 1) * (abs(p1.y - p2.y) + 1);
}

inline Rect makeRect(const Point& p1, const Point& p2) {
    return {min(p1.x, p2.x), max(p1.x, p2.x), min(p1.y, p2.y), max(p1.y, p2.y), area(p1, p2)};
}

// check line between p and (p.x-0.5, -1)
inline bool inside(const Point& p, const vector<Rect>& horizontals, const vector<Rect>& verticals) {
    bool in = false;
    for (const Rect& line : verticals) {
        if (belongToRect(p, line)) {
            return true;
        }
    }
    for (const Rect& line : horizontals) {
        if (belongToRect(p, line)) {
            return true;
        }
        if (line.x1 < p.x && line.x2 >= p.x && line.y1 < p.y) {
            in = !in;
        }
    }
    return in;
}

inline void reduce(Point& p, const Rect& r) {
    p.x = max(r.x1, min(r.x2, p.x));
    p.y = max(r.y1, min(r.y2, p.y));
}

bool lineIntersectRect(const Rect& rect, const Rect& line) {
    bool isHorizontal = line.y1 == line.y2;
    if (isHorizontal) {
        if (line.y1 > rect.y1 && line.y1 < rect.y2) {
            bint overlapX1 = max(line.x1, rect.x1 + 1);
            bint overlapX2 = min(line.x2, rect.x2 - 1);
            if (overlapX1 <= overlapX2) return true;
        }
    } else {
        if (line.x1 > rect.x1 && line.x1 < rect.x2) {
            bint overlapY1 = max(line.y1, rect.y1 + 1);
            bint overlapY2 = min(line.y2, rect.y2 - 1);
            if (overlapY1 <= overlapY2) return true;
        }
    }
    return false;
}

int main() {
    vector<string> lines = readAllLines("data/day9.txt");
    vector<Point> points;

    for (auto& l : lines) {
        auto parts = split(l, ',');
        points.push_back({stoll(parts[0]), stoll(parts[1])});
    }

    // part 1

    bint biggestArea = 0;
    for (size_t i = 0; i < points.size(); i++) {
        for (size_t j = i + 1; j < points.size(); j++) {
            const Point& p1 = points[i];
            const Point& p2 = points[j];
            bint area = abs(p1.x - p2.x + 1) * abs(p1.y - p2.y + 1);
            if (area > biggestArea) biggestArea = area;
        }
    }

    cout << biggestArea << endl;

    // part 2

    vector<Rect> allLines;
    vector<Rect> horizontals;
    vector<Rect> verticals;
    for (size_t i = 0; i < points.size(); i++) {
        size_t j = (i + 1) % points.size();
        Rect newLine = makeRect(points[i], points[j]);
        allLines.push_back(newLine);
        if (newLine.y1 == newLine.y2) horizontals.push_back(newLine);
        else verticals.push_back(newLine);
    }

    vector<Rect> allRects;
    for (size_t i = 0; i < points.size(); i++) {
        for (size_t j = i + 1; j < points.size(); j++) {
            allRects.push_back(makeRect(points[i], points[j]));
        }
    }

    sort(allRects.begin(), allRects.end(), [](const Rect& r1, const Rect& r2) { return r1.area > r2.area; });

    // vector<Point> diff {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    //
    // for (auto& rect : allRects) {
    //     bool fullyFilled = true;
    //     for (auto& p : points) {
    //         if (!belongToRect(p, rect)) continue;
    //         for (const auto& df : diff) {
    //             Point corner = p + df;
    //             reduce(corner, rect);
    //             if (inside(corner, horizontals, verticals)) continue;
    //             fullyFilled = false;
    //             break;
    //         }
    //         if (!fullyFilled) break;
    //     }
    //     if (!fullyFilled) continue;
    //     cout << rect.area << endl;
    //     break;
    // }

    for (auto& rect : allRects) {
        bool intersect = false;
        for (auto& line : allLines) {
            if (lineIntersectRect(rect, line)) {
                intersect = true;
                break;
            }
        }
        if (intersect) continue;
        cout << rect.area << endl;
        break;
    }

    // 4618378450 too high

    return 0;
}