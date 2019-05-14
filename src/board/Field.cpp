#include "Field.h"
#include <iostream>

void Field::addMove(Move move) {
    this->moves.insert(this->moves.begin(), move);
}

void Field::print() {
    if(!this->moves.empty()){
        std::cout << (char) this->type << " {" << this->position.y << " " << this->position.x << "}:";
        for (Move move: this->moves) {
            std::cout << " " << move.movement << "(" << (char) move.dest->type << "{" << move.dest->position.y << " " << move.dest->position.x << "})";
        }
        std::cout << std::endl;
    }
}
