#include "Bug.h"
#include <cstdlib>
#include <ctime>

Bug::Bug(int id, Position pos, Direction dir, int size)
    : id(id), position(pos), direction(dir), size(size), alive(true) {
    path.push_back(pos);
}

bool Bug::isWayBlocked() const {
    switch (direction) {
        case Direction::NORTH: return position.y == 0;
        case Direction::EAST:  return position.x == 9;
        case Direction::SOUTH: return position.y == 9;
        case Direction::WEST:  return position.x == 0;
        default: return false;
    }
}

void Bug::addToPath(Position newPos) {
    path.push_back(newPos);
}

Position Bug::getLatestPosition() const {
    return path.back();
}

string Bug::directionToString() const {
    switch (direction) {
        case Direction::NORTH: return "North";
        case Direction::EAST:  return "East";
        case Direction::SOUTH: return "South";
        case Direction::WEST:  return "West";
        default: return "Unknown";
    }
}