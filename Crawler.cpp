#include "Crawler.h"
#include <cstdlib>
#include <ctime>
using namespace std;

Crawler::Crawler(int id, Position pos, Direction dir, int size)
    : Bug(id, pos, dir, size) {
    srand(static_cast<unsigned>(time(nullptr)));
}

void Crawler::move() {
    if (!alive) return;

    while (isWayBlocked()) {
        direction = static_cast<Direction>((rand() % 4) + 1);
    }

    Position newPos = position;
    switch (direction) {
        case Direction::NORTH: newPos.y--; break;
        case Direction::EAST:  newPos.x++; break;
        case Direction::SOUTH: newPos.y++; break;
        case Direction::WEST:  newPos.x--; break;
    }

    position = newPos;
    addToPath(newPos);
}

string Crawler::getType() const {
    return "Crawler";
}