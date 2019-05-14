#ifndef DIAMONDSANDMINES_BOARD_H
#define DIAMONDSANDMINES_BOARD_H

#include <string>
#include "Field.h"

using namespace std;


class Board {
public:
    int height, width;
    int limit;
    int startY, startX;
    Field ***board;

    Board() = default;

    friend std::istream& operator>>(std::istream& str, Board& data);

    Field* get(Position position);

    void print();
};

#endif //DIAMONDSANDMINES_BOARD_H
