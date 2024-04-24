
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

std::string formatDate(const time_t &t) {
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

int main() {
  // Get current time
  time_t now = time(nullptr);

  // Call formatDate function
  std::string formattedDate = formatDate(now);

  // Output the formatted date
  std::cout << formattedDate << std::endl;

  return 0;
}
