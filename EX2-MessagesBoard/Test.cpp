/************************************************************************************
 * C++ course, Ariel university.
 * Assignment number 2.
 *
 * AUTHORS: Eyal Levi
 * https://github.com/LeviEyal
 * Date: 2021-03
 ***********************************************************************************/

#include "doctest.h"
#include "Board.hpp"
#include <iostream>
#include <ctime>
#include <stdexcept>
#include <string>

using namespace ariel;
using namespace std;

const int MAX_MESSAGE_LENGTH = 100;
const int MAX_ROW = UINT16_MAX;
const int MAX_COL = UINT16_MAX;
const int NUMBER_OF_TESTS = 2000;
const int FIRST_CHAR = 32;
const int LAST_CHAR = 126;


string randomMessage(){
    string ans;
    uint length = rand()%MAX_MESSAGE_LENGTH;
    for(uint i=0; i<length; i++){
        ans += rand()%(LAST_CHAR-FIRST_CHAR+1) + FIRST_CHAR;
    }
    return ans;
}

TEST_CASE("Test 1: Post and then read"){
    Board b;
    srand((unsigned)time(0));

    for (uint i = 0; i < NUMBER_OF_TESTS; i++){
        uint rand_row = rand() % MAX_ROW;
        uint rand_col = rand() % MAX_COL;
        Direction rand_direction = (rand()%2)==1 ? Direction::Horizontal : Direction::Vertical;
        string rand_message = randomMessage();

        CHECK_NOTHROW(b.post(rand_row, rand_col, rand_direction, rand_message));
        CHECK(b.read(rand_row, rand_col, rand_direction, rand_message.size()) == rand_message);
    }
}

TEST_CASE("Test 2: Text overiding 1"){
    Board b;
    b.post(0, 0, Direction::Horizontal, "aaaaaaa");
    CHECK(b.read(0, 0, Direction::Horizontal, 7) == "aaaaaaa");

    b.post(0, 0, Direction::Vertical, "bbbbbb");
    CHECK(b.read(0, 0, Direction::Horizontal, 7) == "baaaaaa");
    b.post(0, 1, Direction::Vertical, "cccccc");
    CHECK(b.read(0, 0, Direction::Horizontal, 7) == "bcaaaaa");
    b.post(0, 2, Direction::Vertical, "dddddd");
    CHECK(b.read(0, 0, Direction::Horizontal, 7) == "bcdaaaa");
    b.post(0, 3, Direction::Vertical, "eeeeee");
    CHECK(b.read(0, 0, Direction::Horizontal, 7) == "bcdeaaa");
    b.post(0, 4, Direction::Vertical, "ffffff");
    CHECK(b.read(0, 0, Direction::Horizontal, 7) == "bcdefaa");
    b.post(0, 5, Direction::Vertical, "gggggg");
    CHECK(b.read(0, 0, Direction::Horizontal, 7) == "bcdefga");
    b.post(0, 6, Direction::Vertical, "hhhhhh");
    CHECK(b.read(0, 0, Direction::Horizontal, 7) == "bcdefgh");
}

TEST_CASE("Test 3: Text overiding 2"){
    Board b;
    b.post(0, 0, Direction::Vertical, "aaaaaaa");
    CHECK(b.read(0, 0, Direction::Vertical, 7) == "aaaaaaa");

    b.post(0, 0, Direction::Horizontal, "bbbbbb");
    CHECK(b.read(0, 0, Direction::Vertical, 7) == "baaaaaa");
    b.post(1, 0, Direction::Horizontal, "cccccc");
    CHECK(b.read(0, 0, Direction::Vertical, 7) == "bcaaaaa");
    b.post(2, 0, Direction::Horizontal, "dddddd");
    CHECK(b.read(0, 0, Direction::Vertical, 7) == "bcdaaaa");
    b.post(3, 0, Direction::Horizontal, "eeeeee");
    CHECK(b.read(0, 0, Direction::Vertical, 7) == "bcdeaaa");
    b.post(4, 0, Direction::Horizontal, "ffffff");
    CHECK(b.read(0, 0, Direction::Vertical, 7) == "bcdefaa");
    b.post(5, 0, Direction::Horizontal, "gggggg");
    CHECK(b.read(0, 0, Direction::Vertical, 7) == "bcdefga");
    b.post(6, 0, Direction::Horizontal, "hhhhhh");
    CHECK(b.read(0, 0, Direction::Vertical, 7) == "bcdefgh");
}

TEST_CASE("Test 4: Read from empty board"){
    Board b;
    srand((unsigned)time(0));

    for (uint i = 0; i < NUMBER_OF_TESTS; i++){
        uint rand_row = rand()%MAX_ROW;
        uint rand_col = rand()%MAX_COL;
        Direction rand_direction = (rand()%2)==1 ? Direction::Horizontal : Direction::Vertical;
        uint rand_length = rand()%MAX_MESSAGE_LENGTH;
        string empty_message(rand_length, '_');

        CHECK(b.read(rand_row, rand_col, rand_direction, rand_length) == empty_message);
    }
}
