#include "FieldDoctor.hpp"

using namespace std;
using namespace pandemic;


Player& FieldDoctor::treat(City c){
    if (city != c && !Board::is_connected(city, c)) {
        throw std::invalid_argument{"illegal action: not connected " + city_string(c)};
    }
    if (board[c] == 0) {
        throw std::invalid_argument{"illegal action: no more cubes remain in city " + city_string(c)};
    }
    if (board.is_cure_discoverd(c)) {
        board[c] = 0;
    }
    else {
        board[c]--;
    }
    return *this;
}