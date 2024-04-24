class Node:
    def __init__(self, value):
        self.value = value
        self.next = None

    def get_data(self):
        return self.value

    def set_data(self, value):
        self.value = value

    def get_next(self):
        return self.next

    def set_next(self, next):
        self.next = next


class LList:
    def __init__(self):
        self.head = None

    def insertF(self, value):
        newNode = Node(value)
        newNode.next = self.head
        self.head = newNode

    def getList(self):
        current = self.head
        while current is not None:
            print(current.value, "->", end=" ")
            current = current.next
        print("None \n")

    def rmByVal(self, value):
        current = self.head
        while current.next.value != value:
            current = current.next
        temp = current.next
        print(temp.value, "has been removed BY VALUE from the linked list")
        current.next = current.next.next
        del temp

    def rmById(self, index):
        current = self.head
        for i in range(1, index):
            current = current.next
        temp = current.next
        print(
            temp.value, "has been removed BY INDEX [", index, "] from the linked list"
        )
        current.next = current.next.next
        del temp

    def insertL(self, value):
        current = self.head
        while current.next is not None:
            current = current.next
        newNode = Node(value)
        current.next = newNode
        print(value, "has been added to the END of the linked list")

    def insertToId(self, value, index):
        current = self.head
        for i in range(1, index):
            current = current.next
        newNode = Node(value)
        newNode.next = current.next
        current.next = newNode
        print(value, "has been added at INDEX [", index, "] of the linked list")


# node1 = Node(35)
# print(node1.get_data())
myList = LList()
myList.insertF(3)
myList.insertF(5)
myList.insertF(14)
myList.insertF(9)
myList.insertF(1)
myList.insertF(7)
myList.insertF(10)
myList.getList()
myList.rmByVal(14)
myList.getList()
myList.rmById(4)
myList.getList()
myList.insertL(99)
myList.getList()
myList.insertToId(150, 3)
myList.getList()
