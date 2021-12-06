#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "NumberWithUnits.hpp"
using namespace std;
using namespace ariel;

const string COLOR_MENU = "\e[1;95m";
const string COLOR_QUERY = "\e[1;93m";
const string COLOR_ANSWER = "\e[1;92m";
const string COLOR_ERROR = "\e[1;31m";

void create_file(string s)
{
    ofstream file1("temp.txt");
    file1 << s;
    file1.close();
}

int main()
{
    system("clear");
    string buff, unit1, unit2, op;
    double n1 = 0, n2 = 0;
    cout << COLOR_MENU << "Welcome! supported commands: " << endl;
    cout << "insert   - \"insert <number1><unit1> = <number1><unit1>\"" << endl;
    cout << "compare  - \"compare <number1><unit1> <number1><unit1>\"" << endl;
    cout << "evaluate - \"evaluate <number1><unit1> <+,-,+=,...> <number1><unit1>\"" << COLOR_QUERY << endl;
    while (true)
    {

        cin >> op;
        cin.ignore();

        if (op == "insert")
        {
            getline(cin, buff);
            create_file(buff);
            ifstream units_file{"temp.txt"};
            NumberWithUnits::read_units(units_file);

            cout << COLOR_ANSWER << "  -> Answer: Units ratio inserted to the unit-table" << endl;
            NumberWithUnits::print_table();
            cout << COLOR_QUERY;
        }
        else if (op == "compare")
        {
            string buff;
            string unit1;
            string unit2;
            double n1 = 0;
            double n2 = 0;
            cin >> n1 >> unit1 >> n2 >> unit2;
            try
            {
                NumberWithUnits a{n1, unit1};
                NumberWithUnits b{n2, unit2};
                try
                {
                    if (a == b)
                    {
                        cout << COLOR_ANSWER << "  -> Answer: " << a << " == " << b << COLOR_QUERY << endl;
                    }
                    else if (a < b)
                    {
                        cout << COLOR_ANSWER << "  -> Answer: " << a << " < " << b << COLOR_QUERY << endl;
                    }
                    else if (a <= b)
                    {
                        cout << COLOR_ANSWER << "  -> Answer: " << a << " <= " << b << COLOR_QUERY << endl;
                    }
                    else if (a > b)
                    {
                        cout << COLOR_ANSWER << "  -> Answer: " << a << " > " << b << COLOR_QUERY << endl;
                    }
                    else if (a >= b)
                    {
                        cout << COLOR_ANSWER << "  -> Answer: " << a << " >= " << b << COLOR_QUERY << endl;
                    }
                }
                catch (const std::exception &e)
                {
                    cout << COLOR_ANSWER << "  -> Answer: " << COLOR_ERROR << e.what() << COLOR_QUERY << endl;
                }
            }
            catch (const std::exception &e)
            {
                cout << COLOR_ANSWER << "  -> Answer: " << COLOR_ERROR << e.what() << COLOR_QUERY << endl;
            }
        }
        else if (op == "evaluate")
        {
            string oper;
            string unit1;
            string unit2;
            double n1 = 0;
            double n2 = 0;
            cin >> n1 >> unit1 >> oper >> n2;
            try
            {
                NumberWithUnits a{n1, unit1};
                
                try
                {
                    if (oper == "*")
                    {
                        cout << COLOR_ANSWER << "  -> Answer: " << (a * n2) << COLOR_QUERY << endl;
                    }
                    else if (oper == "+")
                    {
                        cin >> unit2;
                        NumberWithUnits b{n2, unit2};
                        cout << COLOR_ANSWER << "  -> Answer: " << (a + b) << COLOR_QUERY << endl;
                    }
                    else if (oper == "-")
                    {
                        cin >> unit2;
                        NumberWithUnits b{n2, unit2};
                        cout << COLOR_ANSWER << "  -> Answer: " << (a - b) << COLOR_QUERY << endl;
                    }
                    else if (oper == "+=")
                    {
                        cin >> unit2;
                        NumberWithUnits b{n2, unit2};
                        cout << COLOR_ANSWER << "  -> Answer: " << (a += b) << COLOR_QUERY << endl;
                    }
                    else if (oper == "-=")
                    {
                        cin >> unit2;
                        NumberWithUnits b{n2, unit2};
                        cout << COLOR_ANSWER << "  -> Answer: " << (a -= b) << COLOR_QUERY << endl;
                    }
                }
                catch (const std::exception &e)
                {
                    cout << COLOR_ERROR << e.what() << COLOR_QUERY << endl;
                }
            }
            catch (const std::exception &e)
            {
                cout << COLOR_ANSWER << "  -> Answer: " << COLOR_ERROR << e.what() << COLOR_QUERY << endl;
            }
        }
    }
}