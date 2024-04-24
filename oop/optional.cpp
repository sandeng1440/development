#include <cstdio>
#include <iostream>
#include <optional>
#include <string>
using namespace std;

int main(){
  optional<int> p, q;
  string userInput;
  cout<<"Enter p: ";
  getline(cin, userInput);
  cout<<endl;
  if(!userInput.empty()) p = stoi(userInput);
  cout<<"Enter q: ";
  getline(cin, userInput);
  cout<<endl;
  if(!userInput.empty()) q = stoi(userInput);

  cout<<endl<<"p: "<< *p <<endl<<"q: "<<*q<<endl<<"p + q: "<<(*p + *q)<< endl;
  return 0;
}
