#ifndef DIAMONDSANDMINES_FIELD_H
#define DIAMONDSANDMINES_FIELD_H

#include <vector>
#include "Move.h"

enum FieldType {
    STONE = '#',
    GEM = '+',
    MINE = '*',
    CAVITY = 'O',
    VEHICLE = '.',
    EMPTY = ' '
};


class Field {
public:
    Position position;
    FieldType type;
    std::vector<Move> moves;

    Field(Position position, FieldType type): position(position), type(type) {};

    void addMove(Move move);

    void print();
};


#endif //DIAMONDSANDMINES_FIELD_H
