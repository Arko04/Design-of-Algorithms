#include <iostream>
#include <vector>
#include <cmath>

template <class T>
class Ones {
public:
    Ones(int digits) {
        for (int i = 0; i < digits; ++i) increase();
    }

    void increase() {
        num_ *= 10;
        ++num_;
        ++digits_;
    }
    void decrease() {
        num_ /= 10;
        --digits_;
    }

    Ones& operator++() {
        increase();
        return *this;
    }
    Ones operator++(int) {
        Ones temp(*this);
        ++(*this);
        return temp;
    }

    Ones& operator--() {
        decrease();
        return *this;
    }
    Ones operator--(int) {
        Ones temp(*this);
        --(*this);
        return temp;
    }

    T get() const { return num_; }
    int digits() const { return digits_; }

private:
    T num_ = 0;
    int digits_ = 0;
};

long long solve(long long num, Ones<long long> ones) {
    const long long all1number = ones.get();
    const long long all1digits = ones.digits();

    // how many 1s are used to reach num
    int usageCount = (num / all1number) * all1digits;

    // num after removing all1numbers from it
    num %= all1number;

    // remove one 1 for the next recursion
    ones.decrease();

    // num being 0 means that we have created it and there's no need to continue
    if (num == 0) return usageCount;

    // to reach num, we can choose to go from below or above
    // e.g. for 59, we can either go from below (5 * 11) or above (111 - 5 * 11)
    return std::min(solve(num, ones), solve(all1number - num, ones) + all1digits)
           + usageCount;
}

int main() {
    long long n;
    std::cin >> n;

    int digits = std::floor(std::log10(n)) + 1;
    Ones<long long> ones(digits + 1);

    std::cout << solve(n, ones);
    return 0;
}
