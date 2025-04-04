//
// Created by AGBro on 31/03/2025.
//
//
#ifndef BOARD_H
#define BOARD_H

// #include "Bug.h"
#include "Position.h"
#include "Crawler.h"
#include <vector>
#include <map>
#include <memory>
#include <string>
using namespace std;

class Board {
private:
    vector<unique_ptr<Crawler>> crawlers_;  //Memory managements

    map<Position, vector<Crawler*>> cellOccupancy;  //Bug tracker


    void updateCellOccupancy();
    void fightInCell(Position pos);
    void writeLifeHistoryToFile() const;

public:
    Board();
    ~Board() = default;


    void initializeBoard(const string& filename);
    void displayAllCrawlers() const;
    Crawler* findBug(int id) const;
    void tapBoard();
    void displayLifeHistory() const;
    void displayAllCells() const;
    void runSimulation();


    bool isGameOver() const;
    int getAliveBugCount() const;
};

#endif // BOARD_H