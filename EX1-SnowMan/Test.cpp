/************************************************************************************
 * Test units for for testing snowman.cpp
 *
 * AUTHORS: Eyal Levi
 * https://github.com/LeviEyal
 * Date: 2021-03
 ***********************************************************************************/

#include <string>
#include <algorithm>

#include "doctest.h"
#include "snowman.hpp"

using namespace ariel;
using namespace std; 

/**
 * Returns the input string without the whitespace characters: space, newline and tab.
 * Requires std=c++2a.
 */
string nospaces(string input) {
	std::erase(input, ' ');
	std::erase(input, '\t');
	std::erase(input, '\n');
	std::erase(input, '\r');
	return input;
}

/**
 * This Test Case will assert that an input number will NOT be valid
 * if it has some digit not in the range 1-4.
 */
TEST_CASE("number digits out of range"){
    CHECK_THROWS(snowman(51111111));
    CHECK_THROWS(snowman(15111111));
    CHECK_THROWS(snowman(11511111));
    CHECK_THROWS(snowman(11151111));
    CHECK_THROWS(snowman(11115111));
    CHECK_THROWS(snowman(11111511));
    CHECK_THROWS(snowman(11111151));
    CHECK_THROWS(snowman(11111115));
    CHECK_THROWS(snowman(11111110));
    CHECK_THROWS(snowman(11111101));
    CHECK_THROWS(snowman(11111011));
    CHECK_THROWS(snowman(11110111));
    CHECK_THROWS(snowman(11101111));
    CHECK_THROWS(snowman(11011111));
    CHECK_THROWS(snowman(10111111));
}

/**
 * This Test Case will assert that an input number will NOT be valid
 * if it has less than 8 digits.
 */
TEST_CASE("Input number too small"){
    CHECK_THROWS(snowman(1));
    CHECK_THROWS(snowman(11));
    CHECK_THROWS(snowman(111));
    CHECK_THROWS(snowman(1111));
    CHECK_THROWS(snowman(11111));
    CHECK_THROWS(snowman(111111));
    CHECK_THROWS(snowman(1111111));
    CHECK_THROWS(snowman(2321435));
    CHECK_THROWS(snowman(2314321));
    CHECK_THROWS(snowman(1234));
}

/**
 * This Test Case will assert that an input number will NOT be valid
 * if it has more than 8 digits.
 */
TEST_CASE("Input number too big"){
    CHECK_THROWS(snowman(232142735));
    CHECK_THROWS(snowman(232142735));
    CHECK_THROWS(snowman(111111111));
    CHECK_THROWS(snowman(123412341));
    CHECK_THROWS(snowman(444444444));
}

/**
 * This Test Case will assert that an input number will not be valid
 * if it is a negative number.
 */
TEST_CASE("Input negative number"){
    CHECK_THROWS(snowman(-11111111));
    CHECK_THROWS(snowman(-22222222));
    CHECK_THROWS(snowman(-33333333));
    CHECK_THROWS(snowman(-44444444));
}

/**
 * This Test Case will assert that the function snowman picks the head properly.
 * It will test only the head options - the first digit in the number/
 */
TEST_CASE("Testing the head of a snowman") {
    CHECK(nospaces(snowman(11111111)) == nospaces("       \n _===_ \n (.,.) \n<( : )>\n ( : ) "));
    CHECK(nospaces(snowman(11111111)) == nospaces("       \n _===_ \n (. , .) \n< ( : )>\n (  : ) "));
    CHECK(nospaces(snowman(21111111)) == nospaces("  ___  \n ..... \n (.,.) \n<( : )>\n ( : ) "));
    CHECK(nospaces(snowman(31111111)) == nospaces("   _   \n  /_\\  \n (.,.) \n<( : )>\n ( : ) "));
    CHECK(nospaces(snowman(41111111)) == nospaces("  ___  \n (_*_) \n (.,.) \n<( : )>\n ( : ) "));
}

/**
 * This Test Case will assert that the function snowman picks the nose properly.
 * It will test only the nose options - the second digit in the number/
 */
