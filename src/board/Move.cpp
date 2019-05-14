#include "Move.h"

Position Movement::move(Movement::Type movement, Position position) {
    switch (movement) {
        case N:
            return Position{position.y-1, position.x};
        case NE:
            return Position{position.y-1, position.x+1};
        case E:
            return Position{position.y, position.x+1};
        case SE:
            return Position{position.y+1, position.x+1};
        case S:
            return Position{position.y+1, position.x};
        case SW:
            return Position{position.y+1, position.x-1};
        case W:
            return Position{position.y, position.x-1};
        case NW:
            return Position{position.y-1, position.x-1};
    }
}