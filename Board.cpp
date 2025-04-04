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
            crawlers_.push_back(make_unique<Crawler>(Crawler{id, pos, dir, size}));
        }
        // Add other bug types here when implemented
    }

    file.close();
    updateCellOccupancy();
}

void Board::displayAllCrawlers()const {
    cout << "\nAll Bugs: \n";
    cout << "---------------------------------------------------";
    cout << "ID\tType\tPosition\tSize\tDirection\tStatus\n";
    cout << "---------------------------------------------------";

    for (const auto& crawler : crawlers_) {
        cout << crawler->getId() << "\t"
        << "Crawler\t"
        << crawler->getPosition().x << ", " << crawler->getPosition().y << "\t"
        << crawler->getSize() << "\t"
        << crawler->directionToString() << "\t"
        << (crawler->isAlive() ? "Alive" : "Dead") << "\n";
    }
    cout << "---------------------------------------------------";
    cout << "Total bugs: " << crawlers_.size() << " ("
    << getAliveBugCount() << " alive, "
    << (crawlers_.size() - getAliveBugCount()) << " dead)\n";
}

Crawler* Board::findBug(int id) const {
    auto it = find_if(crawlers_.begin(), crawlers_.end(),
        [id](const unique_ptr<Crawler>& crawler) { return crawler->getId() == id; });

    return (it != crawlers_.end()) ? it->get() : nullptr;
}

void Board::tapBoard() {
    // Move all alive bugs
    for (auto& crawler : crawlers_) {
        if (crawler->isAlive()) {
            crawler->move();
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
    for (const auto& crawler : crawlers_) {
        cout << crawler->getId() << " " << crawler->typeToString() << " Path: ";
        for (const auto& pos : crawler->getPositions()) {
            cout << "(" << pos.x << "," << pos.y << ")";
            if (&pos != &crawler->getPositions().back()) {
                cout << ",";
            }
        }

        if (!crawler->isAlive()) {
            // Find who ate this bug (if any)
            for (const auto& potentialEater : crawlers_) {
                if (potentialEater->isAlive() &&
                    potentialEater->getPosition() == crawler->getPositions().back()) {
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
        displayAllCrawlers();  // Show current state
        this_thread::sleep_for(chrono::milliseconds(100));  // 0.1 second delay
    }

    // Find the last bug standing
    auto lastBug = find_if(crawlers_.begin(), crawlers_.end(),
        [](const unique_ptr<Crawler>& bug) { return bug->isAlive(); });

    if (lastBug != crawlers_.end()) {
        cout << "Game Over! Last bug standing: "
             << (*lastBug)->typeToString() << " "
             << (*lastBug)->getId() << endl;
    }

    writeLifeHistoryToFile();
}

// Private helper methods
void Board::updateCellOccupancy() {
    cellOccupancy.clear();

    for (auto& bug : crawlers_) {
        if (bug->isAlive()) {
            cellOccupancy[bug->getPosition()].push_back(bug.get());
        }
    }
}

void Board::fightInCell(Position pos) {
    auto& bugsInCell = cellOccupancy[pos];

    // Find the biggest bug(s)
    int maxSize = 0;
    vector<Crawler*> biggestBugs;

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
    Crawler* winner = biggestBugs[rand() % biggestBugs.size()];
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

    for (const auto& bug : crawlers_) {
        outFile << bug->getId() << " " << bug->typeToString() << " Path: ";
        for (const auto& pos : bug->getPositions()) {
            outFile << "(" << pos.x << "," << pos.y << ")";
            if (&pos != &bug->getPositions().back()) {
                outFile << ",";
            }
        }

        if (!bug->isAlive()) {
            // Find who ate this bug if there was a bug who ate the bug
            for (const auto& potentialEater : crawlers_) {
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
    return count_if(crawlers_.begin(), crawlers_.end(),
        [](const unique_ptr<Crawler>& bug) { return bug->isAlive(); });
}
//