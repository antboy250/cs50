import cs50
import sys

key = sys.argv[1].lower()


text = cs50.get_string("plaintext: ")

def cypher(string):
    if not key.isalpha():
        print("USAGE: python vigenere.py key")
        return 1
    size = len(key)
    cyphered = ""
    count = 0
    for char in string:
        if char.isalpha():
            cyphered += chr(ord(char) + ord(key[count%size]) - 97)
        else:
            cyphered += char
        count += 1
    return cyphered

print(cypher(text))