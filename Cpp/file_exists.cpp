#include <fstream>
#include <iostream>
using namespace std;

int main() {
  ifstream myfile;
  myfile.open("file_exists.txt");
  if (myfile) {
    cout << "File exists" << endl;
    myfile.close();
  } else {
    cout << "File does not exist" << endl;
  }
  return 0;
}
