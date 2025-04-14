#ifndef BUG_H
#define BUG_H

#include "Position.h"
#include "Direction.h"
#include <list>
#include <string>
#include <memory>
using namespace std;

class Bug {
protected:
    int id;
    Position position;
    Direction direction;
    int size;
    bool alive;
    list<Position> path;

public:
    Bug(int id, Position pos, Direction dir, int size);
    virtual ~Bug() = default;

    virtual void move() = 0;
    virtual string getType() const = 0;

    bool isWayBlocked() const;
    void addToPath(Position newPos);
    Position getLatestPosition() const;
    string directionToString() const;

    int getId() const {return id;}
    Position getPosition() const {return position;}
    Direction getDirection() const {return direction;}
    int getSize() const {return size;}
    bool isAlive() const {return alive;}
    const list<Position>& getPath() const {return path;}

    void setAlive(bool status) {alive = status;}
    void setDirection(Direction dir) {direction = dir;}
    void setPosition(Position pos) {position = pos;}
    void grow(int amount) {size += amount;}
};

#endif