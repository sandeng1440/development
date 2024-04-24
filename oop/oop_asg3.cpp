/*
 *
 * By Deng Athian
 * RegNo: 22/07144
 *
 * */
#include <array>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// student
class Student {
private:
  array<string, 2> details;
  array<int, 6> results;
  float total;
  char grade;

public:
  // method that runs all the methods in the right order
  void runner();
  // inputting the values
  bool enterResults();
  // calculate total score
  void totalScore();
  // calculating the grade
  void gradeStudent();
  // displaying the details
  void showDetails();
  // outputting values to file: accepts the filename as an argument
  void outputFile(string);
  // method that checks whether the file already exists: accepts the filename as
  // the argument
  bool fileExists(string);
  // method to append to file if it exists: accepts filename as argument
  void appendToFile(string);
  // method to format the time/date: accepts the time as the argument
  string formatDate(const time_t &);
};

// login interface
bool login(string, string);
// menu for the admin after login
int adminMenu();

int main() {
  bool r = true;
  do { // loop to check if the credentials are correct
    r = login("admin", "user1");
    if (!r) {
      cout << "\nInvalid credentials. Try again...";
    } else {
      cout << "\nWelcome";
    }
  } while (!r);

  int choice = 0;
  do {
    choice = adminMenu();
    if (choice == 1) {
      Student newStud;
      newStud.runner();
    }
  } while (choice != 2);
  return 0;
}

// login
bool login(string un, string pwd) {
  string usrname, passwd;
  cout << "\nLogin..." << endl << "Username: ";
  cin >> usrname;
  cout << "Password: ";
  cin >> passwd;
  return usrname == un && passwd == pwd;
}

// menu for admin
int adminMenu() {
  int choice = 0;
  cout << "\nChoose..." << endl
       << "1) Enter student results" << endl
       << "2) Quit" << endl;
  cin >> choice;
  if (cin.fail()) {
    choice = 0;
    cout << "Enter a valid choice...";
  }
  return choice;
}

void Student::runner() {
  bool l;
  do {
    l = enterResults();
  } while (!l);
  totalScore();
  gradeStudent();
  outputFile("students_scores.txt");
}

bool Student::enterResults() {
  array<int, 6> limits = {5, 5, 10, 15, 15, 50};
  string input;
  // details
  cout << "\nEnter Student's Details..." << endl;
  cout << "RegNo: ";
  cin >> details[0];
  cout << "Name: ";
  cin >> details[1];
  // results
  cout << "\nEnter Student's Results..." << endl;
  for (int i = 0; i < results.size(); ++i) {
    bool t = true;
    if (i < results.size() - 3) {
      do {
        cout << "Assignment " << i + 1 << "(x/" << limits[i] << "): ";
        cin >> input;
        try {
          results[i] = stoi(input);
        } catch (const exception &e) {
          results[i] = -1;
        }
        if (results[i] <= limits[i] && results[i] >= 0) {
          t = false;
        } else {
          cout << "ERROR: Value off limits -> [0..." << limits[i] << "]" << endl
               << "Retry..." << endl;
        }
      } while (t);
    } else if (i < results.size() - 1) {
      do {
        cout << "CAT " << i - 2 << "(x/15): ";
        cin >> input;
        try {
          results[i] = stoi(input);
        } catch (const exception &e) {
          results[i] = -1;
        }
        if (results[i] <= limits[i] && results[i] >= 0) {
          t = false;
        } else {
          cout << "ERROR: Value off limits -> [0..." << limits[i] << "]" << endl
               << "Retry..." << endl;
        }
      } while (t);
    } else {
      do {
        cout << "Exam(x/50): ";
        cin >> input;
        try {
          results[i] = stoi(input);
        } catch (const exception &e) {
          results[i] = -1;
        }
        if (results[i] <= limits[i] && results[i] >= 0) {
          t = false;
        } else {
          cout << "ERROR: Value off limits -> [0..." << limits[i] << "]" << endl
               << "Retry..." << endl;
        }
      } while (t);
    }
  }
  // displaying the values for the user to confirm or discard
  showDetails();
  // confirming the entered values
  cin.ignore();
  cout << "Confirm [Y/n]: ";
  getline(cin, input);
  if (input.empty() || input == "Y" || input == "y") {
    return true;
  } else if (input == "N" || input == "n") {
    return false;
  } else {
    cout << "Defaulting to Y";
    return true;
  }
}

void Student::showDetails() {
  cout << "\nRegNo: " << details[0] << endl
       << "Student Name: " << details[1] << endl;
  for (int i = 0; i < results.size(); ++i) {
    if (i < results.size() - 3) {
      cout << "Assignment " << i + 1 << ": " << results[i] << endl;
    } else if (i < results.size() - 1) {
      cout << "CAT " << i - 2 << ": " << results[i] << endl;
    } else {
      cout << "Exam: " << results[i] << endl;
    }
  }
}

void Student::totalScore() {
  total = 0;
  for (int i = 0; i < results.size(); ++i) {
    total += results[i];
  }
}

void Student::gradeStudent() {
  if (total >= 70)
    grade = 'A';
  else if (total >= 60)
    grade = 'B';
  else if (total >= 50)
    grade = 'C';
  else if (total >= 40)
    grade = 'D';
  else
    grade = 'E';
}

bool Student::fileExists(string filename) {
  ifstream file;       // declaration
  file.open(filename); // opening; if it exists, then a file descriptor is
                       // returned, else a null value is returned
  if (file) {          // if a file descriptor exists then it's true else it is
                       // false
    file.close();      // close if it exists
    return true;
  } else {
    return false;
  }
}

string Student::formatDate(const time_t &t) {
  // Convert time_t to tm structure
  tm *ltm = localtime(&t);

  // Define days of the week and months
  const char *days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                          "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

  // Format the date
  std::stringstream ss;
  ss << std::setw(3) << days[ltm->tm_wday] << " " << std::setw(2)
     << std::setfill('0') << ltm->tm_mday << " " << months[ltm->tm_mon] << " "
     << ltm->tm_year + 1900 << " " << std::setw(4) << std::setfill('0')
     << ltm->tm_hour * 100 + ltm->tm_min << " "
     << (ltm->tm_hour < 12 ? "AM" : "PM");

  return ss.str();
}

void Student::appendToFile(string fName) {
  ofstream outFile(fName, ios::app);
  if (outFile.is_open()) {
    for (int i = 0; i < details.size(); ++i) {
      outFile << left << setw(13) << details[i];
    }
    for (int i = 0; i < results.size(); ++i) {
      outFile << left << setw(13) << results[i];
    }
    outFile << left << setw(15) << total;
    outFile << left << setw(13) << grade << endl;
  }
}

void Student::outputFile(string fileName) {
  if (fileExists(fileName)) {
    appendToFile(fileName);
  } else {
    // Add headings and the date/time before appending to the file
    // date/time
    time_t now = time(nullptr);
    string date = formatDate(now);
    string postTime = "Scores Posted On " + date;
    // headings
    ofstream outFile(fileName, ios::app);
    if (outFile.is_open()) {
      outFile << postTime << endl
              << left << setw(13) << "RegNo" << setw(13) << "Name" << setw(13)
              << "Asg1(x/5)" << setw(13) << "Asg2(x/5)" << setw(13)
              << "Asg3(x/10)" << setw(13) << "CAT1(x/15)" << setw(13)
              << "CAT2(x/15)" << setw(13) << "Exam(x/50)" << setw(15)
              << "Total(x/100)" << setw(13) << "Grade" << endl;
    }
    outFile.close();
    appendToFile(fileName);
  }
  cout << "\nFilename: " << fileName << endl;
}
