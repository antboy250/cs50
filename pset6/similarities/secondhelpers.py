from enum import Enum


class Operation(Enum):
    """Operations"""

    DELETED = 1
    INSERTED = 2
    SUBSTITUTED = 3

    def __str__(self):
        return str(self.name.lower())


def distances(a, b):
    """Calculate edit distance from a to b"""
    lengthrow = len(a) + 2
    lengthcol = len(b) + 2
    table = [[0 for x in range(lengthcol)] for y in range(lengthrow)]
    table[0][1] = ""
    table[1][0] = ""
    table[1][1] = (0, None)
    i = 2
    cost = 0
    for char in a:
        table[i][0] = char
        table[i][1] = (cost, Operation.DELETED)
        cost += 1
        i += 1
    j = 2
    cost = 0
    for char in b:
        table[0][j] = char
        table[1][j] = (cost, Operation.INSERTED)
        cost += 1
        j += 1

    i=2
    j=2
    #putting in whole table into helper function to do recursively or iteratively we will see
    for chara in a:
        for charb in b:
            table[i][j] = distance(table, i, j, a, b)
            j += 1
        i += 1

    return table

memo = {}
def distance(tabla, row, col, worda, wordb):
    if worda[:row] == "":
        return (len(wordb[:col]), Operation.INSERTED)
    if wordb[:col] == "":
        return (len(worda[:row]), Operation.DELETED)
    extra = 0 if worda[row] == wordb[col] else 1

    i1 = (tabla, row-1, col, worda, wordb)
    print(i1)
    if not i1 in memo:
        memo[i1] = distance(*i1)
    j1 = (tabla, row, col-1, worda, wordb)
    if not j1 in memo:
        memo[j1] = distance(*j1)
    ij1 = (tabla, row-1, col-1, worda, wordb)
    if not ij1 in memo:
        memo[ij1] = distance(*ij1)
    data = [(memo[i1], Operation.DELETED), (memo[j1], Operation.INSERTED),(memo[ij1] + extra, Operation.SUBSTITUTED)]


    cost_op = min(data, key = lambda t: t[0])

    return cost_op