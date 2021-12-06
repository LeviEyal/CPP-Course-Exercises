#include "Scientist.hpp"

using namespace std;
using namespace pandemic;

Player& Scientist::discover_cure(Color c) {
    if(!board.is_research_station(city)){
        throw std::invalid_argument{"illegal action: city "+city_string(city)+" has no research station!"};
    }
    int count = 0;
    for(const auto& t : cards){
        if(Board::color_of(t) == c) {
            count++;
        }
    }
    if(count < n){
        throw std::invalid_argument{"illegal action: you only have "+std::to_string(count)+" "+ color_string(c) + " cards remaining " };
    }
    count = 1;
    for(auto it = cards.begin(); it != cards.end(); count++){
        if(count == n) { break; }
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