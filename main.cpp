
#include "Board.h"
#include <iostream>

int main() {
    Board board;
    board.initializeBoard("crawler-bugs.txt");
    board.displayAllCrawlers();
}
