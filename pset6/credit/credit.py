import cs50

cardnum = cs50.get_int("Number: ")
while cardnum <= 0:
    cardnum = cs50.get_int("Number: ")

# length = len(str(cardnum))

def cardvalid(card):
    length = len(str(card))
    strcard = str(card)
    if length != 15 and length != 16 and length != 13:
        print("INVALID")
        return 1
    total = 0
    count = 1
    while card > 0:
        if count % 2 == 1:
            total = total + card % 10
        else:
            total = total + (2 * (card % 10)) % 10 + (2 * (card % 10))//10
        count += 1
        card = card//10
    if total % 10 == 0:
        if length == 15 and strcard[0] == "3" and (strcard[1] == "4" or strcard[1] == "7"):
            print("AMEX")
            return 0
        elif (length == 13 or length == 16) and strcard[0] == "4":
            print("VISA")
            return 0
        elif length == 16 and (strcard[0] == "5" and (strcard[1] == "1" or strcard[1] == "2"
        or strcard[1] == "3" or strcard[1] == "4" or strcard[1] == "5")):
            print("MASTERCARD")
            return 0
        else:
            print("INVALID")
            return 0
    else:
        print("INVALID")
        return 1

cardvalid(cardnum)