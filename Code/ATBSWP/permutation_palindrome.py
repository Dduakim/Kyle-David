'''
Write an efficient function that checks whether any permutation of an input string is a palindrome.

When given a string, iterate through and create counter for each unique char in the string

for final counts of each char, only one char can be odd, the rest must all be even


pseudo:
create dictionary
iterate through string
    if char exists then +1 to the value for that hash
    else create the hash of that char in dict
check values of dict, if only one hash has an odd value, then return true
else return false


'''



def counter(input_string):
    dict1 = {}
    for charr in input_string:
        if charr in dict1:
            dict1[charr] += 1
        else:
            dict1[charr] = 1
    return dict1

def palindrome(dict1):
    odd_count = 0
    for odd in dict1.values():
        if odd % 2 != 0:
            odd_count += 1
        if odd_count >= 2:
            return False
    if odd_count < 2:
        return True

def main():
    input_string = input("What is the string? ")
    dict1 = counter(input_string)
    print(palindrome(dict1))

main()
