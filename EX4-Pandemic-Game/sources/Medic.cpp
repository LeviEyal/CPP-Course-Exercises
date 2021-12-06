#include "Medic.hpp"

using namespace std;
using namespace pandemic;


Player& Medic::treat(City c) {
    if (city != c) {
        throw std::invalid_argument{"illegal action: you are not in city " + city_string(c)};
    }
    if (board[c] == 0) {
        throw std::invalid_argument{"illegal action: no more cubes remain in city " + city_string(c)};
    }

    board[c] = 0;
    return *this;
}

void Medic::arrive() {
    if(board.is_cure_discoverd(city)) {
        board[city] = 0;
    }
}