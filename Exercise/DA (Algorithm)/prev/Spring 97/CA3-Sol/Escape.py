from collections import defaultdict
from heapq import *
from sys import stdin

def readNums(single=False):
    if single:
        return int(stdin.readline())
    return [int(x) for x in stdin.readline().split()]

junctions, roads = readNums()
start, end = readNums()

neighbors = defaultdict(list)
drivers = {}
for _ in xrange(roads):
    a, b, cost = readNums()
    neighbors[a].append((b, cost))
    neighbors[b].append((a, cost))
for i in xrange(1, junctions+1):
    drivers[i] = readNums() # distance, cost

def shouldGo(node, cost, fuel, costs, maxFuel):
    prevCost = costs.get(node, float('inf'))
    prevFuel = maxFuel.get(node, -1)
    # if cost > prevCost and fuel < prevFuel or:
    if cost >= prevCost and fuel <= prevFuel:
        return False
    return True

def dijkstra(start, end):
    costs = {start: 0}
    maxFuel = {start: 0}
    heap = [(0, start, 0, False)] # (moneySpent, position, taxiTimeLeft)
    while len(heap) > 0:
        # print heap
        moneySpent, position, fuelLeft, hadCabbie = heappop(heap)
        # print moneySpent, position, fuelLeft, costs[position], maxFuel[position]
        if position == end:
            return moneySpent
        # check if been here cheaper with more taxi time left
        # if costs[position] != moneySpent or maxFuel[position] != fuelLeft:
        #     continue
        # option A: switch cabbie
        driverDistance, driverCost = drivers[position]
        if fuelLeft != driverDistance and not hadCabbie:
            heappush(heap, (moneySpent + driverCost, position, driverDistance, True))
        # option B: continue driving
        for node, distance in neighbors[position]:
            next_fuel = fuelLeft - distance
            # print "  ", node, distance, next_fuel
            if next_fuel >= 0 and shouldGo(node, moneySpent, next_fuel, costs, maxFuel):
                costs[node] = moneySpent
                maxFuel[node] = next_fuel
                heappush(heap, (moneySpent, node, next_fuel, False))
    return -1

print dijkstra(start, end)
