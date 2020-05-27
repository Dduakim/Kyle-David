# take input of n, make a dictionary with n number of keys
# take further input of n amounts and create respective key - field pairs
# take further input of names and if the name exists as a key, return the phone number associated
# if name does not exist, return "Not Found"


# first figure out method of input, how to take input line by line
# dict_maker creates dictionary and iterates over n times, taking the n next inputs as key-value pairs
# return dictionary as global
# dict_checker checks all subsequent inputs on if they exist as keys in dictionary;
# if they exist print the value, if don't exist then return "Not Found"

def dict_test():
    dict = []
    for n in range(2):
        dict += input()
    return dict

def main():
    dict = dict_test()
    print(dict)

main()
