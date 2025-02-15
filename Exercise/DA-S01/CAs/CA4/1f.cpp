#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

constexpr int MYMAX = 10000000;

inline bool floatEq(double a, double b) {
    constexpr double epsilon = 1e-5;
    return std::abs(a - b) <= epsilon * std::abs(a);
}

struct Line {
    Line() = default;
    Line(double aa, double bb, double cc)
        : a(aa),
          b(bb),
          c(cc) {}

    // Ax + By + C = 0
    double a, b, c;
};

struct Point {
    Point() = default;
    Point(double x_, double y_)
        : x(x_),
          y(y_) {}

    double x;
    double y;

    static bool isInsidePoly(const std::vector<Point>& polygon, const std::vector<Line>& lines, Point p) {
        Line pLine {0, p.x - MYMAX, (MYMAX * p.y) - (p.x * p.y)};

        int count = 0;
        for (int i = 0; i < polygon.size() - 1; ++i) {
            if (doTheyIntersect(p, Point {MYMAX, p.y}, pLine, polygon[i], polygon[i + 1], lines[i]) == Intersect::yes) ++count;
        }
        if (doTheyIntersect(p, Point {MYMAX, p.y}, pLine, polygon.back(), polygon.front(), lines.back()) == Intersect::yes) ++count;

        return count % 2;
    }

    enum class Intersect {
        no,
        yes,
        collinear
    };
    static double pointInLine(Point p, Line l) {
        return (l.a * p.x) + (l.b * p.y) + l.c;
    }
    static Intersect doTheyIntersect(Point a1, Point b1, Line one, Point a2, Point b2, Line two) {
        double d1 = pointInLine(a2, one);
        double d2 = pointInLine(b2, one);
        if (d1 > 0 && d2 > 0) return Intersect::no;
        if (d1 < 0 && d2 < 0) return Intersect::no;
        d1 = pointInLine(a1, two);
        d2 = pointInLine(b1, two);
        if (d1 > 0 && d2 > 0) return Intersect::no;
        if (d1 < 0 && d2 < 0) return Intersect::no;
        if (floatEq((one.a * two.b) - (two.a * one.b), 0)) return Intersect::collinear;
        return Intersect::yes;
    }
};

using Polygon = std::vector<Point>;

void floydWarshall(std::vector<std::vector<int>>& dp) {
    const int n = dp.size();
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[k][j]);
            }
        }
    }
}

void solve(std::vector<std::vector<int>>& dist,
           const std::vector<Polygon>& areas,
           const std::vector<std::pair<Point, Point>>& minMax,
           const std::vector<int>& inpArea) {
    auto shortestPath = [&dist](int a1, int a2) {
        return (dist[a1][a2] == MYMAX) ? -1 : dist[a1][a2];
    };

    for (int i = 0; i < inpArea.size() - 1; ++i) {
        if (inpArea[i] == -1 || inpArea[i + 1] == -1) {
            std::cout << -1 << '\n';
            continue;
        }
        int res = shortestPath(inpArea[i], inpArea[i + 1]);
        if (res == -1) std::cout << "INF" << '\n';
        else std::cout << res << '\n';
    }
}

int whichArea(const std::vector<Polygon>& areas,
              const std::vector<std::vector<Line>>& eqs,
              const std::vector<std::pair<Point, Point>>& minMax,
              const Point p) {
    for (int i = 0; i < areas.size(); ++i) {
        if (p.x < minMax[i].first.x || p.x > minMax[i].second.x ||
            p.y < minMax[i].first.y || p.y > minMax[i].second.y) continue;
        if (Point::isInsidePoly(areas[i], eqs[i], p)) return i;
    }
    return -1;
}

std::vector<std::vector<Line>> areasEquations(const std::vector<Polygon>& areas) {
    std::vector<std::vector<Line>> result;
    result.reserve(areas.size());
    for (const auto& polygon : areas) {
        std::vector<Line> here;
        here.reserve(polygon.size());
        for (int i = 0; i < polygon.size() - 1; ++i) {
            here.emplace_back(polygon[i + 1].y - polygon[i].y,
                              polygon[i].x - polygon[i + 1].x,
                              (polygon[i + 1].x * polygon[i].y) - (polygon[i].x * polygon[i + 1].y));
        }
        here.emplace_back(polygon.front().y - polygon.back().y,
                          polygon.back().x - polygon.front().x,
                          (polygon.front().x * polygon.back().y) - (polygon.back().x * polygon.front().y));
        result.push_back(std::move(here));
    }
    return result;
}

int main() {
    int n, m; // n area m edge
    std::cin >> n >> m;

    std::vector<std::vector<int>> graph(n, std::vector<int>(n, MYMAX));
    for (int i = 0; i < n; ++i) {
        graph[i][i] = 0;
    }
    std::vector<Polygon> areas(n);
    std::vector<std::pair<Point, Point>> minMax(n);

    for (int i = 0; i < n; ++i) {
        int v;
        std::cin >> v;
        minMax[i].first = {std::numeric_limits<double>::max(), std::numeric_limits<double>::max()};
        minMax[i].second = {std::numeric_limits<double>::min(), std::numeric_limits<double>::min()};
        for (int j = 0; j < v; ++j) {
            double y, x;
            std::cin >> y >> x;
            areas[i].emplace_back(x, y);
            minMax[i].first.x = std::min(minMax[i].first.x, x);
            minMax[i].first.y = std::min(minMax[i].first.y, y);
            minMax[i].second.x = std::max(minMax[i].second.x, x);
            minMax[i].second.y = std::max(minMax[i].second.y, y);
        }
    }

    for (int i = 0; i < m; ++i) {
        int id1, id2, t;
        std::cin >> id1 >> id2 >> t;
        graph[id1][id2] = t;
    }

    floydWarshall(graph); // graph = dist
    const auto eqs = areasEquations(areas);
    int r;
    std::cin >> r;
    for (int test = 0; test < r; ++test) {
        int p;
        std::cin >> p;
        std::vector<int> inpArea;
        for (int i = 0; i < p; ++i) {
            double y, x;
            std::cin >> y >> x;
            inpArea.push_back(whichArea(areas, eqs, minMax, Point {x, y}));
        }
        solve(graph, areas, minMax, inpArea);
    }

    return 0;
}
