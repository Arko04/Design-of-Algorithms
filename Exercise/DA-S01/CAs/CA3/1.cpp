#include <cmath>
#include <iostream>
#include <vector>

int main() {
    int a, b;
    std::cin >> a >> b;

    int maxN = (std::sqrt(8LL * (a + b) + 1) - 1) / 2;

    std::vector<bool> vecA(maxN, false);
    std::vector<bool> vecB(maxN, false);

    int nA = 0;
    int nB = 0;

    while (maxN) {
        if (a >= b) {
            if (a - maxN < 0) {
                --maxN;
                continue;
            }
            vecA[maxN - 1] = true;
            a -= maxN;
            ++nA;
            --maxN;
        }
        else {
            if (b - maxN < 0) {
                --maxN;
                continue;
            }
            vecB[maxN - 1] = true;
            b -= maxN;
            ++nB;
            --maxN;
        }
    }

    std::cout << nA << '\n';
    for (int i = vecA.size() - 1; i >= 0; --i) {
        if (vecA[i]) std::cout << i + 1 << ' ';
    }
    std::cout << '\n'
              << nB << '\n';
    for (int i = vecB.size() - 1; i >= 0; --i) {
        if (vecB[i]) std::cout << i + 1 << ' ';
    }

    return 0;
}
