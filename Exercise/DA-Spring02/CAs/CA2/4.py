n = int(input())
tapes = list(map(int, input().split()))
tapes.insert(0, -1)

def calc_min_cuts(l_ind, r_ind) :
    if l_ind > r_ind :
        return 0

    shortest_tape_pos = 0
    shortest_tape = float('inf')
    min_actions = r_ind - l_ind + 1

    for i in range(l_ind, r_ind + 1) :
        if tapes[i] < shortest_tape :
            shortest_tape = tapes[i]
            shortest_tape_pos = i

    for i in range(l_ind, r_ind + 1) :
        tapes[i] -= shortest_tape

    return min(min_actions, shortest_tape + calc_min_cuts(l_ind, shortest_tape_pos - 1) +
            calc_min_cuts(shortest_tape_pos + 1, r_ind))

print(calc_min_cuts(1, n))
