
#include <iostream>
#include <queue>
using namespace std;


void menu(){
    cout<<"\n\n";
    cout<<"-----------------"<<endl;
    cout<<"CHOOSE AN ACTIION"<<endl;
    cout<<"-----------------"<<endl;
    cout<<"1. Add to the back of the queue."<<endl;
    cout<<"2. Remove the element at the front of the queue."<<endl;
    cout<<"3. Exit"<<endl;
    cout<<endl;
    cout<<"Number: "<<endl;
}

queue<int> myQueue;

void pushMenu(){
    cout<<"Enter the number to push to the queue: "<<endl;
    int val;
    cin>>val;
    myQueue.push(val);
}
int display(){
    if (myQueue.empty()){
        cout<<"The queue is empty."<<endl;
        return 0;
    }
    cout<<myQueue.front()<<" -> ... -> "<<myQueue.back()<<" ("<<myQueue.size()<<")"<<endl;
    return 0;
}

int main(){
    
    int val;
    while(val != 3){
        menu();
        cin>>val;
        switch (val){
            case 1:
                pushMenu();
                display();
                break;
            case 2:
                if (myQueue.empty()){
                    cout<<"The queue is empty."<<endl;
                    break;
                }
                myQueue.pop();
                display();
                break;
            case 3:
                return 0;
            default:
                cout<<"Invalid option."<<endl;
        }
    }
    return 0;
}

