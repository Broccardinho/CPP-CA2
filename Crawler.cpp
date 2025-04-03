//
// Created by AGBro on 31/03/2025.
//

#include "Crawler.h"
#include <cstdlib>
#include <ctime>
#include <sstream>

Crawler::Crawler(int id, Position pos, Direction dir, int size)
    : id(id), position(pos), direction(dir), size(size), alive(true) {
    path.push_back(pos);  // Initialize path with starting position
    srand(static_cast<unsigned>(time(nullptr)));  // Seed random number generator
}

void Crawler::move() {
    if (!alive) return;

    // If way is blocked, change direction randomly until not blocked
    while (isWayBlocked()) {
        direction = static_cast<Direction>((rand() % 4) + 1);  // Random direction 1-4
    }

    // Move based on current direction
    Position newPos = position;
    switch (direction) {
        case Direction::NORTH: newPos.y--; break;
        case Direction::EAST:  newPos.x++; break;
        case Direction::SOUTH: newPos.y++; break;
        case Direction::WEST:  newPos.x--; break;
    }

    position = newPos;
    path.push_back(newPos);  // Add new position to path history
}

bool Crawler::isWayBlocked() const {
    switch (direction) {
        case Direction::NORTH: return position.y == 0;
        case Direction::EAST:  return position.x == 9;
        case Direction::SOUTH: return position.y == 9;
        case Direction::WEST:  return position.x == 0;
        default: return false;
    }
}

string Crawler::directionToString() const {
    switch (direction) {
        case Direction::NORTH: return "North";
        case Direction::EAST:  return "East";
        case Direction::SOUTH: return "South";
        case Direction::WEST:  return "West";
        default: return "Unknown";
    }
}