#include "Researcher.hpp"

using namespace std;
using namespace pandemic;
const int cards_to_discard = 5;

Player& Researcher::discover_cure(Color c){
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
