import cs50
#ask use for integer for pyramid height
height = cs50.get_int("Enter Pyramid Height: ")
while height > 23 or height < 0:
    height = cs50.get_int("Enter Pyramid Height: ")

def pyramid(rows):
    for row in range(rows):
        print(" "*(rows - (row + 1)), end="")
        print("#"*(row + 1), end="")
        print("  ", end="")
        print("#"*(row + 1))

pyramid(height)