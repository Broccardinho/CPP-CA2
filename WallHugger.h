//
// Created by AGBro on 16/04/2025.
//

#ifndef WALLHUGGER_H
#define WALLHUGGER_H

using namespace std;

#include "Bug.h"

class WallHugger : public Bug{
    public:
    WallHugger(int id, Position pos, Direction dir, int size);
    void move() override;
    string getType() const override;
};



#endif //WALLHUGGER_H
