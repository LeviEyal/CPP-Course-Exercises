#include "Dispatcher.hpp"

using namespace std;
using namespace pandemic;

Player& Dispatcher::fly_direct(City c){
    if(city == c){
        throw std::invalid_argument{"Illegal action: you already in " + city_string(c)};
    }
    if(board.is_research_station(city)) {
        city = c;
    }
    else {
        return Player::fly_direct(c);
    }
    return *this;
}