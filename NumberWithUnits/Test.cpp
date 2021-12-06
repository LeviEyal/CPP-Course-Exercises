/************************************************************************************
 * C++ course, Ariel university.
 * Assignment number 3.
 *
 * AUTHORS: Eyal Levi
 * https://github.com/LeviEyal
 * Date: 2021-04
 ***********************************************************************************/

#include "doctest.h"
#include "NumberWithUnits.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <stdexcept>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace ariel;
using namespace std;

/************************************************************************************************
 *                                        UTILITIES
************************************************************************************************/
const int NUMBER_OF_TESTS = 1000;
const string FILE_CONTENT_1(
    (string)"1 km = 1000 m\n"
    "1 m = 100 cm\n" +
    "1 kg = 1000 g\n" +
    "1 ton = 1000 kg\n" +
    "1 hour = 60 min\n" +
    "1 min = 60 sec\n" +
    "1 USD = 3.33 ILS\n" +
    "1 cm = 10mm"
);
const string FILE_CONTENT_2(
    (string)"1 inch = 25.4 mm\n" +
    "1 cm = 10 mm\n" +
    "1 foot = 30.48 cm\n" +
    "1 mile = 5280 foot\n" +
    "1 yard = 36 inch"
);                        
/* All units divided by dimentions :*/
const vector<vector<string>> allUnits = {
    {"kg", "g", "ton"},
    {"km", "m", "cm", "mm"},
    {"hour", "min", "sec"},
    {"ILS", "USD"}
};
/* Generates a random Integer with a specified range : */
double random(int from, int to)
{
    return from + rand() % ((to + 1) - from);
}
/* Creates a txt file containing a given string : */
void create_file(string s)
{
    ofstream file1("temp.txt");
    file1 << s;
    file1.close();
}

/************************************************************************************************
 *                                        ALL TESTS
************************************************************************************************/
TEST_CASE("Testing the constructor")
{
    create_file(FILE_CONTENT_1);
    ifstream units_file{"temp.txt"};
    NumberWithUnits::read_units(units_file);

    vector<string> exists_units = {
        "km", "m", "cm", "mm", "kg", "g", "ton", "hour", "min", "sec", "USD", "ILS"
    };
    vector<string> not_exists_units = {
        "tm", "r", "kml", "Meters", "KM", "G", "Ton", "Hour", "minutes", "seconds", "usd", "ils"
    };

    uint arraySize = not_exists_units.size();
    for (uint i = 0; i < NUMBER_OF_TESTS; i++)
    {
        /* Check not existing unit in the units-table - invalid!: */
        CHECK_THROWS(NumberWithUnits a = NumberWithUnits(1, not_exists_units[i % arraySize]));
        /* Check existing unit in the units-table - valid!: */
        CHECK_NOTHROW(NumberWithUnits b = NumberWithUnits(1, exists_units[i % arraySize]));
    }
}

/*-----------------------------------------------------------------------------------------*/
TEST_CASE("Testing the units-table expanding")
{
    create_file(FILE_CONTENT_1);
    ifstream units_file{"temp.txt"};
    NumberWithUnits::read_units(units_file);
    CHECK_NOTHROW(NumberWithUnits a = NumberWithUnits(1, "g"));     //should be exist
    CHECK_THROWS(NumberWithUnits b = NumberWithUnits(1, "yard"));  //should NOT be exist
    
    create_file(FILE_CONTENT_2);
    ifstream units_file1{"temp.txt"};
    NumberWithUnits::read_units(units_file1);
    CHECK_NOTHROW(NumberWithUnits a = NumberWithUnits(1, "g"));     //should remain exist
    CHECK_NOTHROW(NumberWithUnits b = NumberWithUnits(1, "yard"));  //now it should be exist
}

/*-----------------------------------------------------------------------------------------*/

