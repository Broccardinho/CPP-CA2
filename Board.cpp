#include "Board.h"
#include "Crawler.h"
#include "Hopper.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>
#include <ctime>
#include <iomanip>
#include "SuperBug.h"

#include "WallHugger.h"
using namespace std;



Board::Board() {
    // bug direction changer
    srand(static_cast<unsigned int>(time(nullptr)));
}

Board::~Board() {
    clearBugs(); // Cleans up all allocated Bug objects
}

void Board::clearBugs() {
    for (Bug *bug: bugs) {
        delete bug;
    }
    bugs.clear();

    superBug = nullptr; // the superbug must be reset aswell
}



void Board::initializeBoard(const string &filename) {
    clearBugs(); // Clear any existing bugs
    int id, x, y, direction, size, hopLength = 0;

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }
        stringstream ss(line);
        char type;
        int id, x, y, direction, size;
        char comma;

        //error checkers
        if (!(ss >> type >> comma)) {
            cerr << "Error reading bug type from line: " << line << endl;
            continue;
        }

        if (!(ss >> id >> comma >> x >> comma >> y >> comma >> direction >> comma >> size)) {
            cerr << "Error parsing bug data from line: " << line << endl;
            continue;
        }

        if (type == 'H' && !(ss >> comma >> hopLength)) {
            cerr << "Error reading bug data from line: " << line << endl;
            continue;
        }

        if (direction < 1 || direction > 4) {
            cerr << "Invalid direction (" << direction << ") for bug ID " << id << endl;
            continue;
        }

        Position pos{x, y};
        Direction dir = static_cast<Direction>(direction);

        if (type == 'C') {
            bugs.push_back(new Crawler(id, pos, dir, size));
            cout << "Created Crawler: ID=" << id << ", Position=(" << x << "," << y
                    << "), Direction=" << direction << ", Size=" << size << endl;
        } else if (type == 'H') {
            bugs.push_back(new Hopper(id, pos, dir, size, hopLength));
            cout << "Created Hopper: ID=" << id << ", Position=(" << x << "," << y
                    << "), Direction=" << direction << ", Size=" << size << ", HopLength = " << hopLength << endl;
        } else if (type == 'W') {
            bugs.push_back(new WallHugger(id, pos, dir, size));
            cout << "Created WallHugger: ID=" << id << ", Position=(" << x << "," << y
                    << "), Direction=" << direction << ", Size=" << size << endl;
        } else {
            cerr << "Unknown bug type: " << type << endl;
        }
    }
    if (bugs.empty()) {
        cerr << "Warning: No bugs were loaded from the file." << endl;
    } else {
        cout << "Successfully loaded " << bugs.size() << " bugs." << endl;
    }
}

void Board::displayAllBugs() const {
    for (const Bug *bug: bugs) {
        cout << bug->getId() << " "
                << bug->getType() << " "
                << "(" << bug->getPosition().x << "," << bug->getPosition().y << ") "
                << bug->getSize() << " "
                << bug->directionToString() << " "
                << (bug->isAlive() ? "Alive" : "Dead") << endl;
        if (const Hopper *h = dynamic_cast<const Hopper *>(bug)) {
            cout << "HopLength: " << h->getHopLength();
        }
        cout << endl;
    }
}

void Board::findBugById(int id) const {
    for (const Bug *bug: bugs) {
        if (bug->getId() == id) {
            cout << "Bug Found:\n"
                    << "ID: " << bug->getId() << " | "
                    << "Type: " << bug->getType() << " | "
                    << "Position: (" << bug->getPosition().x << "," << bug->getPosition().y << ") | "
                    << "Size: " << bug->getSize() << " | "
                    << "Direction: " << bug->directionToString() << " | "
                    << "Status: " << (bug->isAlive() ? "Alive" : "Dead") << endl;
            if (const Hopper *h = dynamic_cast<const Hopper *>(bug)) {
                cout << "HopLength: " << h->getHopLength();
            }
            return;
        }
    }
    cout << "Bug with ID " << id << " not found.\n";
}

void Board::tapBoard() {
    //cout << "\n=== TAPPING THE BOARD ===" << endl;
    moveAllLivingBugs();
    //
    // cout << "\nPositions before battles:" << endl;
    // updateBugPositions();
    // for (auto &[pos, bugs]: bugsByPosition) {
    //     if (bugs.size() > 1) {
    //         cout << "Multiple bugs at (" << pos.x << "," << pos.y << "): ";
    //         for (auto bug: bugs) cout << bug->getId() << " ";
    //         cout << endl;
    //     }
    // }

    resolveBattles();
    //
    // cout << "\nBattle results:" << endl;
    // updateBugPositions();
    // for (auto &[pos, bugs]: bugsByPosition) {
    //     if (!bugs.empty()) {
    //         cout << "(" << pos.x << "," << pos.y << "): ";
    //         for (auto bug: bugs) {
    //             cout << bug->getId() << "(" << (bug->isAlive() ? "Alive" : "Dead") << ") ";
    //         }
    //         cout << endl;
    //     }
    // }
    //cout << "Board Tapped!!! Bugs have moved and battles over!!!" << endl;
}

void Board::moveAllLivingBugs() {
    for (Bug *bug: bugs) {
        if (bug->isAlive()) {
            bug->move();
        }
    }
    updateBugPositions();
}

void Board::updateBugPositions() {
    bugsByPosition.clear();
    for (Bug *bug: bugs) {
        if (bug->isAlive()) {
            bugsByPosition[bug->getPosition()].push_back(bug);
        }
    }
}

