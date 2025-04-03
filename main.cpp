#include <cstdio>

#include "Board.h"
using namespace std;
#include <iostream>

int main () {
    Board board;
    int choice;
    cout << "\n===== Bug's Life Simulation =====\n";
    cout << "1. Initialize Bug Board (load from file)\n";
    cout << "2. Display all Bugs\n";
    cout << "3. Find a Bug (by ID)\n";
    cout << "4. Tap the Bug Board (move all bugs)\n";
    cout << "5. Display Life History of all Bugs\n";
    cout << "6. Display all Cells and their Bugs\n";
    cout << "7. Run Simulation (auto-tap every 0.1s)\n";
    cout << "8. Exit (save history to file)\n";
    cout << "================================\n";
    cout << "Enter your choice (1-8): ";
    cin >> choice;

    switch (choice) {
        case 1:
             board.initializeBoard("crawler-bugs.txt");  // Call initializeBoard with a filename
        //move bug txt file to cmake
        break;
        case 2:;
    }


}
