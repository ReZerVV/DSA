def min_split(s, parts):
    n = len(s)
    parts = [0] + parts + [n]
    m = len(parts)
    dp = [[0]*m for _ in range(m)]
    for l in range(2, m):
        for i in range(m - l):
            j = i + l
            dp[i][j] = float('inf')
            for k in range(i+1, j):
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j] + parts[j]-parts[i])
    return dp[0][-1]

s = "abcdefghij"
parts = [3, 5]
print(min_split(s, parts))