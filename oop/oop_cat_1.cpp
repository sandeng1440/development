#include <cstdio>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <optional>
#include <ostream>
#include <string>
using namespace std;

class Student {
private:
  string name, remark, s_asg1, s_asg2, s_asg3, s_cat1,
      s_cat2; // these extra string versions of the optional<int> asg1... are
              // for handling blank inputs
  int attendance, totalMarks;
  int assignmentsMissed = 0,
      catsMissed = 0; // initialized to 0 so as to increment
  optional<int> asg1, asg2, asg3, cat1,
      cat2; // optional because they can be left blank

  // method to calculate the totalMarks and the remark
  void set() {
    if (attendance <= 4) { // if number of attended classes does not exceed 4
      remark = "Repeat unit";
    } else {
      // number of attended classes exceeds 4
      switch (assignmentsMissed) {
      case 0:
        switch (catsMissed) {
        case 0:
          remark = "Issue exam card"; // attendance > 4, assignmentsMissed = 0,
                                      // catsMissed = 0
          break;
        case 1:
          remark = "Seek permission"; // attendance > 4, assignmentsMissed = 0,
                                      // catsMissed = 1
          break;
        default:
          remark = "Repeat unit"; // attendance > 4, assignmentsMissed = 0,
                                  // catsMissed > 1
        }
        break;
      default:
        remark = "Repeat unit"; // attendance > 4, assignmentsMissed > 0,
                                // catsMissed >= 1
      }
    }
    totalMarks = *asg1 + *asg2 + *asg3 + *cat1 + *cat2;
  }

public:
  // check whether the file already exists
  bool file_check() {
    ifstream file_stud; // declaration
    file_stud.open(
        "students.txt"); // opening; if it exists, then a file descriptor is
                         // returned, else a null value is returned
    if (file_stud) { // if a file descriptor exists then it's true else it is
                     // false
      file_stud.close(); // close if it exists
      return true;
    } else {
      return false;
    }
  }

  void get() {
    string userInput; // all user input shall be taken by this variable
    cout << "Enter Name: ";
    cin >> name;
    cout << "Enter Attendance: ";
    cin >> attendance;
    cin.ignore(); // solves an issue whereby asg1 is skipped and the user is
                  // unable to input anything

    // =============================================ASSIGNMENT1
    cout << "Enter Assignment 1: ";
    getline(cin, userInput); // normal cin does not allow blanks as input

    // Handling optional inputs
    if (!userInput.empty()) {
      try { // this is successful if the input is a number
        asg1 = stoi(userInput);
        s_asg1 = userInput;
      } catch (const exception
                   &e) { // is triggered whenever the input is not a number
        cout << "Invalid input: Value left empty." << endl;
        s_asg1 = "-"; // placeholder for when an assignment has not been done
        asg1 = 0;     // set to 0 to ensure that the totalMarks is valid
        assignmentsMissed++; // used to check how many assignments have not been
                             // done
      }
    } else { // this is triggered when the input is blank
      s_asg1 = "-";
      asg1 = 0; // set to 0 to ensure that the totalMarks is valid
      assignmentsMissed++;
    }

    // ==============================================ASSIGNMENT2
    cout << "Enter Assignment 2: ";
    getline(cin, userInput);
    if (!userInput.empty()) {
      try {
        asg2 = stoi(userInput);
        s_asg2 = userInput;
      } catch (const exception &e) {
        cout << "Invalid input: Value left empty." << endl;
        s_asg2 = "-";
        asg2 = 0;
        assignmentsMissed++;
      }
    } else {
      s_asg2 = "-";
      asg2 = 0;
      assignmentsMissed++;
    }

    // ==============================================ASSIGNMENT3
    cout << "Enter Assignment 3: ";
    getline(cin, userInput);
    if (!userInput.empty()) {
      try {
        asg3 = stoi(userInput);
        s_asg3 = userInput;
      } catch (const exception &e) {
        cout << "Invalid input: Value left empty." << endl;
        s_asg3 = "-";
        asg3 = 0;
        assignmentsMissed++;
      }
    } else {
      s_asg3 = "-";
      asg3 = 0;
      assignmentsMissed++;
    }

    // ==============================================CAT1
    cout << "Enter CAT 1: ";
    getline(cin, userInput);
    if (!userInput.empty()) {
      try {
        cat1 = stoi(userInput);
        s_cat1 = userInput;
      } catch (const exception &e) {
        cout << "Invalid input: Value left empty." << endl;
        s_cat1 = "-";
        cat1 = 0;
        catsMissed++;
      }
    } else {
      s_cat1 = "-";
      cat1 = 0;
      catsMissed++;
    }

    // ==============================================CAT2
    cout << "Enter CAT 2: ";
    getline(cin, userInput);
    if (!userInput.empty()) {
      try {
        cat2 = stoi(userInput);
        s_cat2 = userInput;
      } catch (const exception &e) {
        cout << "Invalid input: Value left empty." << endl;
        s_cat2 = "-";
        cat2 = 0;
        catsMissed++;
      }
    } else {
      s_cat2 = "-";
      cat2 = 0;
      catsMissed++;
    }

    // calls for functions to calculate remark and totalMarks and perform file
    // output
    set();
    outputFile();
  }

  void outputFile() { // method to output info to the file

    bool check = file_check(); // returns true if file exists
    ofstream student_file("students.txt", ios::app);
    if (!check) { // if file does not exist
      cout << endl << "NOTE: New file created >>> students.txt" << endl << endl;
      student_file << left << setw(17) << "Student_Name" << setw(15)
                   << "Attendance" << setw(9) << "Asg1" << setw(9) << "Asg2"
                   << setw(9) << "Asg3" << setw(9) << "CAT1" << setw(9)
                   << "CAT2" << setw(10) << "Total" << setw(20) << "Remark"
                   << endl;
    }
    cout << endl << "NOTE: File changed >>> students.txt" << endl << endl;
    student_file << left << setw(17) << name << setw(15) << attendance
                 << setw(9) << s_asg1 << setw(9) << s_asg2 << setw(9) << s_asg3
                 << setw(9) << s_cat1 << setw(9) << s_cat2 << setw(10)
                 << totalMarks << setw(20) << remark << endl;
    student_file.close();
  }
};

int menu() { // menu for selecting what to do
  cout << setfill('_') << setw(64) << "MENU";
  cout << endl
       << "Choose between the options below by entering the number:" << endl
       << endl
       << "1) Enter new student details" << endl
       << "2) Exit" << endl;
  cout << setfill('_') << setw(64) << "WRITTEN BY: Deng Athian 22/07144"
       << endl;
  int ch;
  cin >> ch;
  return ch;
}
void doStuff(int ch) { // function to handle the class Student
  if (ch == 1) {
    cout << endl << "NOTE: Entering new student details..." << endl;
    Student myStud;
    myStud.get();
  } else if (ch == 2) {
    exit(0);
  } else {
    cout << endl << "Invalid option" << endl;
  }
}

// ===============================main
int main() {
  int ch;
  do {
    ch = menu();
    doStuff(ch);
  } while (ch != 2); // 2 is for exit
  return 0;
}
