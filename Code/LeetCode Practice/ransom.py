def dict_maker(input_string):
    dict = {}
    for letter in input_string:
        if letter.isalpha() == True:
            if letter in dict:
                dict[letter] += 1
            else:
                dict[letter] = 1
    return dict

def comparer(dict1, dict2):
    for key, value in dict2.items():
        if key in dict1:
            if dict1[key] <= dict2[key]:
                return True
            else:
                return False
        else:
            return False

def main():
    if len(magazines) < len(ransom):
        print("It didn't work")
    else:
        ransom_dict = dict_maker(ransom)
        magazine_dict = dict_maker(magazines)
        if comparer(ransom_dict, magazine_dict) == True:
            print("It worked!")
        else:
            print("It didn't work.")

ransom = "asdfghjkl"
magazines = "asdfghjkllaksjd"

main()
