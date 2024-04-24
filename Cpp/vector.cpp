
#include <iostream>
#include <vector>
using namespace std;

int display(vector <int> vec){
    if (vec.empty()){
        cout<<"The vector is empty."<<endl;
        return 0;
    }
    for (int i=0; i<vec.size(); i++){
        cout<<vec[i]<<" -> ";
    }
    cout<<"END"<<endl;

    return 0;
}

int main(){
    vector <int> myVector;
    //myVector.assign(6,2);
    display(myVector);
    myVector.push_back(7);
    display(myVector);

    return 0;
}

