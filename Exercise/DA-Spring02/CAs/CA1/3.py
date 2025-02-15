def update_side(side):
    if len(side) == 0:
        return '[]'
    return '[' + ', '.join(f"'{robot}'" for robot in side) + ']'

def update_state(state_number, left_side, right_side):
    left_str = update_side(left_side)
    right_str = update_side(right_side)
    return f'State{state_number}: {left_str}{right_str}'

def move_right(robot, left, right, robots_count) :
    for i in range(robots_count) :
        left.remove(robot)
        if robot == 'S' :
            right.append(robot)
        else :
            right.insert(0, robot)

def move_left(robot, left, right, robot_count) :
    for i in range(robot_count) :
        right.remove(robot)
        left.append(robot)

def cross_river(left, right):
    steps_number = 0
    solution = ""

    if right.count('S') == 1:
        print('Impossible to cross all robots')
        return

    state_number = 1
    solution += update_state(state_number, left, right) + '\n'

    while True:
        solution += 'Action: Right\n'
        steps_number += 1

        if right.count('S') == 0 or left.count('L') == 0:
            move_right('S', left, right, 2)
        else:
            move_right('L', left, right, 1)

        state_number += 1
        solution += update_state(state_number, left, right) + '\n'

        if len(left) == 0:
            break

        solution += 'Action: Left\n'
        steps_number += 1

        move_left('S', left, right, 1)

        state_number += 1
        solution += update_state(state_number, left, right) + '\n'

    return steps_number, solution

left = ['L', 'L', 'S', 'S']
right = []
steps, solution = cross_river(left, right)

print(f'Solution: {steps}')
print(solution)