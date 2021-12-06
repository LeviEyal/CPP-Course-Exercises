/************************************************************************************
 * C++ course, Ariel university.
 * Assignment number 3.
 *
 * AUTHORS: Eyal Levi
 * https://github.com/LeviEyal
 * Date: 2021-04
 ***********************************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <map>
#include "NumberWithUnits.hpp"
using namespace std;

const double EPS = 0.001;
const int COLUMN_WIDTH = 20;

namespace ariel {
    
    static map<string, map<string, double> > table;
//-----------------------------------------------------------------------------------------------------------------
    /**
     * @brief Construct a new Number With Units:: Number With Units object
     * 
     * @param amount 
     * @param unit 
     */
    NumberWithUnits::NumberWithUnits(double amount, const string& unit){
        if(table.count(unit) == 0){
            throw invalid_argument{"Unit doesn't exist in the units table!"};
        }
        this->amount = amount;
        this->unit = unit;
    }
//-----------------------------------------------------------------------------------------------------------------
    /**
     * @brief Read a text file with each line in the format:
     *          "1 <unit1> = <ratio> <unit2>"nit
     *        For example:
     *          "1 km = 1000 m"
     *        And build a table of units ratios.
     * 
     * @param units_file A file stream contains the units as described above.
     */
    void NumberWithUnits::read_units(ifstream& units_file) {
        string buff;
        string unit1;
        string unit2;
        double n1 = 0;
        double n2 = 0;
        while(units_file >> n1 >> unit1 >> buff >> n2 >> unit2) {
            table[unit1][unit2] = n2;
            table[unit2][unit1] = 1/n2;
            table[unit1][unit1] = 1;
            table[unit2][unit2] = 1;

            /* connect all nodes to each other in current GCC (same dimention)*/
            for (const auto &pair1 : table[unit1]) {
                for (const auto &pair2 : table[unit2]) {
                    table[pair1.first][pair2.first] = table[pair1.first][unit1] * table[unit1][unit2] * table[unit2][pair2.first];
                    table[pair2.first][pair1.first] = 1.0 / table[pair1.first][pair2.first];
                }
            }
        }
    }

//-----------------------------------------------------------------------------------------------------------------
    /**
     * @brief convert val of unit1 to unit2
     *        For Example:
     *              convert from 3[km] to 3000[m],
     *              convert from 30[sec] to 0.5[min],
     *              convert from 3.7[ton] to 3700[kg]. etc.
     * 
     * @param val   A given value of unit1 to be converted to unit2.
     * @param from  source unit
     * @param to    destination unit
     * @return      double The converted value
     */
    double convertFromTo(double val, const string& from, const string& to){
        if(from == to) {return val;}
        try {
            return val * table.at(from).at(to);
        }
        catch(const exception& e) {
            throw invalid_argument{"Units do not match - ["+from+"] cannot be converted to ["+to+"]"};
        }
    }

//-----------------------------------------------------------------------------------------------------------------
    /* Overloading the in\out stream operators: {<<, >>} */

    ostream& operator<<(ostream& out, const NumberWithUnits& t){
        out << t.amount << "[" << t.unit << "]";
        return out;
    }
    
    istream& operator>>(istream& in, NumberWithUnits& t){
        string buff;
        double val;
        in >> val;
        /* Stream into buff until first ']' char */ 
        getline(in, buff, ']');
        /* Remove all spaces: */ 
        buff.erase(remove(buff.begin(), buff.end(), ' '), buff.end());
        /* Remove '[' char */ 
        buff = buff.substr(1, buff.size() - 1);
 
        t = NumberWithUnits{val, buff};
        return in;
    }
//-----------------------------------------------------------------------------------------------------------------
    /* Overloading the arithmetic operators: {+, +=, -, -=} */

    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits& n2) {
        double converted = convertFromTo(n2.amount, n2.unit, this->unit);
        NumberWithUnits ans(this->amount+converted, this->unit);
        return ans;
    }
    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits& n2) {
        double converted = convertFromTo(n2.amount, n2.unit, this->unit);
        NumberWithUnits ans(this->amount-converted, this->unit);
        return ans;
    }
    NumberWithUnits NumberWithUnits::operator+() {
        NumberWithUnits ans(+this->amount, this->unit);
        return ans;
    }
    NumberWithUnits NumberWithUnits::operator-() {
        NumberWithUnits ans(-this->amount, this->unit);
        return ans;
    }
    NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits& n2) {
        *this = *this + n2;
        return *this;
    }
    NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits& n2) {
        *this = *this - n2;
        return *this;
    }

//-----------------------------------------------------------------------------------------------------------------
    /* Overloading the Increament\Decreament operators: {++x, x++, --x, x--} */

    NumberWithUnits& NumberWithUnits::operator++() {  //prefix
        ++(this->amount);
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator++(int) {  //postfix
        return NumberWithUnits((this->amount)++, this->unit);
    }
    NumberWithUnits& NumberWithUnits::operator--() {  //prefix
        --(this->amount);
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator--(int) {  //postfix
        return NumberWithUnits((this->amount)--, this->unit);
    }

//-----------------------------------------------------------------------------------------------------------------
    /* Overloading the Multiplication operator: {number*x, x*number, x*=number, number*=x} */

    NumberWithUnits operator*(const NumberWithUnits& n, const double num) {
        return NumberWithUnits(n.amount*num, n.unit);
    }
    NumberWithUnits operator*(const double num, const NumberWithUnits& n) {
        return NumberWithUnits(n.amount*num, n.unit);
    }
    NumberWithUnits& NumberWithUnits::operator*=(const double num) {
        this->amount *= num;
        return *this;
    }

//-----------------------------------------------------------------------------------------------------------------
    /* Overloading the comparison operators: {>, >=, <, <=, ==, !=} */

    int compare(const NumberWithUnits& n1, const NumberWithUnits& n2){
        
        double x = n1.amount - convertFromTo(n2.amount, n2.unit, n1.unit);
        int ans = 0;
        if(x > EPS){ ans = 1;}
        else if(-x > EPS) {ans = -1;}
        return ans;
    }

    bool operator>(const NumberWithUnits& n1, const NumberWithUnits& n2){
        return compare(n1, n2) > 0;
    }
    bool operator>=(const NumberWithUnits& n1, const NumberWithUnits& n2){
        return compare(n1, n2) >= 0;
    }
    bool operator<(const NumberWithUnits& n1, const NumberWithUnits& n2){
        return compare(n1, n2) < 0;
    }
    bool operator<=(const NumberWithUnits& n1, const NumberWithUnits& n2){
        return compare(n1, n2) <= 0;
    }
    bool operator==(const NumberWithUnits& n1, const NumberWithUnits& n2){
        return compare(n1, n2) == 0;
    }
    bool operator!=(const NumberWithUnits& n1, const NumberWithUnits& n2){
        return compare(n1, n2) != 0;
    }

//-----------------------------------------------------------------------------------------------------------------
    /**
     * @brief Print the converting-units-table.
    */
    void NumberWithUnits::print_table(){
        uint m = 0;
        for(auto &elem : table){
            uint size = elem.second.size();
            m = std::max(m, size);
        }
        string line(m*COLUMN_WIDTH/2, '-');
        
        cout << line << " UNITS TABLE " << line  << endl;
        for(auto &elem1 : table){
            cout << "1 " << elem1.first << "\t:=";
            for(auto &elem2 : table[elem1.first]){
                string t = to_string(elem2.second) + "[" + elem2.first + "]";
                cout << right << std::setw(COLUMN_WIDTH) << t;
            }
            cout << endl;
        }
        cout << line << "---- END ----" << line  << endl;
    }
}