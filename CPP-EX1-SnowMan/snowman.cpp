/************************************************************************************
 * C++ course, Ariel university.
 * Assignment number 1.
 * 
 * Generating 'snowman' from an 8-digits integer.
 * For the full documentation visit:
 * https://codegolf.stackexchange.com/questions/49671/do-you-want-to-code-a-snowman
 *
 * AUTHORS: Eyal Levi
 * https://github.com/LeviEyal
 * Date: 2021-03
 ***********************************************************************************/

#include <iostream>
#include <vector>
#include <stdexcept>
#include "snowman.hpp"
using namespace std;

/* All snowman body parts: head=0, nose=1, ... , base=7. */
enum  parts { head, nose, leftEye, rightEye, leftArm, rightArm, torso, base };
const int validInputNumber = 8;

const vector<string> H = {"       \n _===_ ", "  ___  \n ..... ", "   _   \n  /_\\  ", "  ___  \n (_*_) "};
const vector<string> N = {",", ".", "_", " "};
const vector<string> L = {".", "o", "O", "-"};
const vector<string> R = {".", "o", "O", "-"};
const vector<string> X1 = {" ", "\\", " ", " "};
const vector<string> X2 = {"<", " ", "/", " "};
const vector<string> Y1 = {" ", "/", " ", " "};
const vector<string> Y2 = {">", " ", "\\", " "};
const vector<string> T = {" : ", "] [", "> <", "   "};
const vector<string> B = {" : ", "\" \"", "___", "   "};

/* 
 * converting char '1'-'5' to its integer representation
 * after that it decrease 1 from the number to fit the arrays range 0-4.
 * Example: input: '1', output: 0 etc. 
 */
int toDigit(char c){
    return (c-'0')-1; 
}

namespace ariel{
    /**
     * @brief The function gets a 8-digits number with each digit range from 1 to 4.
     *        It generates a string representation of a so-called 'snowman',
     *        with each digit of the input number represnt different part of the snowman.
     * 
     * @param num a 8-digits integer with each digit range from 1 to 4
     * @return a string representation of the correspond snowman
     */
	string snowman(int num){
        string n = to_string(num);
        if(n.size() != validInputNumber){
            throw out_of_range{"The input number must be positive and have exacly 8 digits!\n"};
        }

        try{
            /* If some digit is NOT in the range 0-3, then an exception will be thrown. */
            return H.at(toDigit(n[head])) + "\n"
                + X1.at(toDigit(n[leftArm])) + "(" + L.at(toDigit(n[leftEye])) + N.at(toDigit(n[nose]))
                + R.at(toDigit(n[rightEye])) + ")" + Y1.at(toDigit(n[rightArm])) + "\n"
                + X2.at(toDigit(n[leftArm])) + "(" + T.at(toDigit(n[torso])) + ")" + Y2.at(toDigit(n[rightArm])) + "\n"
                + " (" + B.at(toDigit(n[base])) + ") ";  
        }
        catch (const std::exception& ){
            throw out_of_range{"The input number digits must ranged from 1 to 4!\n"};
        }
    }
};