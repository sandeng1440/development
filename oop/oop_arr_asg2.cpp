// NOTE: GROUP D
// Michael Ted 22/05883
// Grace Wanjiru 19/04014
// Randy Kariuki 22/05571
// Michelle Naisenya 22/06098
// Deng Athian 22/07144

#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

// Structure to hold participant data
struct EventData {
  int numParticipants;
  double **expenditures;

  // Constructor to initialize the structure
  EventData(int participants) : numParticipants(participants) {
    // Memory for the 2-D array
    expenditures = new double *[numParticipants];
    for (int i = 0; i < numParticipants; ++i) {
      expenditures[i] =
          new double[4]; // 4 categories: food, drinks, transport, entertainment
    }
  }

  // data entry for each participant
  void inputData() {
    cout << "---------------------------------------------------" << endl;
    for (int i = 0; i < numParticipants; ++i) {
      cout << "\nEnter expenditures for participant " << (i + 1) << endl
           << "---------------------------------------------------" << endl;
      for (int j = 0; j < 4; ++j) {
        switch (j) {
        case 0:
          cout << "Food: ";
          cin >> expenditures[i][j];
          break;
        case 1:
          cout << "Drinks: ";
          cin >> expenditures[i][j];
          break;
        case 2:
          cout << "Transport: ";
          cin >> expenditures[i][j];
          break;
        default:
          cout << "Entertainment: ";
          cin >> expenditures[i][j];
        }
      }
    }
    // cout << "---------------------------------------------------" << endl;
  }

  // Calculate total expenditure for all participants
  double totalExp() {
    double total = 0.0;
    for (int i = 0; i < numParticipants; ++i) {
      for (int j = 0; j < 4; ++j) {
        total += expenditures[i][j];
      }
    }
    return total;
  }

  // Calculate mean expenditure for participants
  double meanExp() { return totalExp() / (numParticipants * 4); }

  // Calculate the variance for the expenditure
  double varianceExp() {
    double mean = meanExp();
    double variance = 0.0;
    for (int i = 0; i < numParticipants; ++i) {
      for (int j = 0; j < 4; ++j) {
        variance += pow(expenditures[i][j] - mean, 2);
      }
    }
    return variance / (numParticipants * 4);
  }

  // Destructor to free the memory
  ~EventData() {
    for (int i = 0; i < numParticipants; ++i) {
      delete[] expenditures[i];
    }
    delete[] expenditures;
  }
};

int main() {
  int numParticipants;
  cout << "Enter the number of participants in the event: ";
  cin >> numParticipants;

  // Create an instance of the ParticipantData structure
  EventData eventData(numParticipants);

  // Input data for each participant
  eventData.inputData();

  // Display results
  cout << fixed << setprecision(2);
  cout << "\nTotal: Ksh." << eventData.totalExp() << endl;
  cout << "Mean: Ksh." << eventData.meanExp() << endl;
  cout << "Variance: Ksh." << eventData.varianceExp() << endl;

  return 0;
}
