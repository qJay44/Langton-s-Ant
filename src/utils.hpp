#include <iostream>
#include <sstream>

// Custom locale separator
struct separated : std::numpunct<char> {
  char do_thousands_sep() const { return ' '; }
  std::string do_grouping() const { return "\03"; }
};

// Separate thousands
static std::string formatWithDots(int value) {
  static std::locale ourLocal(std::cout.getloc(), new separated);
  std::stringstream ss;
  ss.imbue(ourLocal);
  ss << std::fixed << value;

  return ss.str();
};

