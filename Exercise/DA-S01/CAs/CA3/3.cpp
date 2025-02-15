#include <iostream>
#include <vector>

bool solveForUpperbound(const std::vector<int>& exam, const std::vector<int>& days, int limit) {
    constexpr int NO_EXAM = -1;
    // lastExamDay says which day is the last time an exam takes place in.
    std::vector<int> lastExamDay(days.size(), NO_EXAM);

    int count = 0; // count the number of unique exams from the first day to the limit.
    for (int i = limit; i >= 0; --i) {
        if (exam[i] && lastExamDay[exam[i] - 1] == NO_EXAM) {
            lastExamDay[exam[i] - 1] = i;
            ++count;
        }
    }

    if (count != days.size()) return false; // not all exams are covered with the current upperbound.

    std::vector<int> daysCpy(days);
    std::vector<int> takenExams;
    for (int i = limit; i >= 0; --i) {
        // push the last days with exam into our taken exams.
        if (exam[i] && lastExamDay[exam[i] - 1] == i) takenExams.push_back(exam[i] - 1);
        // use any days before the exam to study. the order does not matter.
        // if there are enough not-last-exam days before an exam, that exam can be completed so we pop it.
        else if (!takenExams.empty() && (--daysCpy[takenExams.back()] == 0)) takenExams.pop_back();
    }

    return takenExams.empty(); // return whether all exams were passed.
}

int solve(const std::vector<int>& exam, const std::vector<int>& days) {
    int l = 0;
    int r = exam.size() - 1;

    // test intervals to find the minumum in which all the exams can be passed using binary search.
    while (l <= r) {
        int mid = (l + r) / 2;
        // if it's possible to pass all the exams with the interval [beginning, 'mid']
        if (solveForUpperbound(exam, days, mid)) {
            r = mid - 1; // lower the upperbound to check again if there is a smaller interval.
        }
        else l = mid + 1; // move the upperbound higher.
    }

    // if r has not changed, it means that there is no answer even when the whole array is the upperbound.
    if (r == exam.size() - 1) return -1;
    return l + 1;
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> exam(n);
    std::vector<int> days(m);
    for (int i = 0; i < n; ++i) {
        std::cin >> exam[i];
    }
    for (int i = 0; i < m; ++i) {
        std::cin >> days[i];
    }

    std::cout << solve(exam, days);

    return 0;
}
