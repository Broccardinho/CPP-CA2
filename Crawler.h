#ifndef CRAWLER_H
#define CRAWLER_H

#include "Bug.h"

class Crawler : public Bug {
public:
    Crawler(int id, Position pos, Direction dir, int size);
    void move() override;
    std::string getType() const override;
};

#endif