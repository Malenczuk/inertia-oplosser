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
    std::stringstream(line) >> tmp.height >> tmp.width;
    std::getline(str, line);
    std::stringstream(line) >> tmp.limit;


    tmp.board = new Field **[tmp.height];
    for (int i = 0; i < tmp.height; ++i) {
        tmp.board[i] = new Field *[tmp.width];
        std::getline(str, line);
        for (int j = 0; j < tmp.width; ++j) {
            if (line[j] == FieldType::VEHICLE) {
                tmp.start = Position{i, j};
                tmp.board[i][j] = new Field(Position{i, j}, FieldType::CAVITY);
            } else {
                tmp.board[i][j] = new Field(Position{i, j}, (FieldType) line[j]);
                if (line[j] == FieldType::GEM) tmp.gems.insert(tmp.gems.begin(), tmp.board[i][j]);
            }
        }
    }
//    tmp.generateAllEdges();
    tmp.generateEdges(tmp.get(tmp.start));

    data = tmp;
    return str;
}

void Board::print() {
    std::cout << "height: " << this->height << std::endl;
    std::cout << "width: " << this->width << std::endl;
    std::cout << "limit: " << this->limit << std::endl;
    std::cout << "vehicle: {" << start.y << " " << start.x << "}" << std::endl;
    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < this->width; ++j) {
            if (start.y == i && start.x == j) std::cout << (char) FieldType::VEHICLE;
            else std::cout << (char) this->board[i][j]->type;
        }
        std::cout << std::endl;
    }
    std::cout << "Gems: " << std::endl;
    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < this->width; ++j) {
            Field *f = this->board[i][j];
            if (f->type == FieldType::GEM) {
                std::cout << "+ {" << f->position.y << " " << f->position.x << "}:";
                for (Move m: f->gemMoves)
                    std::cout << " " << m.movement << "({" << m.src->position.y << " " << m.src->position.x << "} {" << m.dst->position.y << " " << m.dst->position.x << "})";
                std::cout << std::endl;
            }
        }
    }
    std::cout << "Graph: " << std::endl;
    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < this->width; ++j) {
            this->board[i][j]->print();
        }
    }
}

Field *Board::get(Position position) {
    return this->board[position.y][position.x];
}

void Board::generateAllEdges() {
    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < this->width; ++j) {
            if (this->board[i][j]->type != FieldType::STONE && this->board[i][j]->type != FieldType::MINE) {
                for (Movement::Type m: Movement::All) {
                    Field *field = this->board[i][j];
                    Field *next;
                    do {
                        next = this->get(Movement::move(m, field->position));
                        if ((next->type == FieldType::EMPTY || next->type == FieldType::GEM)) field = next;
                        else if (next->type == FieldType::STONE && field != this->board[i][j])
                            this->board[i][j]->addMove(Move(m, this->board[i][j], field));
                        else if (next->type == FieldType::CAVITY) this->board[i][j]->addMove(Move(m, this->board[i][j], next));
                    } while ((next->type == FieldType::EMPTY || next->type == FieldType::GEM));
                }
            }
        }
    }
}

void Board::generateEdges(Field *s) {
    for (Movement::Type m: Movement::All) {
        std::vector<Field *> gemFields;
        Field *field = s;
        Field *next;
        do {
            next = this->get(Movement::move(m, field->position));
            switch (next->type) {
                case STONE:
                    if (field != s) {
                        for (Field *g: gemFields) g->gemMoves.insert(g->gemMoves.begin(), Move(m, s, field));
                        s->addMove(Move(m, s, field));
                        if (field->moves.empty()) this->generateEdges(field);
                    }
                    break;
                case CAVITY:
                    for (Field *g: gemFields) g->gemMoves.insert(g->gemMoves.begin(), Move(m, s, next));
                    s->addMove(Move(m, s, next));
                    if (next->moves.empty()) this->generateEdges(next);
                    break;
                case GEM:
                    gemFields.insert(gemFields.begin(), next);
                case EMPTY:
                    field = next;
                default:
                    break;
            }
        } while ((next->type == FieldType::EMPTY || next->type == FieldType::GEM));
    }
}
