n, m = map(int, input().split())
table = []
for i in range(n) :
    table.append(list(map(int, input().split())))

INF = 10 ** 10

dp0 = [[INF for j in range(m)] for i in range(n)] # Just move right in a row
dp1 = [[INF for j in range(m)] for i in range(n)] # Just move left in a row

dp0[0][0] = table[0][0]
dp1[0][0] = table[0][0]

for j in range(1, m) :
    dp0[0][j] = dp0[0][j - 1] + table[0][j]

for i in range(1, n) :
    for j in range(m) :
        if j > 0 :
            dp0[i][j] = min(dp0[i - 1][j], dp1[i - 1][j], dp0[i][j - 1]) + table[i][j]
            dp1[i][m - 1 - j] = min(dp1[i - 1][m - 1 - j], dp0[i - 1][m - 1 - j], dp1[i][m - j]) + table[i][m - 1 - j]
        else :
            dp0[i][j] = min(dp0[i - 1][j], dp1[i - 1][j]) + table[i][j]
            dp1[i][m - 1 - j] = min(dp1[i - 1][m - 1 - j], dp0[i - 1][m - 1 - j]) + table[i][m - 1 - j]

print(dp0[n - 1][m - 1])
