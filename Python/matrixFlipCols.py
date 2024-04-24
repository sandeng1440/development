
def reflectHorizontal (ar: list[list[int]]) -> list[list[int]]:
    for i in range(len(ar)): # number of rows
        left = 0
        right = len(ar[i]) - 1 # number of columns
        while(left < right):
            temp = ar[i][left]
            ar[i][left] = ar[i][right]
            ar[i][right] = temp
            left+=1
            right-=1
    return ar

def printMatrix(ar: list[list[int]]) -> None:
    for i in range(len(ar)):
        print(f'{ar[i]}')

if __name__=='__main__':
    array: list[list[int]] = [
            [0,1,2],
            [1,2,3],
            [2,3,4]
    ]
    string = '-' * 20
    print(f'\nUnreflected Array\n{string}')
    printMatrix(array)
    reflectedArray = reflectHorizontal(array)
    print(f'\nReflected Array\n{string}')
    printMatrix(reflectedArray)

