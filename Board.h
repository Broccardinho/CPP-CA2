#ifndef BOARD_H
#define BOARD_H

#include "Bug.h"
#include <vector>
#include <map>
#include <memory>
#include <string>

#include "BugType.h"
#include "SuperBug.h"
using namespace std;

class Board {
private:
    vector<Bug*> bugs;
    map<Position, vector<Bug*>> bugsByPosition;
    SuperBug* superBug = nullptr;

    void updateBugPositions();
    void createBug(BugType type, int id, Position pos, Direction dir, int size, int hopLength =0);

public:
    void addSuperBug();
    SuperBug* getSuperBug() const { return superBug; }

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
    void saveLifeHistoryToFile() const;//Q8
    const vector<Bug*>& getAllBugs() const { return bugs; }


    private:
    void moveAllLivingBugs();
    void resolveBattles();
};

#endif // BOARD_H
