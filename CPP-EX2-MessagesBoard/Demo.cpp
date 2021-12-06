/**
 * Demo program for message-board exercise.
 * 
 * Author: Erel Segal-Halevi
 * Since : 2021-03
 */

#include "Board.hpp"
#include "Direction.hpp"
using ariel::Direction;

#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
	ariel::Board board;
	// board.post(/*row=*/0, /*column=*/0, Direction::Horizontal, "");
	// board.post(/*row=*/0, /*column=*/7, Direction::Vertical, "");
	// board.post(/*row=*/2, /*column=*/9, Direction::Horizontal, "");
	// board.post(/*row=*/3, /*column=*/12, Direction::Vertical, "");
	// board.post(/*row=*/5, /*column=*/15, Direction::Horizontal, "");
	// board.post(/*row=*/10, /*column=*/11, Direction::Horizontal, "");
	// board.post(/*row=*/10, /*column=*/16, Direction::Vertical, "");
	// board.post(/*row=*/10, /*column=*/19, Direction::Vertical, "");
	board.post(/*row=*/100+0, /*column=*/100+0, Direction::Horizontal, "Alon");
	board.post(/*row=*/100+0, /*column=*/100+7, Direction::Vertical, "Fireshtein");
	board.post(/*row=*/100+2, /*column=*/100+9, Direction::Horizontal, "is");
	board.post(/*row=*/100+3, /*column=*/100+12, Direction::Vertical, "the");
	board.post(/*row=*/100+5, /*column=*/100+15, Direction::Horizontal, "gayest");
	board.post(/*row=*/100+10, /*column=*/100+11, Direction::Horizontal, "in");
	board.post(/*row=*/100+10, /*column=*/100+16, Direction::Vertical, "the");
	board.post(/*row=*/100+10, /*column=*/100+19, Direction::Vertical, "world!");

	board.show();

	cout << "in 5x0 50 chars: " << board.read(5, 0, Direction::Horizontal ,50) << endl;
	cout << "in 100x100 10 chars: " << board.read(100, 100, Direction::Horizontal ,10) << endl;
	cout << "in 0x19 90 chars: " << board.read(0, 19, Direction::Vertical ,90) << endl;
}

