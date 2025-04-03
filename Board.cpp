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
    // bug direction changer
    srand(static_cast<unsigned int>(time(nullptr)));
}

Board::~Board() {
    clearBugs();  // Cleans up all allocated Bug objects
}

void Board::clearBugs() { //ensures that each time this is ran, the bugs are reset
    for (Crawler* bug : bugs) {
        delete bug;
    }
    bugs.clear();
}

void Board::initializeBoard(const string& filename) {
    clearBugs();  // Clear any existing bugs

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
    for (const Crawler* bug : bugs) {
        cout << bug->getId() << " "
             << "Crawler "  // Directly output the type since we only have Crawlers
             << "(" << bug->getPosition().x << "," << bug->getPosition().y << ") "
             << bug->getSize() << " "
             << bug->directionToString() << " "
             << (bug->isAlive() ? "Alive" : "Dead") << endl;
    }
}
