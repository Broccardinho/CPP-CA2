//
// Created by AGBro on 31/03/2025.
//

#ifndef BUG_H
#define BUG_H

#include "Position.h"
#include "Direction.h"
#include "BugType.h"
#include <list>
#include <string>

using namespace std;

class Bug {
    protected:
    int id;
    Position position;
    Direction direction;
    int size;
    bool alive;
    list<Position> path;
    BugType type;

    public:
    Bug(int id, Position pos, Direction dir, int size, BugType bT);

    void move();
    bool isWayBlocked()const;

    int getId()const {
        return id;
    }
    Position getPosition()const {
        return position;
    }
    Direction getDirection()const {
        return direction;
    }
    int getSize()const {
        return size;
    }
    bool isAlive()const {
        return alive;
    }
    list<Position> getPositions()const{
        return path;
    }
    BugType getType()const {
        return type;
    }

    void setAlive(bool status) {
        alive = status;
    }
    void setDirection(Direction dir) {
        direction = dir;
    }
    void setPosition(Position pos) {
        position = pos;
    }
    void grow(int amount) {
        size += amount;
    }

    string directionToString()const;
    string typeToString()const;
};

#endif //BUG_H