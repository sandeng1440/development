#include <iostream>
#include <map>
#include <string>
using namespace std;

void digits_name(int);
map<int, string> Digits = {{0, "zero"},  {1, "one"},  {2, "two"}, {3, "three"},
                           {4, "four"},  {5, "five"}, {6, "six"}, {7, "seven"},
                           {8, "eight"}, {9, "nine"}};

int main() {
  int input = 0;
  do {
    cout << "\nEnter a number: ";
    cin >> input;
    cout << endl;
    digits_name(input);
  } while (true);
}

void digits_name(int num) {
  int k = num / 10;
  if (k == 0) {
    cout << Digits[num] << " ";
    return;
  }
  digits_name(k);
  cout << Digits[num % 10] << " ";
}
