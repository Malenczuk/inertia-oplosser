#ifndef DIAMONDSANDMINES_MOVE_H
#define DIAMONDSANDMINES_MOVE_H

struct Position {
    int y, x;
};

namespace Movement
{
    enum Type {
        N = 0,
        NE = 1,
        E = 2,
        SE = 3,
        S = 4,
        SW = 5,
        W = 6,
        NW = 7,
    };

    static const Movement::Type All[] = { N, NE, E, SE, S, SW, W, NW };

    Position move(Type movement, Position position);

}

class Field;
class Move {
public:
    Movement::Type movement;
    Field *dest;

    Move(Movement::Type movement, Field *dest) : movement(movement), dest(dest) {}


};


#endif //DIAMONDSANDMINES_MOVE_H
