//
// Created by AGBro on 31/03/2025.
//

#ifndef POSITION_H
#define POSITION_H

struct Position {
    int x;
    int y;

    bool operator<(const Position& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

#endif //POSITION_H
