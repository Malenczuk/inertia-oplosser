#ifndef DIAMONDSANDMINES_BOARD_H
#define DIAMONDSANDMINES_BOARD_H

#include <string>
#include "Field.h"

class Board {
public:
    int height, width;
    int limit;
    Position start;
    Field ***board;
    std::vector<Field *> gems;

    Board() = default;

    friend std::istream &operator>>(std::istream &str, Board &data);

    Field *get(Position position);

    void print();

private:
    void generateAllEdges();

    void generateEdges(Field *s);
};

#endif //DIAMONDSANDMINES_BOARD_H
