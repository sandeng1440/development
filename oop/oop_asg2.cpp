
#include <cmath>
#include <iostream>
#include <list>
using namespace std;

struct eventData {
  // 2-D array
  int n;
  list<list<int>> expenses;
  float sum, mean, var;

  // constructor
  eventData() {
    sum = 0.0;
    mean = 0.0;
    var = 0.0;
  }

  // Data entry
  void setData() {
    cout << "\nEnter the number of participants: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
      cout << "\nEnter for participant " << i + 1 << ": " << endl;
      cout << "---------------------------------------------------------"
           << endl;
      int k = 0;
      list<int> part;
      for (int j = 0; j < 4; j++) {
        switch (j) {
        case 0:
          cout << "Food: ";
          cin >> k;
          part.push_back(k);
          break;
        case 1:
          cout << "\nDrinks: ";
          cin >> k;
          part.push_back(k);
          break;
        case 2:
          cout << "\nTransport: ";
          cin >> k;
          part.push_back(k);
          break;
        default:
          cout << "\nEntertainment: ";
          cin >> k;
          part.push_back(k);
        }
      }
      expenses.push_back(part);
    }
  }

  // Total, mean, variance
  void analyseData() {

    // mean and sum
    for (auto &part : expenses) {
      for (auto &item : part) {
        sum += item;
      }
    }
    mean = sum / n;

    // variance
    for (auto &part : expenses) {
      for (auto &item : part) {
        var += pow(item - mean, 2);
      }
    }
    var /= (n * 4);
  }
};

int main() {
  eventData myData;
  myData.setData();
  myData.analyseData();

  cout << endl
       << "-------------------------------------------------" << endl
       << "Sum: " << myData.sum << endl;
  cout << "Mean: " << myData.mean << endl;
  cout << "Variance: " << myData.var << endl;

  return 0;
}
