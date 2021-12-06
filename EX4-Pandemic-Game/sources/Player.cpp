#include "Player.hpp"

using namespace std;
using namespace pandemic;
const int cards_to_discard = 5;
//------------------------------------------------------------------------------------------------------------------------------------------
Player& Player::take_card(City c){
    cards.insert(c);
    return *this;
}
//------------------------------------------------------------------------------------------------------------------------------------------
Player& Player::drive(City c){
    if(city == c){
        throw std::invalid_argument{"Illegal action: you already in " + city_string(c)};
    }
    if(!Board::is_connected(city, c)){
        throw std::invalid_argument{"Illegal action: " + city_string(city) + " is not connected to " + city_string(c)};
    }
    city = c;
    arrive();
    return *this;
}
//------------------------------------------------------------------------------------------------------------------------------------------
Player& Player::fly_direct(City c){
    if(city == c){
        throw std::invalid_argument{"Illegal action: you already in " + city_string(c)};
    }
    if(!cards.contains(c)){
        throw std::invalid_argument{"Illegal action: you do not have the card of " + city_string(c)};
    }
    cards.erase(c);
    city = c;
    arrive();
    return *this;
}
//------------------------------------------------------------------------------------------------------------------------------------------
Player& Player::fly_charter(City c){
    if(city == c){
        throw std::invalid_argument{"Illegal action: you already in " + city_string(c)};
    }
    if(!cards.contains(city)){
        throw std::invalid_argument{"Illegal action: you do not have the card of " + city_string(city)};
    }
    cards.erase(city);
    city = c;
    arrive();
    return *this;
}
//------------------------------------------------------------------------------------------------------------------------------------------
Player& Player::fly_shuttle(City c){
    if(city == c){
        throw std::invalid_argument{"Illegal action: you already in " + city_string(c)};
    }
    if(!board.is_research_station(city) || !board.is_research_station(c)){
        throw std::invalid_argument{"Illegal action: " + city_string(city) + " and " + city_string(c) + " must both have research station."};
    }
    city = c;
    arrive();
    return *this;
}
//------------------------------------------------------------------------------------------------------------------------------------------
Player& Player::build(){
    if(!cards.contains(city)){
        throw std::invalid_argument{"Cant build research station! the player dont have a " + city_string(city) + " card"};
    }
    board.build_research_station(city);
    cards.erase(city);
    return *this;
}
//------------------------------------------------------------------------------------------------------------------------------------------
Player& Player::discover_cure(Color c){
    if(!board.is_research_station(city)){
        throw std::invalid_argument{"illegal action: city "+city_string(city)+" has no research station!"};
    }
    int count = 0;
    for(const auto& t : cards){
        if(Board::color_of(t) == c) {
            count++;
        }
    }
    if(count < cards_to_discard){
        throw std::invalid_argument{"illegal action: you only have "+std::to_string(count)+" "+ color_string(c) + " cards remaining " };
    }
    count = 1;
    for(auto it = cards.begin(); it != cards.end(); count++){
        if(count == cards_to_discard) { break; }
        if(Board::color_of(*it) == c) {
            it = cards.erase(it);
        }
        else {
            ++it;
        }
    }
    board.mark_cured(c);
    return *this;
}
//------------------------------------------------------------------------------------------------------------------------------------------
Player& Player::treat(City c){
    if (city != c) {
        throw std::invalid_argument{"illegal action: you are not in city " + city_string(c)};
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