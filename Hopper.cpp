#include "Hopper.h"
#include <ctime>
using namespace std;

Hopper::Hopper(int id, Position pos, Direction dir, int size, int hopLength)
    : Bug(id, pos, dir, size), hopLength(hopLength) {
    srand(static_cast<unsigned>(time(NULL)));
}

void Hopper::move() {
    if (!alive) return;

    Position newPos = position;
    int remainingHop = hopLength;

    while (isWayBlocked()) {
        direction = static_cast<Direction>(rand() % 4);
    }

    while (remainingHop > 0 && !isWayBlocked()) {
        switch (direction) {
            case Direction::NORTH: newPos.y--;break;
            case Direction::EAST: newPos.x++;break;
            case Direction::SOUTH: newPos.y++;break;
            case Direction::WEST: newPos.x--;break;
        }
        remainingHop--;
    }

    if(newPos != position) {
        position = newPos;
        addToPath(newPos);
    }
}

string Hopper::getType() const {
    return "Hopper";
}