TEST_CASE("Testing the +, - operators")
{
    for (uint i = 0; i < NUMBER_OF_TESTS; i++)
    {
        /* Picking a random numbers: */
        double r1 = random(1, 1000);
        double r2 = random(1, 1000);
        double r3 = random(1, 1000);
        double r4 = random(1, 1000);

        /* Creating a random NumberWithUnits objects: */
        NumberWithUnits rand_km{r1, "km"};
        NumberWithUnits rand_m{r2, "m"};
        NumberWithUnits rand_sec{r3, "sec"};
        NumberWithUnits rand_min{r4, "min"};

        SUBCASE("The operator +")
        {
            /* Testing for appropiate addition: */
            CHECK(rand_km + rand_m == NumberWithUnits{r1 + (r2 / 1000), "km"});
            CHECK(rand_m + rand_km == NumberWithUnits{r2 + (r1 * 1000), "m"});
            CHECK(rand_sec + rand_min == NumberWithUnits{r3 + (r4 * 60), "sec"});
            CHECK(rand_min + rand_sec == NumberWithUnits{r4 + (r3 / 60), "min"});
            /* Throws an error when trying to sum two units from different dimentions*/
            CHECK_THROWS(rand_km + rand_sec);
            CHECK_THROWS(rand_sec + rand_km);
        }
        SUBCASE("The operator -")
        {
            /* Testing for appropiate subtraction: */
            CHECK(rand_km - rand_m == NumberWithUnits{r1 - (r2 / 1000), "km"});
            CHECK(rand_m - rand_km == NumberWithUnits{r2 - (r1 * 1000), "m"});
            CHECK(rand_sec - rand_min == NumberWithUnits{r3 - (r4 * 60), "sec"});
            CHECK(rand_min - rand_sec == NumberWithUnits{r4 - (r3 / 60), "min"});
            /* Throws an error when trying to subtract a unit from a different dimention unit*/
            CHECK_THROWS(rand_km - rand_sec);
            CHECK_THROWS(rand_sec - rand_km);
        }
    }
}
/*-----------------------------------------------------------------------------------------*/

TEST_CASE("Testing the UNARY +, - operators")
{
    for (uint i = 0; i < NUMBER_OF_TESTS; i++)
    {
        /* Picking a random numbers: */
        double r = random(1, 1000);

        /* Creating a random NumberWithUnits objects: */
        NumberWithUnits rand_km{r, "km"};

        /* Testing the unary operator + */
        CHECK((+rand_km) == NumberWithUnits{+r, "km"});
        /* Testing the unary operator - */
        CHECK(-rand_km == NumberWithUnits{-r, "km"});
    }
}
/*-----------------------------------------------------------------------------------------*/

TEST_CASE("Testing the ++/-- operators")
{
    for (uint i = 0; i < NUMBER_OF_TESTS; i++)
    {
        /* Picking a random number: */
        double r = random(1, 1000);

        /* Picking a random unit: */
        uint k = random(0, allUnits.size() - 1);    //dimention
        uint j = random(0, allUnits[k].size() - 1); //unit from the dimention
        string rand_unit = allUnits[k][j];
        NumberWithUnits a{r, rand_unit};

        SUBCASE("Testing the opartor ++")
        {
            CHECK(a++ == NumberWithUnits{r++, rand_unit});
            CHECK(a == NumberWithUnits{r, rand_unit});
            CHECK(++a == NumberWithUnits{++r, rand_unit});
            CHECK(a == NumberWithUnits{r, rand_unit});
        }
        SUBCASE("Testing the opartor --")
        {
            CHECK(a-- == NumberWithUnits{r--, rand_unit});
            CHECK(a == NumberWithUnits{r, rand_unit});
            CHECK(--a == NumberWithUnits{--r, rand_unit});
            CHECK(a == NumberWithUnits{r, rand_unit});
        }
    }
}
/*-----------------------------------------------------------------------------------------*/

TEST_CASE("Testing the +=, -= operators")
{
    for (uint i = 0; i < NUMBER_OF_TESTS; i++)
    {
        /* Picking a random numbers: */
        double r1 = random(1, 1000);
        double r2 = random(1, 1000);

        /* Creating a random NumberWithUnits objects: */
        NumberWithUnits rand_km{r1, "km"};
        NumberWithUnits rand_m{r2, "m"};

        SUBCASE("The operator +=")
        {
            /* Testing for appropiate addition: */
            CHECK((rand_km += rand_m) == NumberWithUnits{r1 += (r2 / 1000), "km"});
            CHECK(rand_km == NumberWithUnits{r1, "km"});
            CHECK((rand_m += rand_km) == NumberWithUnits{r2 += (r1 * 1000), "m"});
            CHECK(rand_m == NumberWithUnits{r2, "m"});
        }
        SUBCASE("The operator -=")
        {
            CHECK((rand_km -= rand_m) == NumberWithUnits{r1 -= (r2 / 1000), "km"});
            CHECK(rand_km == NumberWithUnits{r1, "km"});
            CHECK((rand_m -= rand_km) == NumberWithUnits{r2 -= (r1 * 1000), "m"});
            CHECK(rand_m == NumberWithUnits{r2, "m"});
        }
    }
}
/*-----------------------------------------------------------------------------------------*/

