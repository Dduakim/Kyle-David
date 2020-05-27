'''
given a list of integers, return an integer of length of longest increasing subsequence within the
set of numbers.

ex: if list = [1,2,3,1,2,5,6,3,43,1]

return 3 (1, 2, 3)

todo:

receive input list from user
create two variables
    local counter
    global counter
iterate through list starting from second index
if value is greater than previous value, increase local counter by 1
check if local counter is greater than global counter, if so then set global counter = local counter
if value is not greater than previous value, reset local counter to 0
print value of global counter
'''

def counter(user_list):
    local_count = 1
    global_count = 0
    for count in range(1, len(user_list)):
        if user_list[count] > user_list[count-1]:
            local_count += 1
        if local_count > global_count:
            global_count = local_count
        elif user_list[count] <= user_list[count-1]:
            local_count = 1
    return global_count


def main():
    user_list = [int(x) for x in input().split()]
    print(counter(user_list))

main()
