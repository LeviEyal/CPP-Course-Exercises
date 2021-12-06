#pragma once
#include "City.hpp"
#include "Color.hpp"
#include <map>
#include <set>
#include <iostream>

namespace pandemic {

    class Board {

        static std::map<City, std::set<City>> connections;
        std::map<City, int> diseas_cubes;
        std::set<Color> cure_discoverd;
        std::set<City> research_stations;

        public:
            Board() {}
            int& operator[](City c);
            bool is_clean();
            void build_research_station(City c);
            bool is_research_station(City c);
            void mark_cured(Color c);
            bool is_cure_discoverd(City c);
            void remove_cures();
            
            static bool is_connected(City& c1, City& c2);
            static Color color_of(City c);
            friend std::ostream& operator<<(std::ostream& out, const Board& b);
    };
}
