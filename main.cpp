#include <cstdio>
#include "Board.h"
using namespace std;
#include <iostream>

int main() {
    Board board;
    int choice;

    do {
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
                board.initializeBoard("crawler-bugs.txt");
            break;
            case 2:
                board.displayAllBugs();
            break;
            case 3: {
                int searchId;
                cout << "Enter Bug ID to find: ";
                cin >> searchId;
                board.findBugById(searchId);
                break;
            }
            case 4:
                board.tapBoard();
                    break;
            case 5:
                // Implement life history display
                    break;
            case 6:
                // Implement cell display
                    break;
            case 7:
                // Implement simulation
                    break;
            case 8:
                cout << "Exiting program..." << endl;
            break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 8);

    return 0;
}
//