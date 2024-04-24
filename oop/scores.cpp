#include <iostream>
using namespace std;
// Write a program in cpp that prompts the user to enter n scores, then
// calculate and display the average of those scores.
class avrg_of_scores {
private:
  float sum = 0, avrg;

public:
  void calculate() {
    int n;
    float arr[n];

    cout << "Enter the number of scores: " << endl;
    cin >> n;
    for (int i = 0; i < n; i++) {
      cout << "Enter score " << i + 1 << ":" << endl;
      cin >> arr[i];
    }
    for (int i = 0; i < n; i++) {
      sum += arr[i];
    }
    avrg = sum / n;
    cout << "The average is: " << avrg << endl;
  }
};

int main() {
  avrg_of_scores my_scores;
  my_scores.calculate();

  return 0;
}
