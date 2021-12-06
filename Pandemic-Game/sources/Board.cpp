#include "Board.hpp"

using namespace std;
using namespace pandemic;

int& Board::operator[](City c) {
    return diseas_cubes[c];
}

bool Board::is_clean() {
    for(auto& pair: diseas_cubes) {
        if(pair.second > 0) {
            return false;
        }
    }
    return true;
}

bool Board::is_connected(City& c1, City& c2) {
    return connections.at(c1).contains(c2);
}

void Board::build_research_station(City c) {
    research_stations.insert(c);
}

bool Board::is_research_station(City c) {
    return research_stations.contains(c);
}

void Board::mark_cured(Color c) {
    cure_discoverd.insert(c);
}

bool Board::is_cure_discoverd(City c) {
    return (bool)cure_discoverd.count(color_of(c));
}

void Board::remove_cures() {
    cure_discoverd.clear();
}

Color Board::color_of(City c) {
    return cities_colors.at(c);
}

std::ostream& pandemic::operator<<(std::ostream& out, const Board& b) {
    const std::string LINE = "\e[1;95m";
    const std::string HEADLINE = "\e[1;93m";
    const std::string FIELDS = "\e[1;96m";
    const std::string REGULAR = "\e[0m";
    out << LINE << "-------------------------- BOARD --------------------------" << std::endl;
    out << HEADLINE << "level of disease:" << FIELDS << std::endl;
    for(const auto& e: b.diseas_cubes) {
        out << "\t" << city_string(e.first) << ": \t\t" << e.second << std::endl;
    }
    out << HEADLINE << "Cure discovered for colors:" << FIELDS << std::endl;
    for(const auto& c: b.cure_discoverd) {
        out << "\t" << color_string(c) << std::endl;
    }
    out << HEADLINE << "Research stations:" << FIELDS << std::endl;
    for(const auto& rs: b.research_stations) {
        out << "\t" << city_string(rs) << std::endl;
    }
    out << LINE << "------------------------ END BOARD ------------------------" << REGULAR << std::endl;
    return out;
}

std::map<City, std::set<City>> Board::connections {
    { Algiers, {Madrid, Paris, Istanbul, Cairo } },
    { Atlanta, {Chicago, Miami, Washington } },
    { Baghdad, {Tehran, Istanbul, Cairo, Riyadh, Karachi } },
    { Bangkok, {Kolkata, Chennai, Jakarta, HoChiMinhCity, HongKong } },
    { Beijing, {Shanghai, Seoul } },
    { Bogota, {MexicoCity, Lima, Miami, SaoPaulo, BuenosAires } },
    { BuenosAires, {Bogota, SaoPaulo } },
    { Cairo, {Algiers, Istanbul, Baghdad, Khartoum, Riyadh } },
    { Chennai, {Mumbai, Delhi, Kolkata, Bangkok, Jakarta } },
    { Chicago, {SanFrancisco, LosAngeles, MexicoCity, Atlanta, Montreal } },
    { Delhi, {Tehran, Karachi, Mumbai, Chennai, Kolkata } },
    { Essen, {London, Paris, Milan, StPetersburg } },
    { HoChiMinhCity, {Jakarta, Bangkok, HongKong, Manila } },
    { HongKong, {Bangkok, Kolkata, HoChiMinhCity, Shanghai, Manila, Taipei } },
    { Istanbul, {Milan, Algiers, StPetersburg, Cairo, Baghdad, Moscow } },
    { Jakarta, {Chennai, Bangkok, HoChiMinhCity, Sydney } },
    { Johannesburg, {Kinshasa, Khartoum } },
    { Karachi, {Tehran, Baghdad, Riyadh, Mumbai, Delhi } },
    { Khartoum, {Cairo, Lagos, Kinshasa, Johannesburg } },
    { Kinshasa, {Lagos, Khartoum, Johannesburg } },
    { Kolkata, {Delhi, Chennai, Bangkok, HongKong } },
    { Lagos, {SaoPaulo, Khartoum, Kinshasa } },
    { Lima, {MexicoCity, Bogota, Santiago } },
    { London, {NewYork, Madrid, Essen, Paris } },
    { LosAngeles, {SanFrancisco, Chicago, MexicoCity, Sydney } },
    { Madrid, {London, NewYork, Paris, SaoPaulo, Algiers } },
    { Manila, {Taipei, SanFrancisco, HoChiMinhCity, Sydney, HongKong } },
    { MexicoCity, {LosAngeles, Chicago, Miami, Lima, Bogota } },
    { Miami, {Atlanta, MexicoCity, Washington, Bogota } },
    { Milan, {Essen, Paris, Istanbul } },
    { Montreal, {Chicago, Washington, NewYork } },
    { Moscow, {StPetersburg, Istanbul, Tehran } },
    { Mumbai, {Karachi, Delhi, Chennai } },
    { NewYork, {Montreal, Washington, London, Madrid } },
    { Osaka, {Taipei, Tokyo } },
    { Paris, {Algiers, Essen, Madrid, Milan, London } },
    { Riyadh, {Baghdad, Cairo, Karachi } },
    { SanFrancisco, {LosAngeles, Chicago, Tokyo, Manila } },
    { Santiago, {Lima } },
    { SaoPaulo, {Bogota, BuenosAires, Lagos, Madrid } },
    { Seoul, {Beijing, Shanghai, Tokyo } },
    { Shanghai, {Beijing, HongKong, Taipei, Seoul, Tokyo } },
    { StPetersburg, {Essen, Istanbul, Moscow } },
    { Sydney, {Jakarta, Manila, LosAngeles } },
    { Taipei, {Shanghai, HongKong, Osaka, Manila } },
    { Tehran, {Baghdad, Moscow, Karachi, Delhi } },
    { Tokyo, {Seoul, Shanghai, Osaka, SanFrancisco } },
    { Washington, {Atlanta, NewYork, Montreal, Miami } }
};