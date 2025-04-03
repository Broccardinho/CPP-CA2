//
// Created by AGBro on 31/03/2025.
//

#ifndef CRAWLER_H
#define CRAWLER_H

#include "Position.h"
#include "Direction.h"
#include <list>
#include <string>

using namespace std;

class Crawler {
private:
    int id;
    Position position;
    Direction direction;
    int size;
    bool alive;
    list<Position> path;

public:
    Crawler(int id, Position pos, Direction dir, int size);

    // Movement functions
    void move();
    bool isWayBlocked() const;

    // Getter functions
    int getId() const { return id; }
    Position getPosition() const { return position; }
    Direction getDirection() const { return direction; }
    int getSize() const { return size; }
    bool isAlive() const { return alive; }
    list<Position> getPath() const { return path; }

    // Setter functions
    void setAlive(bool status) { alive = status; }
    void setDirection(Direction dir) { direction = dir; }
    void setPosition(Position pos) { position = pos; }
    void grow(int amount) { size += amount; }

    // Utility functions
    string directionToString() const;
    string getType() const { return "Crawler"; }  // Specific to Crawler
    string typeToString() const { return "Crawler"; }
};

#endif // CRAWLER_H