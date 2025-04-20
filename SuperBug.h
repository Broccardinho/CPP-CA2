#ifndef SUPERBUG_H
#define SUPERBUG_H

#include "Bug.h"
#include <SFML/Graphics.hpp>

class SuperBug : public Bug {
public:
    SuperBug(int id, Position pos, Direction dir, int size);

    void move() override;  // Override with player-controlled logic
    std::string getType() const override;

    void handleInput(sf::Keyboard::Key key); // Handles player input
};

#endif
