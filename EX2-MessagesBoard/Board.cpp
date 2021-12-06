/************************************************************************************
 * C++ course, Ariel university.
 * Assignment number 2.
 *
 * AUTHORS: Eyal Levi
 * https://github.com/LeviEyal
 * Date: 2021-03
 ***********************************************************************************/

#include <iostream>
#include "Board.hpp"
using namespace std;

namespace ariel {
    /**
     * @brief Post a message on the board on a given position.
     * 
     * @param row       The row number of the position
     * @param column    The column number of the position
     * @param direction The direction - wheter Horizontal of Vertical
     * @param message   The message as a string
     */
    void Board::post(uint row, uint column, Direction direction, string const &message) {
        this->maxRaw = max(this->maxRaw, row);
        this->maxCol = max(this->maxCol, column);
        this->minRaw = min(this->minRaw, row);
        this->minCol = min(this->minCol, column);
        for(char ch: message){
            this->board[row][column].val = ch;
            (direction == Direction::Horizontal)? column++ : row++;
        }
    }
//----------------------------------------------------------------------------------------------
    /**
     * @brief Read a message from the messages board from a given position
     * 
     * @param row       The row number of the position
     * @param column    The column number of the position
     * @param direction The direction - wheter Horizontal of Vertical
     * @param length    The length of the message to read from the board
     * @return string   The string that the method read
     */
    string Board::read(uint row, uint column, Direction direction, uint length) {
        string ans;
        for(uint i=0; i<length; i++){
            ans += this->board[row][column].val;
            (direction == Direction::Horizontal)? column++ : row++;
        }
        return ans;
    }
//----------------------------------------------------------------------------------------------
    /**
     * @brief Draw the board with all the posted messages on.
     */
    void Board::show() {
        for (uint i = this->minRaw; i <= this->maxRaw; i++) {
            for (uint j = this->minCol; j <= this->maxCol; j++) {
                cout << this->board[i][j].val << " ";
            }
            cout << "\n\n";
        }
    }
}
