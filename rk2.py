N = int(input())
def kmeasure(N):
    if N == 1:
        return [0,0]
    return [kmeasure(N-1),kmeasure(N-1)]
print(kmeasure(N))