# the range function is partially inclusive of the boundaries
# this will print from 1-100
for i in range(1,10):
    print(i)

print('This is the end of the first print \n')

# a third parameter can be added to the range function to indicate "step"
for i in range(1,101,5):
    print(i)

print('This is the end of the range with step \n')

# To print only odd numbers between 1 and 10
for i in range(1,10,2):
    print(i)

print('This is the end of the printing of odd numbers between 1-10 \n')

# range can also be given only one parameter
for i in range(5):
    print(i)

print('This is the end of the range with one parameter. Note it starts with a zero, \nand it excludes the upper boundary as always\n')


