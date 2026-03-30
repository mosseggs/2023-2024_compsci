list1 = ["a", "b", "c", "d", "e", "f"]
list2 = [1, 2, 3, 4, 5]

# prints from the 1st index on, starting at 0
print(list1[1:])

# prints from the 2nd index to the 4th (non inclusive)
print(list2[2:4])

# prints the -1st index, or the last index.
print(list2[-1])

# prints from the start to the 3rd index, starting at 0
print(list1[:3])

# prints from the -3rd index to the -1st index, or the 3rd from the back to the last index
print(list1[-3: -1])

# prints from the 1st index to the 4th index with iterations of 2, starting at 0
print(list1[1: 4: 2])

# concat the 2 lists beginning with list 1 and then adding on list 2
print(list1 + list2)

# start from the 5th index to the 1st index, counting backwards with iterations of 1, starting at 0. It just counts it backwards.
print(list1[5: 1: -1])