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

    if (position.y == 0 && direction != Direction::EAST) {
        direction = Direction::EAST;
    } else if (position.y == 9 && direction != Direction::SOUTH) {
        direction = Direction::SOUTH;
    } else if (position.y == 9 && direction != Direction::WEST) {
        direction = Direction::WEST;
    } else if (position.y == 0 && direction != Direction::NORTH) {
        direction = Direction::NORTH;
    }
    Position newPos = position;

    switch (direction) {
        case Direction::EAST:
            newPos.x++;
            if (newPos.x > 9) {
                newPos.x = 9;
                direction = Direction::SOUTH;
                newPos.y++;
            }
            break;

        case Direction::SOUTH:
            newPos.y++;
            if (newPos.y > 9) {
                newPos.y = 9;
                direction = Direction::WEST;
                newPos.x--;
            }
            break;

        case Direction::WEST:
            newPos.x--;
            if (newPos.x < 0) {
                newPos.x = 0;
                direction = Direction::NORTH;
                newPos.y--;
            }
            break;

        case Direction::NORTH:
            newPos.y--;
            if (newPos.y < 0) {
                newPos.y = 0;
                direction = Direction::EAST;
                newPos.x++;
            }
            break;
    }

    newPos.x = clamp(newPos.x, 0, 9);
    newPos.y = clamp(newPos.y, 0, 9);

    position = newPos;
    addToPath(position);
}

string WallHugger::getType() const {
    return "WallHugger";
}
