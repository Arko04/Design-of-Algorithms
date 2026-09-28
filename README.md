# Design and Analysis of Algorithms

Coursework for **Design and Analysis of Algorithms** at the University of Tehran, Faculty of Electrical and Computer Engineering (Fall 2024), based on CLRS.

## Programming assignments

Competitive-programming style problems, submitted to the course's **Quera** online judge. Every solution here was **accepted** by the judge. Problem statements belong to the course and are not included; each one is summarised by the technique it needs.

| Topic | Problem | Technique | Solution |
|-------|---------|-----------|----------|
| Divide & conquer | Identical Trees | Count the insertion orders that produce the same BST: recursive split around the root, combined with binomial coefficients mod 10⁹+7 | [Python](programming-assignments/01-divide-and-conquer/p1-identical-trees.py) |
| | Mr. Amini's Club | Recursive halving with a merge step | [C++](programming-assignments/01-divide-and-conquer/p2-mr-aminis-club.cpp) |
| | Mr. Amini Again! | Divide & conquer with sorting and binary search (`lower_bound` / `upper_bound`) | [C++](programming-assignments/01-divide-and-conquer/p3-mr-amini-again.cpp) |
| Dynamic programming | Magic Scrolls | Two-state DP (reverse each string or not) to keep a sequence of strings in lexicographic order at minimum cost | [C++](programming-assignments/02-dynamic-programming/p1-magic-scrolls.cpp) |
| | Aladdin and the Genie | Probability DP computed backwards with a sliding-window sum | [C++](programming-assignments/02-dynamic-programming/p2-aladdin-and-the-genie.cpp) |
| | Symbolic Cakes | Tabular DP | [C++](programming-assignments/02-dynamic-programming/p3-symbolic-cakes.cpp) |
| | Magic Statues | Tabular DP | [C++](programming-assignments/02-dynamic-programming/p4-magic-statues.cpp) |
| Greedy | City Theater | Greedy feasibility check inside a binary search on the answer | [C++](programming-assignments/03-greedy/p1-city-theater.cpp) |
| | Harry and Friends | Greedy decomposition of an H/P string into required block counts | [C++](programming-assignments/03-greedy/p2-harry-and-friends.cpp) |
| | Obsessive Librarian | Greedy check of whether one swap can make every window valid | [C++](programming-assignments/03-greedy/p3-obsessive-librarian.cpp) |
| | Strange Project | Greedy ordering with a disjoint-set union (DSU) | [C++](programming-assignments/03-greedy/p4-strange-project.cpp) |
| Graphs | Map of Bitoya | DFS | [C++](programming-assignments/04-graph/p1-map-of-bitoya.cpp) |
| | Middle-earth | BFS shortest paths | [C++](programming-assignments/04-graph/p2-middle-earth.cpp) |
| | Stingy Crab | Minimum spanning tree (DSU) with **LCA** queries on the tree | [C++](programming-assignments/04-graph/p3-stingy-crab.cpp) |
| | Minion Banana Delivery | **Kruskal's** MST with DSU | [C++](programming-assignments/04-graph/p4-minion-banana-delivery.cpp) |
| Network flow | Game | Max-flow with **Ford–Fulkerson** (DFS augmenting paths over forward and residual edges) | [C++](programming-assignments/05-network-flow/p2-game.cpp) |

### Build & run

```bash
g++ -std=c++17 -O2 -o solve programming-assignments/04-graph/p4-minion-banana-delivery.cpp
./solve < input.txt
python3 programming-assignments/01-divide-and-conquer/p1-identical-trees.py < input.txt
```

All C++ solutions compile with GCC (`-std=c++17`). Each program reads the judge's input format from stdin.

## Written homework

My solutions to the six theory assignments are in [homework/](homework/):

| HW | Topic |
|----|-------|
| 1 | Divide and conquer, recurrences |
| 2 | Dynamic programming |
| 3 | Greedy algorithms |
| 4 | Graph algorithms |
| 5 | Network flow |
| 6 | NP-completeness and reductions |
