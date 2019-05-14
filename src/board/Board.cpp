#include "Board.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Move.h"


std::istream &operator>>(std::istream &str, Board &data) {
    std::string line;
    Board tmp{};

    std::getline(str, line);
    stringstream(line) >> tmp.height >> tmp.width;
    std::getline(str, line);
    stringstream(line) >> tmp.limit;


    tmp.board = new Field **[tmp.height];
    for (int i = 0; i < tmp.height; ++i) {
        tmp.board[i] = new Field *[tmp.width];
        std::getline(str, line);
        for (int j = 0; j < tmp.width; ++j) {
            if (line[j] == FieldType::VEHICLE) {
                tmp.startY = i;
                tmp.startX = j;
                tmp.board[i][j] = new Field(Position{i, j}, FieldType::CAVITY);
            } else {
                tmp.board[i][j] = new Field(Position{i, j}, (FieldType) line[j]);
            }
        }
    }

    for (int i = 0; i < tmp.height; ++i) {
        for (int j = 0; j < tmp.width; ++j) {
            if (tmp.board[i][j]->type != FieldType::STONE && tmp.board[i][j]->type != FieldType::MINE) {
                for (Movement::Type m: Movement::All) {
                    Field* field = tmp.board[i][j];
                    Field* next;
                    do {
                        next = tmp.get(Movement::move(m, field->position));
                        if((next->type == FieldType::EMPTY || next->type == FieldType::GEM)) field = next;
                        else if (next->type == FieldType::STONE && field != tmp.board[i][j]) tmp.board[i][j]->addMove(Move(m, field));
                        else if (next->type == FieldType::CAVITY) tmp.board[i][j]->addMove(Move(m, next));
                    } while ((next->type == FieldType::EMPTY || next->type == FieldType::GEM));
                }
            }
        }
    }

    data = tmp;
    return str;
}

void Board::print() {
    std::cout << "height: " << this->height << std::endl;
    std::cout << "width: " << this->width << std::endl;
    std::cout << "limit: " << this->limit << std::endl;
    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < this->width; ++j) {
            std::cout << (char) this->board[i][j]->type;
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < this->width; ++j) {
            this->board[i][j]->print();
        }
    }
}

Field* Board::get(Position position) {
    return this->board[position.y][position.x];
}
