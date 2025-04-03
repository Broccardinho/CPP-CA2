#ifndef BOARD_H
#define BOARD_H

#include "Bug.h"
#include "Crawler.h"
#include <vector>
#include <map>
#include <memory>
#include <string>
using namespace std;
class Board {
private:
    vector<Crawler*> bugs;
public:
    Board();
    ~Board();

    void clearBugs();
     void initializeBoard(const string& filename);//Q1
    void displayAllBugs() const;//Q2
};

#endif // BOARD_H