# given a long string of words, build word cloud data in the dictionary
# where key = words and value = number of times the word occurred
# what do we do with capitalized words and/or names?
# what should we do with punctuation?
# make your own reasonable decisions - for instance "Add" and "add" could be one word with value 2


# example:
# word_data = "Hello world, my baby is my world!"
#potential output = {"hello": 1, "world": 2, "my": 2, "baby": 1, "is": 1}
import string

def splitter(word_data):
    for punctuation in string.punctuation:
        word_data = word_data.replace(punctuation, "")
    return word_data.split()

def counterer(split_data):
    counter_dict = {}
    for word in split_data:
        if word in counter_dict:
            counter_dict[word] += 1
        else:
            counter_dict[word] = 1
    return counter_dict

def main():
    sample_string = splitter(word_data)
    counter_dict = counterer(sample_string)
    print(counter_dict)

word_data = "Hello world, food is my world!"

main()
