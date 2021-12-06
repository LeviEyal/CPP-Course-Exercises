/**
 * Demo file for the exercise on numbers with units
 *
 * @author Erel Segal-Halevi
 * @since 2019-02
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "NumberWithUnits.hpp"
using namespace ariel;

int main() {
  ifstream units_file{"unitss.txt"};
  NumberWithUnits::read_units(units_file);

  NumberWithUnits a{2, "km"};   // 2 kilometers
  cout << "a:\t" << a << endl;           // Prints "2[km]".
  cout << "(-a):\t" << (-a) << endl;    // Prints "-2[km]"
  cout << "(3*a):\t" << (3*a) << endl;    // Prints "6[km]"
  cout << "(a*3):\t" << (a*3) << endl;    // Prints "6[km]"

  NumberWithUnits b{300, "m"};  // 300 meters
  cout << "(a+b):\t" << (a+b) << endl;   // Prints "2.3[km]". Note: units are determined by first number (a).
  cout << "(b-a):\t" << (b-a) << endl;   // Prints "-1700[m]". Note: units are determined by first number (b).

  NumberWithUnits d{200, "cm"};  // 300 meters
  cout << "(a+d):\t" << (a+d) << endl;   // Prints "2.002[km]".
  cout << "(d-a):\t" << (d-a) << endl;   // Prints "-199800[cm]".

  cout << boolalpha; // print booleans as strings from now on:
  cout << "(a>b):\t" << (a>b) << endl;  // Prints "true"
  cout << "(a<=b):\t" << (a<=b) << endl;  // Prints "false"
  cout << "(a==NumberWithUnits{2000, \"m\"}):\t" << (a==NumberWithUnits{2000, "m"}) << endl;  // Prints "true"

  istringstream sample_input{"700 [ kg ]"};
  sample_input >> a;
  cout << a << endl;   // Prints "700[kg]"
  cout << (a += NumberWithUnits{1, "ton"}) << endl;  // prints "1700[kg]"
  cout << a << endl;   // Prints "1700[kg]". Note that a has changed.

  NumberWithUnits c{1, "km"};
  cout << "postfix inc (should be 1):" << c++ << endl;
  cout << "current (should be 2):" << c << endl;
  cout << "prefix inc (should be 3):" << ++c << endl;
  cout << "current (should be 3):" << c << endl;
  cout << "postfix dec (should be 3):" << c-- << endl;
  cout << "current (should be 2):" << c << endl;
  cout << "prefix dec (should be 1):" << --c << endl;
  cout << c++ << endl;
  try {
    cout << (a+b) << endl;  
  } catch (const std::exception& ex) {
    cout << ex.what() << endl; // Prints "Units do not match - [m] cannot be converted to [kg]"
  }
  NumberWithUnits::print_table();
  cout << "End of demo!" << endl;
  return 0;
}
