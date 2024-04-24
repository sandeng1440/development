class Node:
    def __init__(self, value) -> None:
        self.value = value
        self.next = None


class Link_list:
    def __init__(self, value) -> None:
        self.head = Node(value)
        print("insert_front(", value, "):", self.print_list())

    def insert_front(self, value) -> None:
        newNode = Node(value)
        newNode.next = self.head
        self.head = newNode
        print("insert_front(", value, "):", self.print_list())

    def insert_back(self, value) -> None:
        newNode = Node(value)
        current = self.head
        while current.next is not None:
            current = current.next
        current.next = newNode
        print("insert_back(", value, "):", self.print_list())

    def insert_at(self, index, value) -> None:
        current = self.head
        while range(index - 1):
            current = current.next
        newNode = Node(value)
        newNode.next = current.next
        current.next = newNode
        print("insert_at(", index, ",", value, "):", self.print_list())

    def print_list(self) -> None:
        current = self.head
        while current is not None:
            print(current.value, "-> ", end="")
            current = current.next
        print("None")


myList = Link_list(35)
myList.print_list()
myList.insert_front(3)
myList.insert_back(67)
myList.insert_at(1, 9)
