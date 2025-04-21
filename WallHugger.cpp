//
// Created by AGBro on 16/04/2025.
//

#include "WallHugger.h"
#include <algorithm>

using namespace std;

WallHugger::WallHugger(int id, Position pos, Direction dir, int size)
    : Bug(id, pos, dir, size) {
}

void WallHugger::move() {
    if (!alive) return;

    Position newPos = position;

    switch (direction) {
        case Direction::NORTH: newPos.y--; break;
        case Direction::EAST:  newPos.x++; break;
        case Direction::SOUTH: newPos.y++; break;
        case Direction::WEST:  newPos.x--; break;
    }

    if (newPos.x < 0 || newPos.x > 9 || newPos.y < 0 || newPos.y > 9) {
        if (rand() % 5 == 0) {
            switch (direction) {
                case Direction::NORTH: direction = Direction::SOUTH; break;
                case Direction::EAST:  direction = Direction::WEST;  break;
                case Direction::SOUTH: direction = Direction::NORTH; break;
                case Direction::WEST:  direction = Direction::EAST;  break;
            }
        } else {
            switch (direction) {
                case Direction::NORTH: direction = Direction::EAST;  break;
                case Direction::EAST:  direction = Direction::SOUTH; break;
                case Direction::SOUTH: direction = Direction::WEST;  break;
                case Direction::WEST:  direction = Direction::NORTH; break;
            }
        }

        newPos = position;
        switch (direction) {
            case Direction::NORTH: newPos.y--; break;
            case Direction::EAST:  newPos.x++; break;
            case Direction::SOUTH: newPos.y++; break;
            case Direction::WEST:  newPos.x--; break;
        }
    }

    newPos.x = max(0, min(9, newPos.x));
    newPos.y = max(0, min(9, newPos.y));

    position = newPos;
    addToPath(position);
}

string WallHugger::getType() const {
    return "WallHugger";
}
