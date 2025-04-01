//
// Created by AGBro on 31/03/2025.
//

#include "Bug.h"
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

Bug::Bug(int id, Position pos, Direction dir, int size, BugType bT):
        id(id), position(pos), direction(dir), size(size), alive(true), type(bT) {
    path.push_back(pos);
}

bool Bug::isWayBlocked() const {
    switch (direction) {
        case Direction::NORTH: return position.y == 0;
        case Direction::EAST: return position.x == 9;
        case Direction::SOUTH: return position.y == 9;
        case Direction::WEST: return position.x == 0;
        default:return false;
    }
}

string Bug::directionToString() const {
    switch (direction) {
        case Direction::NORTH: return "NORTH";
        case Direction::EAST: return "EAST";
        case Direction::SOUTH: return "SOUTH";
        case Direction::WEST: return "WEST";
        default: return "UNKNOWN";
    }
}

string Bug::typeToString() const {
    switch (type) {
        case BugType::CRAWLER: return "CRAWLER";
        default: return "UNKNOWN";
    }
}

void Bug::move() {
    if (!alive) return;

    switch (type) {
        case BugType::CRAWLER:
            while (isWayBlocked()) {
                direction = static_cast<Direction>((rand() % 4)+1);
            }
        Position newPos = position;
        switch (direction) {
            case Direction::NORTH: newPos.y--; break;
            case Direction::EAST: newPos.x++; break;
            case Direction::SOUTH: newPos.y++; break;
            case Direction::WEST: newPos.x--; break;
        }
        position = newPos;
        path.push_back(newPos);
        break;
    }
}
