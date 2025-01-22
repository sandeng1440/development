class Node:
    def __init__(self, value) -> None:
        self.value = value
        self.next = None


class Link_list:
    def __init__(self, value) -> None:
        self.head = Node(value)
        print(f"insert_front({value}): {self}")

    def insert_front(self, value) -> None:
        newNode = Node(value)
        newNode.next = self.head
        self.head = newNode
        print(f"insert_front({value}): {self}")

    def insert_back(self, value) -> None:
        newNode = Node(value)
        current = self.head
        while current.next is not None:
            current = current.next
        current.next = newNode
        print(f"insert_back({value}): {self}")

    def insert_at(self, index, value) -> None:
        current = self.head
        while range(index - 1):
            current = current.next
        newNode = Node(value)
        newNode.next = current.next
        current.next = newNode
        print(f"insert_at({index}, {value}): {self}")

    def __str__(self) -> str:
        current = self.head
        out = ''
        while current is not None:
            out += f'{current.value} -> '
            current = current.next
        out += 'None'
        return out

myList = Link_list(35)
print(myList)
myList.insert_front(3)
myList.insert_back(67)
myList.insert_at(1, 9)
print(myList)
