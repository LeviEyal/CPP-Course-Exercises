/************************************************************************************
 * C++ course, Ariel university.
 * Assignment number 2 - Main program.
 *
 * AUTHORS: Eyal Levi
 * https://github.com/LeviEyal
 * Date: 2021-03
 ***********************************************************************************/

#include <iostream>
#include <stdexcept>
#include <ctime>
#include <thread>
#include <chrono>
#include "Direction.hpp"
#include "Board.hpp"
using namespace std;
using ariel::Direction;

const string red_line = "\e[1;31m";
const string colors[] {"\e[1;92m", "\e[1;93m", "\e[1;94m", "\e[1;95m", "\e[1;96m"};


int main() {
    srand((unsigned)time(0));
    ariel::Board b;
    string message;
    uint x, y, d, l;
    for(int i=0; true; i++){
        system("clear");
        cout << colors[i%5];
        b.show();
        cout << red_line << "-----------------------------" << flush;
        this_thread::sleep_for(chrono::milliseconds(600));

        uint option;
        cout << "\nDo tou want to post a message(op 1) or read a message(op 2)?\n";
        cin >> option;
        if(option == 1){
            cout << "\nEnter row col direction(1 or 2) and the message\n";
            cin >> x >> y >> d >> message;
            if(d==1){
                b.post(/*row=*/x, /*column=*/y, Direction::Vertical, message);
            }
            else{
                b.post(/*row=*/x, /*column=*/y, Direction::Horizontal, message);
            }
        }
        else {
            cout << "\nEnter row col direction(1 or 2) and the length\n";
            cin >> x >> y >> d >> l;
            cout << "\nThe message is:\n";
            if(d==1){
                cout << b.read(/*row=*/x, /*column=*/y, Direction::Vertical, l) << endl;
            }
            else{
                cout << b.read(/*row=*/x, /*column=*/y, Direction::Horizontal, l) << endl;
            }
            cout << "enter something to continue" << endl;
            cin >> x;
        }
    }
}