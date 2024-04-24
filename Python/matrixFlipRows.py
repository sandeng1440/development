
def reflectVertical (ar: list[list[int]]) -> list[list[int]]:
    for i in range(len(ar[0])): # number of cols 
        up = 0
        down = len(ar) - 1 # number of rows
        while(up < down):
            temp = ar[up][i]
            ar[up][i] = ar[down][i]
            ar[down][i] = temp
            up+=1
            down-=1
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
    reflectedArray = reflectVertical(array)
    print(f'\nReflected Array\n{string}')
    printMatrix(reflectedArray)

