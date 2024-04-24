#include <stdio.h>

struct node{
	int value;
	struct node* link;

	node(){
		value = 0;
		link = 0;
	}

};

struct singlyLL{
	struct node* head;
	//int insertFirst(int);
	//int displayList();

	void insertFirst(int x){
		struct node listNode;
		listNode.value = x;
		listNode.link = head->link;
		head.link = &listNode;
		
		
	}
	
	void displayList(){
		struct node* trav;
		trav = head;
		
		while(trav.link != 0){
			printf("%d -> ",trav.value);

		}
		printf("NULL");
		
		
	}
	
	singlyLL(){
		head = 0;
	}

};



int main(){
	struct singlyLL linkedList;
	linkedList.insertFirst(3);
	linkedList.insertFirst(6);
	linkedList.insertFirst(1);
	linkedList.displayList();
	

	return 0;
}
