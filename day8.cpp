#include "include/utils.h"

#include <algorithm>

struct Point {
    bint x, y, z;
};

struct Connection {
    int id1, id2;
    bint dist2;
};

inline bint dist(const Point& p1, const Point& p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) + (p1.z - p2.z) * (p1.z - p2.z);
}

void mergeGroups(vector<vector<int>>& groups, map<int, int>& pointGroup, int g1, int g2) {
    int source = max(g1, g2);
    int target = min(g1, g2);
    
    for (int point : groups[source]) {
        groups[target].push_back(point);
        pointGroup[point] = target;
    }

    groups[source].clear();
}

int main() {
    vector<string> lines = readAllLines("data/day8.txt");
    int connectLimit = 1000;

    vector<Point> points;
    for (string l : lines) {
        auto parts = split(l, ',');
        points.push_back({stoi(parts[0]), stoi(parts[1]), stoi(parts[2])});
    }

    // part 1

    vector<Connection> allConnections;
    for (size_t i = 0; i < points.size(); i++) {
        for (size_t j = i + 1; j < points.size(); j++) {
            allConnections.push_back({(int)i, (int)j, dist(points[i], points[j])});
        }
    }

    sort(allConnections.begin(), allConnections.end(), [](const Connection& a, const Connection& b) {
        return a.dist2 < b.dist2;
    });

    map<int, int> pointGroup;
    for (size_t i=0; i<points.size(); i++) {
        pointGroup[i] = -1;
    }
    vector<vector<int>> groups;

    int alreadyConnected = 0;
    size_t connId = 0;
    int firstFreeGroup = 0;
    while (connId < allConnections.size() && alreadyConnected < connectLimit) {
        alreadyConnected++;
        Connection conn = allConnections[connId++];
        int g1 = pointGroup[conn.id1];
        int g2 = pointGroup[conn.id2];
        if (g1 != -1 && g2 != -1 && g1 == g2) continue;
        if (g1 == -1 && g2 == -1) {
            int targetGroup = firstFreeGroup++;
            groups.push_back(vector<int>{conn.id1, conn.id2});
            pointGroup[conn.id1] = targetGroup;
            pointGroup[conn.id2] = targetGroup;
            continue;
        }
        if (g1 != -1 && g2 != -1) {
            mergeGroups(groups, pointGroup, g1, g2);
            continue;
        }
        if (g1 == -1) {
            groups[g2].push_back(conn.id1);
            pointGroup[conn.id1] = g2;
        } else if (g2 == -1) {
            groups[g1].push_back(conn.id2);
            pointGroup[conn.id2] = g1;
        }
    }

    vector<vector<int>> sortedGroups = groups;

    sort(sortedGroups.begin(), sortedGroups.end(), [](const vector<int>& g1, const vector<int>& g2) {
        return g1.size() > g2.size();
    });

    bint result = 1;
    for (int i = 0; i < 3; i++) result *= sortedGroups[i].size();

    cout << result << endl;

    // part 2

    size_t lastConnection;

    while (connId < allConnections.size()) {
        alreadyConnected++;
        Connection conn = allConnections[connId++];
        int g1 = pointGroup[conn.id1];
        int g2 = pointGroup[conn.id2];
        if (g1 != -1 && g2 != -1 && g1 == g2) continue;
        lastConnection = connId - 1;
        if (g1 == -1 && g2 == -1) {
            int targetGroup = firstFreeGroup++;
            groups.push_back(vector<int>{conn.id1, conn.id2});
            pointGroup[conn.id1] = targetGroup;
            pointGroup[conn.id2] = targetGroup;
            continue;
        }
        if (g1 != -1 && g2 != -1) {
            mergeGroups(groups, pointGroup, g1, g2);
            continue;
        }
        if (g1 == -1) {
            groups[g2].push_back(conn.id1);
            pointGroup[conn.id1] = g2;
        } else if (g2 == -1) {
            groups[g1].push_back(conn.id2);
            pointGroup[conn.id2] = g1;
        }
    }

    cout << points[allConnections[lastConnection].id1].x * points[allConnections[lastConnection].id2].x << endl;

    return 0;
}