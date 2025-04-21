#include "Hopper.h"
#include <cstdlib>

using namespace std;

Hopper::Hopper(int id, Position pos, Direction dir, int size, int hopLength)
    : Bug(id, pos, dir, size), hopLength(hopLength) {
    if (hopLength <= 0) {
        hopLength = 1;
    }
    if (pos.x < 0 || pos.x > 9 || pos.y < 0 || pos.y > 9) {
        position.x = 0;
        position.y = 0;
    }
}

void Hopper::move() {
    if (!alive) return;

    int randDir = rand() % 4;
    Direction newDir;
    switch (randDir) {
        case 0: newDir = Direction::NORTH; break;
        case 1: newDir = Direction::EAST;  break;
        case 2: newDir = Direction::SOUTH; break;
        case 3: newDir = Direction::WEST;  break;
    }
    direction = newDir;

    Position newPos = position;
    int hopsLeft = hopLength;

    while (hopsLeft > 0) {
        Position nextPos = newPos;
        switch (direction) {
            case Direction::NORTH: nextPos.y--; break;
            case Direction::EAST:  nextPos.x++; break;
            case Direction::SOUTH: nextPos.y++; break;
            case Direction::WEST:  nextPos.x--; break;
        }
        if (nextPos.x < 0 || nextPos.x > 9 || nextPos.y < 0 || nextPos.y > 9) {
            break;
        }
        newPos = nextPos;
        hopsLeft--;
    }

    position = newPos;
    addToPath(position);
}

string Hopper::getType() const {
    return "Hopper";
}