TEST_CASE("Testing the nose of a snowman") {
    CHECK(nospaces(snowman(11111111)) == nospaces("       \n _===_ \n (.,.) \n<( : )>\n ( : ) "));
    CHECK(nospaces(snowman(12111111)) == nospaces("       \n _===_ \n (...) \n<( : )>\n ( : ) "));
    CHECK(nospaces(snowman(13111111)) == nospaces("       \n _===_ \n (._.) \n<( : )>\n ( : ) "));
    CHECK(nospaces(snowman(14111111)) == nospaces("       \n _===_ \n (. .) \n<( : )>\n ( : ) "));
}

/**
 * This Test Case will assert that the function snowman picks the left eye properly.
 * It will test only the left eye options - the third digit in the number/
 */
TEST_CASE("Testing the left eye of a snowman") {
    CHECK(nospaces(snowman(11111111)) == nospaces("       \n _===_ \n (.,.) \n<( : )>\n ( : ) "));
    CHECK(nospaces(snowman(11211111)) == nospaces("       \n _===_ \n (o,.) \n<( : )>\n ( : ) "));
    CHECK(nospaces(snowman(11311111)) == nospaces("       \n _===_ \n (O,.) \n<( : )>\n ( : ) "));
    CHECK(nospaces(snowman(11411111)) == nospaces("       \n _===_ \n (-,.) \n<( : )>\n ( : ) "));
}

/**
 * This Test Case will assert that the function snowman picks the right eye properly.
 * It will test only the right eye options - the fourth digit in the number/
 */
TEST_CASE("Testing the right eye of a snowman") {
    CHECK(nospaces(snowman(11111111)) == nospaces("       \n _===_ \n (.,.) \n<( : )>\n ( : ) "));
    CHECK(nospaces(snowman(11121111)) == nospaces("       \n _===_ \n (.,o) \n<( : )>\n ( : ) "));
    CHECK(nospaces(snowman(11131111)) == nospaces("       \n _===_ \n (.,O) \n<( : )>\n ( : ) "));
    CHECK(nospaces(snowman(11141111)) == nospaces("       \n _===_ \n (.,-) \n<( : )>\n ( : ) "));
}

/**
 * This Test Case will assert that the function snowman picks the left arm properly.
 * It will test only the left arm options - the fifth digit in the number/
 */
TEST_CASE("Testing the left arm of a snowman") {
    CHECK(nospaces(snowman(11111111)) == nospaces("       \n _===_ \n (.,.) \n<( : )>\n ( : ) "));
    CHECK(nospaces(snowman(11112111)) == nospaces("       \n _===_ \n\\(.,.) \n( : )>\n ( : ) "));
    CHECK(nospaces(snowman(11113111)) == nospaces("       \n _===_ \n (.,.) \n/( : )>\n ( : ) "));
    CHECK(nospaces(snowman(11114111)) == nospaces("       \n _===_ \n (.,.) \n ( : )>\n ( : ) "));
}

/**
 * This Test Case will assert that the function snowman picks the right arm properly.
 * It will test only the right arm options - the sixth digit in the number/
 */
TEST_CASE("Testing the right arm of a snowman") {
    CHECK(nospaces(snowman(11111111)) == nospaces("       \n _===_ \n (.,.) \n<( : )>\n ( : ) "));
    CHECK(nospaces(snowman(11111211)) == nospaces("       \n _===_ \n (.,.)/\n<( : ) \n ( : ) "));
    CHECK(nospaces(snowman(11111311)) == nospaces("       \n _===_ \n (.,.) \n<( : )\\\n ( : ) "));
    CHECK(nospaces(snowman(11111411)) == nospaces("       \n _===_ \n (.,.) \n<( : ) \n ( : ) "));
}

/**
 * This Test Case will assert that the function snowman picks the torso properly.
 * It will test only the torso options - the seventh digit in the number/
 */
TEST_CASE("Testing the torso of a snowman") {
    CHECK(nospaces(snowman(11111111)) == nospaces("       \n _===_ \n (.,.) \n<( : )>\n ( : ) "));
    CHECK(nospaces(snowman(11111121)) == nospaces("       \n _===_ \n (.,.) \n<(] [)>\n ( : ) "));
    CHECK(nospaces(snowman(11111131)) == nospaces("       \n _===_ \n (.,.) \n<(> <)>\n ( : ) "));
    CHECK(nospaces(snowman(11111141)) == nospaces("       \n _===_ \n (.,.) \n<(   )>\n ( : ) "));
}

