def binary_search(arr: list[int], target: int) -> int | None:
    start = 0
    end = len(arr) - 1
    while start <=end:
        mid = (start + end) // 2
        if(arr[mid] == target):
            return mid
        if(target < arr[mid]):
            end = mid - 1
        else:
            start = mid + 1
    return None

def recursive_binary_search(arr: list[int], target: int) -> bool:
    if(len(arr) == 0):
        return False
    
    mid = len(arr) // 2
    if(target == arr[mid]):
        return True
    if(target < arr[mid]):
        return recursive_binary_search(arr[:mid], target)
    else:
        return recursive_binary_search(arr[mid + 1:], target)
    
def main():
    l = [0,1,2,3,4,5,6,7,8,9,10,11,12]
    print(f'Binary Search(7): {binary_search(l,7)}')
    print(f'Recursive Binary Search(7): {recursive_binary_search(l,7)}')

main()
