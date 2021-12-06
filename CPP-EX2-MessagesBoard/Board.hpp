#include <string>
#include <map>
#include "Direction.hpp"
using namespace std;

struct node{
    char val = '_';
};

namespace ariel {
    class Board {
        uint minRaw, maxRaw;
        uint minCol, maxCol;
        map<uint, map<uint, node> > board;
    public:
        Board() { 
            maxRaw =  maxCol = 0;
            minRaw = minCol = INT8_MAX;
        }
        ~Board() { }
        void post(uint row, uint column, Direction direction, string const &message);
        string read(uint row, uint column, Direction direction, uint length);
        void show();
    };
}