#include <algorithm>
#include <iostream>
#include <vector>

struct Student {
    int s;
    int r;
};

int solve(const std::vector<Student>& inp, int m) {
    std::vector<std::vector<int>> sep(m);
    for (auto stu : inp) {
        sep[stu.s].push_back(stu.r);
    }

    int max = 0;
    for (const auto& x : sep) {
        if (x.size() > max) max = x.size();
    }

    std::for_each(sep.begin(), sep.end(), [](std::vector<int>& line) {
        std::sort(line.begin(), line.end(), std::greater {});
        for (int i = 1; i < line.size(); ++i) {
            line[i] += line[i - 1];
        }
    });

    std::vector<int> col(max);
    for (int i = 0; i < col.size(); ++i) {
        for (int j = 0; j < sep.size(); ++j) {
            if (sep[j].size() > i && sep[j][i] > 0) {
                col[i] += sep[j][i];
            }
        }
    }

    return *std::max_element(col.begin(), col.end());
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<Student> inp(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> inp[i].s >> inp[i].r;
        --inp[i].s;
    }

    std::cout << solve(inp, m);

    return 0;
}
