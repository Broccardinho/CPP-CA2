//
// Created by AGBro on 31/03/2025.
//

#include "Board.h"
#include "Crawler.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>
#include <ctime>
#include <iomanip>
using namespace std;

Board::Board() {
    //random number generator
    srand(static_cast<unsigned int>(time(nullptr)));
}

void Board::initializeBoard(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        char type;
        int id, x, y, direction, size;
        char comma;

        ss >> type >> comma
           >> id >> comma
           >> x >> comma
           >> y >> comma
           >> direction >> comma
           >> size;

        Position pos{x, y};
        Direction dir = static_cast<Direction>(direction);

        if (type == 'C') {
            bugs.push_back(make_unique<Crawler>(id, pos, dir, size));
        }
        // Add other bug types here when implemented
    }

    file.close();
    updateCellOccupancy();
}

void Board::displayAllBugs() const {
    for (const auto& bug : bugs) {
        cout << bug->getId() << " "
             << bug->typeToString() << " "
             << "(" << bug->getPosition().x << "," << bug->getPosition().y << ") "
             << bug->getSize() << " "
             << bug->directionToString() << " "
             << (bug->isAlive() ? "Alive" : "Dead") << endl;
    }
}

Bug* Board::findBug(int id) const {
    auto it = find_if(bugs.begin(), bugs.end(),
        [id](const unique_ptr<Bug>& bug) { return bug->getId() == id; });

    return (it != bugs.end()) ? it->get() : nullptr;
}

void Board::tapBoard() {
    // Move all alive bugs
    for (auto& bug : bugs) {
        if (bug->isAlive()) {
            bug->move();
        }
    }

    updateCellOccupancy();

    // Check for fights in all occupied cells
    for (const auto& cell : cellOccupancy) {
        if (cell.second.size() > 1) {
            fightInCell(cell.first);
        }
    }
}

void Board::displayLifeHistory() const {
    for (const auto& bug : bugs) {
        cout << bug->getId() << " " << bug->typeToString() << " Path: ";
        for (const auto& pos : bug->getPositions()) {
            cout << "(" << pos.x << "," << pos.y << ")";
            if (&pos != &bug->getPositions().back()) {
                cout << ",";
            }
        }

        if (!bug->isAlive()) {
            // Find who ate this bug (if any)
            for (const auto& potentialEater : bugs) {
                if (potentialEater->isAlive() &&
                    potentialEater->getPosition() == bug->getPositions().back()) {
                    cout << " Eaten by " << potentialEater->getId();
                    break;
                }
            }
        }
        cout << endl;
    }
}

void Board::displayAllCells() const {
    for (int y = 0; y < 10; ++y) {
        for (int x = 0; x < 10; ++x) {
            Position pos{x, y};
            cout << "(" << x << "," << y << "): ";

            auto it = cellOccupancy.find(pos);
            if (it == cellOccupancy.end() || it->second.empty()) {
                cout << "empty";
            } else {
                for (size_t i = 0; i < it->second.size(); ++i) {
                    cout << it->second[i]->typeToString() << " " << it->second[i]->getId();
                    if (i < it->second.size() - 1) {
                        cout << ", ";
                    }
                }
            }
            cout << endl;
        }
    }
}

void Board::runSimulation() {
    while (!isGameOver()) {
        tapBoard();
        displayAllBugs();  // Show current state
        this_thread::sleep_for(chrono::milliseconds(100));  // 0.1 second delay
    }

    // Find the last bug standing
    auto lastBug = find_if(bugs.begin(), bugs.end(),
        [](const unique_ptr<Bug>& bug) { return bug->isAlive(); });

    if (lastBug != bugs.end()) {
        cout << "Game Over! Last bug standing: "
             << (*lastBug)->typeToString() << " "
             << (*lastBug)->getId() << endl;
    }

    writeLifeHistoryToFile();
}

// Private helper methods
void Board::updateCellOccupancy() {
    cellOccupancy.clear();

    for (auto& bug : bugs) {
        if (bug->isAlive()) {
            cellOccupancy[bug->getPosition()].push_back(bug.get());
        }
    }
}

void Board::fightInCell(Position pos) {
    auto& bugsInCell = cellOccupancy[pos];

    // Find the biggest bug(s)
    int maxSize = 0;
    vector<Bug*> biggestBugs;

    for (auto bug : bugsInCell) {
        if (bug->getSize() > maxSize) {
            maxSize = bug->getSize();
            biggestBugs.clear();
            biggestBugs.push_back(bug);
        } else if (bug->getSize() == maxSize) {
            biggestBugs.push_back(bug);
        }
    }

    // In te situation of multiple large bugs, one is randomly chosen to be eaten
    Bug* winner = biggestBugs[rand() % biggestBugs.size()];
    int totalSizeEaten = 0;

    // Mark all other bugs as dead and calculate total size
    for (auto bug : bugsInCell) {
        if (bug != winner) {
            bug->setAlive(false);
            totalSizeEaten += bug->getSize();
        }
    }

    // Winner grows by the total size of eaten bugs
    winner->grow(totalSizeEaten);
}

void Board::writeLifeHistoryToFile() const {
    // current time for filename
    auto now = time(nullptr);
    auto tm = *localtime(&now);
    ostringstream oss;
    oss << "bugs_life_history_" << put_time(&tm, "%Y-%m-%d_%H-%M-%S") << ".out";
    string filename = oss.str();

    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Error creating output file: " << filename << endl;
        return;
    }

    for (const auto& bug : bugs) {
        outFile << bug->getId() << " " << bug->typeToString() << " Path: ";
        for (const auto& pos : bug->getPositions()) {
            outFile << "(" << pos.x << "," << pos.y << ")";
            if (&pos != &bug->getPositions().back()) {
                outFile << ",";
            }
        }

        if (!bug->isAlive()) {
            // Find who ate this bug if there was a bug who ate the bug
            for (const auto& potentialEater : bugs) {
                if (potentialEater->isAlive() &&
                    potentialEater->getPosition() == bug->getPositions().back()) {
                    outFile << " Eaten by " << potentialEater->getId();
                    break;
                }
            }
        }
        outFile << endl;
    }

    outFile.close();
    cout << "Life history written to " << filename << endl;
}

bool Board::isGameOver() const {
    return getAliveBugCount() <= 1;
}

int Board::getAliveBugCount() const {
    return count_if(bugs.begin(), bugs.end(),
        [](const unique_ptr<Bug>& bug) { return bug->isAlive(); });
}