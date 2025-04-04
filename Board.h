#ifndef BOARD_H
#define BOARD_H

#include "Bug.h"
#include "Position.h"
#include "Crawler.h"
#include <vector>
#include <map>
#include <memory>
#include <string>
using namespace std;
class Board {
private:
    vector<Crawler*> bugs;
    map<Position, vector<Crawler*>> bugsByPosition;
public:
    Board();
    ~Board();

    void clearBugs();
     void initializeBoard(const string& filename);//Q1
    void displayAllBugs() const;//Q2
    void findBugById(int id) const;//Q3
    void tapBoard();//Q4
    void displayLifeHistory() const;//Q5
    void displayAllCells() const;//Q6
    void runSimulation();//Q7
    bool isGameOver() const;//Q7
    void saveLifeHistoryToFile();//Q8

    private:
    void moveAllLivingBugs();
    void resolveBattles();
    void updateBugPositions();
};

#endif // BOARD_H