TEST_CASE("Testing the multiplication operators: {float*x, x*float, float*=x}")
{
    for (uint i = 0; i < NUMBER_OF_TESTS; i++)
    {
        /* Picking a random numbers: */
        double r = random(1, 1000);
        double rand_float_number = random(1, 1000);

        /* Picking a random unit: */
        uint dim = random(0, allUnits.size() - 1);
        uint j = random(0, allUnits[dim].size() - 1);
        string rand_unit = allUnits[dim][j];

        NumberWithUnits a{r, rand_unit};
        CHECK((a * rand_float_number) == NumberWithUnits{r * rand_float_number, rand_unit});
        CHECK((rand_float_number * a) == NumberWithUnits{rand_float_number * r, rand_unit});
        CHECK((a *= rand_float_number) == NumberWithUnits{r *= rand_float_number, rand_unit});
        CHECK(a == NumberWithUnits{r, rand_unit});
    }
}
/*-----------------------------------------------------------------------------------------*/

TEST_CASE("Testing the operators >> and <<")
{
    NumberWithUnits a{1, "cm"};

    for (uint i = 0; i < NUMBER_OF_TESTS; i++)
    {
        /* Picking a random number: */
        double rand_number = random(1, 1000);

        /* Picking a random unit: */
        uint dim = random(0, allUnits.size() - 1);
        uint j = random(0, allUnits[dim].size() - 1);
        string rand_unit = allUnits[dim][j];

        /* Testing the operator >>:*/
        istringstream sample{to_string(rand_number) + " [ " + rand_unit + " ]"};
        CHECK_NOTHROW(sample >> a);
        CHECK(a == NumberWithUnits{rand_number, rand_unit});

        /* Testing the operator << :*/
        ostringstream ans;
        ostringstream expected;
        expected << rand_number << "[" << rand_unit << "]";
        ans << a;
        CHECK(ans.str() == expected.str());
    }
}
/*-----------------------------------------------------------------------------------------*/

TEST_CASE("Testing the comparison operators: {>, >=, <, <=, ==, !=}")
{
    CHECK(NumberWithUnits{2, "km"} < NumberWithUnits{2003, "m"});
    CHECK(NumberWithUnits{3000, "m"} > NumberWithUnits{2.9, "km"});
    CHECK(NumberWithUnits{2, "km"} != NumberWithUnits{3000, "m"});
    CHECK(NumberWithUnits{3000, "m"} != NumberWithUnits{2, "km"});

    CHECK(NumberWithUnits{90, "cm"} < NumberWithUnits{3000, "m"});
    CHECK(NumberWithUnits{3000, "m"} > NumberWithUnits{90, "cm"});
    CHECK(NumberWithUnits{90, "cm"} != NumberWithUnits{3000, "m"});
    CHECK(NumberWithUnits{3000, "m"} != NumberWithUnits{90, "cm"});

    CHECK(NumberWithUnits{300, "cm"} == NumberWithUnits{3, "m"});
    CHECK(NumberWithUnits{3, "m"} == NumberWithUnits{300, "cm"});

    /* Throws an error when trying to compare two units from different dimentions*/
    for (uint i = 0; i < NUMBER_OF_TESTS; i++)
    {
        /* Picking a random numbers: */
        double r1 = random(1, 1000);
        double r2 = random(1, 1000);
        bool b;
        CHECK_THROWS(b = (NumberWithUnits{r1, "cm"} == NumberWithUnits{r2, "hour"}));
        CHECK_THROWS(b = (NumberWithUnits{r1, "cm"} < NumberWithUnits{r2, "sec"}));
        CHECK_THROWS(b = (NumberWithUnits{r1, "kg"} > NumberWithUnits{r2, "m"}));
        CHECK_THROWS(b = (NumberWithUnits{r1, "g"} <= NumberWithUnits{r2, "sec"}));
        CHECK_THROWS(b = (NumberWithUnits{r1, "ILS"} >= NumberWithUnits{r2, "hour"}));
        CHECK_THROWS(b = (NumberWithUnits{r1, "USD"} != NumberWithUnits{r2, "kg"}));
    }
}