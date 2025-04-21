#include "Crawler.h"
#include <cstdlib>

using namespace std;

Crawler::Crawler(int id, Position pos, Direction dir, int size)
    : Bug(id, pos, dir, size) {
    if (pos.x < 0 || pos.x > 9 || pos.y < 0 || pos.y > 9) {
        position.x = 0;
        position.y = 0;
    }
}

void Crawler::move() {
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
    switch (direction) {
        case Direction::NORTH: newPos.y--; break;
        case Direction::EAST:  newPos.x++; break;
        case Direction::SOUTH: newPos.y++; break;
        case Direction::WEST:  newPos.x--; break;
    }

    if (newPos.x >= 0 && newPos.x <= 9 && newPos.y >= 0 && newPos.y <= 9) {
        position = newPos;
        addToPath(newPos);
    }
}

string Crawler::getType() const {
    return "Crawler";
}