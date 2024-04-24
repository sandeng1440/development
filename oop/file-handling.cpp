#include <fstream>
#include <iostream>
using namespace std;

// instantiate file handler
// open file
// read/write file
// close file

int main() {
  ofstream my_file("file_for_handling.txt", ios::app);
  my_file << "This is a file made by file-handling.cpp.o" << endl;
  my_file << "This is the second line. I hope it is placed on the next line"
          << endl;
  my_file.close();
  return 0;
}
