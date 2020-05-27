# choosing 2 movies whose total runtimes will equal the exact flight length
# take integer flight_length (in minutes)
# list of integers movie_lengths (in minutes)
# returns boolean -> whether there are 2 numbres in movie_lengths whose sum equals flight_length
# assume users will watch exactly 2 movies
# dont make the users watch the same movie twice
# optimize for runtime over memory


# example movie lengths: 1, 2, 3, 4, 5
# example flight length: 7

# iterate from 1 +2, +3, +4, +5
# then iterate from 2 +3, +4, +5
# then 3 +4, +5
# then 4 +5

list1 = [1,2,3,4,5]

def comparer(flight_length):
    for x in range(0, len(list1)):
        for y in range(x+1, len(list1)):
            if list1[x] + list1[y] == int(flight_length):
                print("True")
            else:
                print("False")

def main():
    flight_length = input("Length of flight in hours(int): ")
    comparer(flight_length)

main()
