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
    table = [[0 for char in range(lengthcol)] for char2 in range(lengthrow)]
    table[0][1] = ""
    table[1][0] = ""
    table[1][1] = (0, None)
    i = 2
    cost = 1
    for char in a:
        table[i][0] = char
        table[i][1] = (cost, Operation.DELETED)
        cost += 1
        i += 1
    j = 2
    cost = 1
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
            table[i][j] = tablebuilder(table, i, j)
            j += 1
        i += 1
        j = 2
    print(table)
    return table

def tablebuilder(tabla, row, col):
    chara = tabla[row][0]
    # print(chara)
    charb = tabla[0][col]
    # print(charb)
    data1 = [(tabla[row-1][col][0] + 1, Operation.DELETED), (tabla[row][col-1][0] + 1, Operation.INSERTED), (tabla[row-1][col-1][0], Operation.SUBSTITUTED)]
    data2 = [(tabla[row-1][col][0] + 1, Operation.DELETED), (tabla[row][col-1][0] + 1, Operation.INSERTED), (tabla[row-1][col-1][0] + 1, Operation.SUBSTITUTED)]
    if chara == charb:
        tabla[row][col] = min(data1, key = lambda t: t[0])
    else:
        tabla[row][col] = min(data2, key = lambda t: t[0])
    return tabla[row][col]

