n = int(input())

heights = list(map(int, input().split()))

def convert_to_uniques(sorted_heights) :
    i = 0
    while i < len(sorted_heights) - 1 :
        if sorted_heights[i] == sorted_heights[i + 1] :
            sorted_heights.pop(i + 1)
        else :
            i += 1

def replace_with_index(heights, sorted_heights) :
    index_replaced_heights = []
    for h in heights :
        index_replaced_heights.append(sorted_heights.index(h))
    return index_replaced_heights

def compress_heights(heights) :
    sorted_heights = sorted(heights)
    convert_to_uniques(sorted_heights)
    return replace_with_index(heights, sorted_heights)

index_replace_heights = compress_heights(heights)

dp = [[[0 for k in range(n + 1)] for j in range(n + 1)] for i in range(n + 1)]

for i in range(n + 1) :
    for j in range(n + 1) :
        dp[i][i][j] = 1

for i in range(n) :
    for j in range(n + 1) :
        if j > index_replace_heights[i] :
            dp[i][i + 1][j] = 1
        else :
            dp[i][i + 1][j] = 2

for k in range(n - 1, -1, -1) :
    for l in range(n - 1, -1, -1) :
        for r in range(l + 2, n + 1) :
            dp[l][r][k] = (dp[l][r - 1][k] + dp[l + 1][r][k] - dp[l + 1][r - 1][k])
            if index_replace_heights[l] == index_replace_heights[r - 1] and index_replace_heights[l] >= k :
                dp[l][r][k] = dp[l][r][k] + dp[l + 1][r - 1][index_replace_heights[l]]

print((dp[0][n][0] - 1) % (10 ** 9 + 7))