void Board::resolveBattles() {
    updateBugPositions();

    for (auto &[position, bugsInCell]: bugsByPosition) {
        vector<Bug *> livingBugs;
        copy_if(bugsInCell.begin(), bugsInCell.end(), back_inserter(livingBugs),
                [](Bug *bug) { return bug->isAlive(); });

        if (livingBugs.size() > 1) {
            cout << "Battle at (" << position.x << "," << position.y << ") between: ";
            for (auto bug: livingBugs) cout << bug->getId() << " ";
            cout << endl;

            auto maxIt = max_element(livingBugs.begin(), livingBugs.end(),
                                     [](Bug *a, Bug *b) { return a->getSize() < b->getSize(); });
            int maxSize = (*maxIt)->getSize();

            vector<Bug *> strongestBugs;
            copy_if(livingBugs.begin(), livingBugs.end(), back_inserter(strongestBugs),
                    [maxSize](Bug *bug) { return bug->getSize() == maxSize; });

            if (!strongestBugs.empty()) {
                Bug *winner = strongestBugs[rand() % strongestBugs.size()];
                int totalSizeEaten = 0;

                for (Bug *bug: livingBugs) {
                    if (bug != winner) {
                        totalSizeEaten += bug->getSize();
                        bug->setAlive(false);
                        cout << "  Bug " << winner->getId() << " ate " << bug->getId() << endl;
                    }
                }

                if (totalSizeEaten > 0) {
                    winner->grow(totalSizeEaten);
                    cout << "  Bug " << winner->getId() << " grew to size "
                            << winner->getSize() << endl;
                }
            }
        }
    }
}

void Board::displayLifeHistory() const {
    if (bugs.empty()) {
        cout << "No bugs found!" << endl;
        return;
    }

    cout << "\n=== LIFE HISTORY OF ALL BUGS ===\n";
    for (const Bug *bug: bugs) {
        cout << "\nBug " << bug->getId();
        cout << " Path: ";

        const auto &path = bug->getPath();
        for (auto it = path.begin(); it != path.end(); ++it) {
            cout << "(" << it->x << "," << it->y << ")";
            if (next(it) != path.end()) cout << " -> ";
        }
        cout << "\nStatus: " << (bug->isAlive() ? "Alive" : "Dead") << endl;
    }
}

void Board::displayAllCells() const {
    map<Position, vector<const Bug *> > cellMap;
    for (const Bug *bug: bugs) {
        if (bug->isAlive()) {
            cellMap[bug->getPosition()].push_back(bug);
        }
    }

    cout << "\n=== ALL CELLS ===\n";
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            Position pos{x, y};
            cout << "(" << x << "," << y << ")";

            auto it = cellMap.find(pos);
            if (it == cellMap.end()) {
                cout << "empty";
            } else {
                bool first = true;
                for (const Bug *bug: it->second) {
                    if (!first)
                        cout << ", ";
                    cout << bug -> getType() << ", " << bug->getId();
                    first = false;
                }
            }
            cout << endl;
        }
    }
}

bool Board::isGameOver() const {
    int aliveCount = 0;
    for (const Bug *bug: bugs) {
        if (bug->isAlive()) aliveCount++;
        if (aliveCount > 1) return false;
    }
    return true;
}

void Board::runSimulation() {
    if (bugs.empty()) {
        cout << "No bugs found!" << endl;
        return;
    }

    cout << "\n=== STARTING SIMULATION ===" << endl;

    int tapCount = 0;
    while (!isGameOver()) {
        tapBoard();
        tapCount++;

        if (tapCount % 10 == 0) {
            int aliveCount = 0;
            for (const Bug *bug: bugs) {
                if (bug->isAlive()) aliveCount++;
            }
            cout << "\nAfter " << tapCount << " taps: " << aliveCount << " bugs remaining\n";
        }

        this_thread::sleep_for(chrono::milliseconds(100));
    }

    for (const Bug *bug: bugs) {
        if (bug->isAlive()) {
            cout << "\n=== SIMULATION COMPLETE ===" << endl;
            cout << "Winner after " << tapCount << " taps: "
                    << "Bug " << bug->getId() << " Size: " << bug->getSize() << endl;
            break;
        }
    }
}

void Board::saveLifeHistoryToFile() const {
    const string filename = "crawlers-result.txt";
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Error: Could not open file " << filename << " for writing." << endl;
        return;
    }

    time_t now = time(nullptr); //gets time

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    outFile << "Bug Life History - " << ctime(&now) << "\n";

    for (const Bug *bug: bugs) {
        outFile << "Bug " << bug->getId() << ":\n";
        outFile << "  Type: " << bug->getType() << "\n";
        outFile << "  Size: " << bug->getSize() << "\n";
        outFile << "  Status: " << (bug->isAlive() ? "Alive" : "Dead") << "\n";
        outFile << "  Path: ";

        const auto &path = bug->getPath();
        for (auto it = path.begin(); it != path.end(); ++it) {
            outFile << "(" << it->x << "," << it->y << ")";
            if (next(it) != path.end()) outFile << " -> ";
        }

        outFile << "\n\n";
    }

    outFile.close();
    cout << "Bug life history automatically saved to " << filename << endl;
}

void Board::addSuperBug() {
    if (!superBug) {
        Position startPos = {5, 5};
        superBug = new SuperBug(999, startPos, Direction::EAST, 99);
        bugs.push_back(superBug); // So it gets drawn
    }
}
