//
// Created by AGBro on 31/03/2025.
//

#ifndef POSITION_H
#define POSITION_H

#endif //POSITION_H

struct Position {
    int x;
    int y;

    Position(int x, int y) : x(x), y(y) {}

    bool operator<(const Position& other) const {
        return (x < other.x) || (x == other.x && y < other.y);
    }

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }

};
