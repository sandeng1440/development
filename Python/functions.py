# A function is definced using the keyword 'def'
def sumFunction(a,b):
    result = a + b
    return result # a function must return something

num1 = int(input('Enter the first number: '))
num2 = int(input('Enter the second number: '))

print('The sum of',num1,'and',num2,'is: ',sumFunction(num1,num2))


