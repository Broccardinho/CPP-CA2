//
// Created by AGBro on 15/04/2025.
//

#ifndef HOPPER_H
#define HOPPER_H

#include "Bug.h"
#include <string>

class Hopper : public Bug {
private:
    int hopLength;
public:
    Hopper(int id, Position pos, Direction dir, int size, int hopLength);
    void move() override;
    std::string getType() const override;
    int getHopLength() const { return hopLength; }
};

#endif