/**
 * This Test Case will assert that the function snowman picks the base properly.
 * It will test only the base options - the eighth digit in the number/
 */
TEST_CASE("Testing the base of snowman") {
    CHECK(nospaces(snowman(11111111)) == nospaces("       \n _===_ \n (.,.) \n<( : )>\n ( : ) "));
    CHECK(nospaces(snowman(11111112)) == nospaces("       \n _===_ \n (.,.) \n<( : )>\n (\" \") "));
    CHECK(nospaces(snowman(11111113)) == nospaces("       \n _===_ \n (.,.) \n<( : )>\n (___) "));
    CHECK(nospaces(snowman(11111114)) == nospaces("       \n _===_ \n (.,.) \n<( : )>\n (   ) "));
}

TEST_CASE("Some random good snowman code") {
    CHECK(nospaces(snowman(11114411)) == nospaces("       \n _===_ \n (.,.) \n ( : ) \n ( : ) "));
    CHECK(nospaces(snowman(33232124)) == nospaces("   _   \n  /_\\  \n\\(o_O) \n (] [)>\n (   ) "));
    CHECK(nospaces(snowman(12222212)) == nospaces("       \n _===_ \n\\(o.o)/\n ( : ) \n (\" \") "));
    CHECK(nospaces(snowman(32443333)) == nospaces("   _   \n  /_\\  \n (-.-) \n/(> <)\\\n (___) "));
    CHECK(nospaces(snowman(44444432)) == nospaces("  ___  \n (_*_) \n (- -) \n (> <) \n (\" \") "));
    CHECK(nospaces(snowman(44242123)) == nospaces("  ___  \n (_*_) \n\\(o -) \n (] [)>\n (___) "));
    CHECK(nospaces(snowman(41341144)) == nospaces("  ___  \n (_*_) \n (O,-) \n<(   )>\n (   ) "));
    CHECK(nospaces(snowman(11111111)) == nospaces("       \n _===_ \n (.,.) \n<( : )>\n ( : ) "));
    CHECK(nospaces(snowman(22222222)) == nospaces("  ___  \n ..... \n\\(o.o)/\n (] [) \n (\" \") "));
    CHECK(nospaces(snowman(33333333)) == nospaces("   _   \n  /_\\  \n (O_O) \n/(> <)\\\n (___) "));
    CHECK(nospaces(snowman(44444444)) == nospaces("  ___  \n (_*_) \n (- -) \n (   ) \n (   ) "));
}

TEST_CASE("some random bad snowman code") {
    CHECK(nospaces(snowman(11114411)) != nospaces(" _===_ \n (.,.) \n ( : ) \n (] [) "));
    CHECK(nospaces(snowman(33232124)) != nospaces("   _   \n  /_\\  \n\\(0_O) \n (] [)>\n (   ) "));
    CHECK(nospaces(snowman(12222212)) != nospaces("       \n _===_\n\\(o.o)/\n (] [) \n (\" \") "));
    CHECK(nospaces(snowman(32443333)) != nospaces("   _   \n  /_\\  \n (o.-) \n/(> <)\\ \n (___) "));
    CHECK(nospaces(snowman(44444432)) != nospaces("  ___  \n (_*_) \n (- -) \n (> <) \n ( \") "));
    CHECK(nospaces(snowman(44242123)) != nospaces("  ___ \n (_*_) \n\\(o -) \n (] [)>\n (   ) "));
    CHECK(nospaces(snowman(41341144)) != nospaces("  ___  \n (_*_) \n (o, -) \n<(  )>\n (   ) "));
    CHECK(nospaces(snowman(11111111)) != nospaces("      \n _===_ \n (.,-) \n<( : )>\n ( : ) "));
    CHECK(nospaces(snowman(22222222)) != nospaces("  ___  \n .... \n\\(o.o)/\n (] [) \n (\" \") "));
    CHECK(nospaces(snowman(33333333)) != nospaces("   _   \n  /_\\  \n (o_O) \n/(> <)\\\n (___)"));
    CHECK(nospaces(snowman(44444444)) != nospaces("  ___  \n (_*_) \n (o -) \n (  ) \n (___) "));
}



/*
    _   
  / _\  
\(o_ O  ) 
 ( ] [)>
 (   ) 



*/