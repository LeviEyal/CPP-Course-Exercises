/************************************************************************************
 * C++ course, Ariel university.
 * Assignment number 3.
 *
 * AUTHORS: Eyal Levi
 * https://github.com/LeviEyal
 * Date: 2021-04
 ***********************************************************************************/
#include <iostream>
#include <map>
#include <string>

namespace ariel {
    class NumberWithUnits{

    private:
        double amount;
        std::string unit;

    public:
        NumberWithUnits(double amount, const std::string& unit);
        static void read_units(std::ifstream& units_file);
        static void print_table();
        friend int compare(const NumberWithUnits& n1, const NumberWithUnits& n2);

        /* Overloading the in/out stream operators - Declerations */
        friend std::ostream& operator<<(std::ostream& out, const NumberWithUnits& t);
        friend std::istream& operator>>(std::istream& in, NumberWithUnits& t);

        /* Overloading the arithmetic operators */
        NumberWithUnits operator+(const NumberWithUnits& n2);
        NumberWithUnits operator-(const NumberWithUnits& n2);
        NumberWithUnits operator-();
        NumberWithUnits operator+();

        NumberWithUnits& operator+=(const NumberWithUnits& n2);
        NumberWithUnits& operator-=(const NumberWithUnits& n2);
        NumberWithUnits& operator*=(const double num);

        /* Increment operations overiding */
        NumberWithUnits& operator++();
        NumberWithUnits& operator--();
        NumberWithUnits operator++(int);
        NumberWithUnits operator--(int);

        /* Multiplication operations overiding */
        friend NumberWithUnits operator*(const NumberWithUnits& n, const double num);
        friend NumberWithUnits operator*(const double num, const NumberWithUnits& n);

        /* Overloading the comparison operators - Declerations */
        friend bool operator>(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator>=(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator<(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator<=(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator==(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator!=(const NumberWithUnits& n1, const NumberWithUnits& n2);
    };
}