
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  vector<int> twoSum(vector<int> &nums, int target) {
    vector<int> result;
    for (int i = 0; i < nums.size(); i++) {
      if (!result.empty()) {
        break;
      }
      for (int j = 0; j < nums.size(); j++) {
        if (i == j) {
          continue;
        } else {
          if (nums[i] + nums[j] == target) {
            result = {i, j};
            break;
          }
        }
      }
    }
    return result;
  }
} Solution;

void display(vector<int> &v) {
  if (v.empty()) {
    cout << "The vector is empty" << endl;
  } else {
    cout << "[";
    for (int i = 0; i < v.size(); i++) {
      cout << v[i];
      if (i != v.size() - 1) {
        cout << ",";
      } else {
        cout << "]" << endl;
      }
    }
    cout << endl;
  }
}

int main() {
  vector<int> List = {2, 7, 11, 15};
  int target = 9;
  int num = 23;
  vector<int> result = Solution.twoSum(List, target);
  display(result);
  if ((num + target) > 10) {
    cout << "It is greater" << endl;
  }
  return 0;
}
