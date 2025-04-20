//
// Created by AGBro on 19/04/2025.
//

#include "SuperBug.h"
#include <iostream>
#include <algorithm>

SuperBug::SuperBug(int id, Position pos, Direction dir, int size)
    : Bug(id, pos, dir, size) {}

void SuperBug::move() {
    // Movement is manual via handleInput, so leave this empty
}

void SuperBug::handleInput(sf::Keyboard::Key key) {
    Position newPos = position;

    switch (key) {
        case sf::Keyboard::Up:    newPos.y = std::max(0, newPos.y - 1); direction = Direction::NORTH; break;
        case sf::Keyboard::Down:  newPos.y = std::min(9, newPos.y + 1); direction = Direction::SOUTH; break;
        case sf::Keyboard::Left:  newPos.x = std::max(0, newPos.x - 1); direction = Direction::WEST; break;
        case sf::Keyboard::Right: newPos.x = std::min(9, newPos.x + 1); direction = Direction::EAST; break;
        default: return;
    }

    if (newPos != position) {
        position = newPos;
        addToPath(newPos);
    }
}

std::string SuperBug::getType() const {
    return "SuperBug";
}
