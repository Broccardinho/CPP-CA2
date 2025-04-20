#include "SFMLSimulation.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

void runSFMLSimulation(Board& board)
{
    const int cellSize = 60;
    const int gridSize = 10;

    RenderWindow window(VideoMode(gridSize * cellSize, gridSize * cellSize), "Bug Battle - SFML");
    window.setFramerateLimit(10);

    vector<RectangleShape> rectangles;
    vector<CircleShape> bugShapes;
    vector<Text> bugTexts;

    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        throw runtime_error("Could not load font");
    }

    // CHECKer board
    int i = 0;
    for (int x = 0; x < gridSize; x++) {
        for (int y = 0; y < gridSize; y++) {
            RectangleShape rect(Vector2f(cellSize, cellSize));
            rect.setFillColor(i%2==0 ? Color(240, 240, 240) : Color(200, 200, 200));
            i++;
            rect.setPosition(Vector2f(x*cellSize, y*cellSize));
            rectangles.push_back(rect);
        }
        i++;
    }

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        board.tapBoard();

        if (event.type == sf::Event::KeyPressed) {
            if (board.getSuperBug()) {
                board.getSuperBug()->handleInput(event.key.code);
            }
        }

        // Bug stufff
        bugShapes.clear();
        bugTexts.clear();
        for (const Bug* bug : board.getAllBugs()) {
            if (!bug->isAlive()) continue;

            CircleShape bugShape(20);
            string type = bug->getType();

            if (type == "Crawler") {
                bugShape.setFillColor(Color::Red);
            } else if (type == "Hopper") {
                bugShape.setFillColor(Color::Blue);
            } else if (type == "WallHugger") {
                bugShape.setFillColor(Color::Yellow);
            } else if (type == "SuperBug") {
                bugShape.setFillColor(sf::Color::Magenta);
            }
            else {
                bugShape.setFillColor(Color::White);
            }


            Position pos = bug->getPosition();
            bugShape.setPosition(pos.x * cellSize + 10, pos.y * cellSize + 10);
            bugShapes.push_back(bugShape);

            Text bugIdText;
            bugIdText.setFont(font);
            bugIdText.setCharacterSize(16);
            bugIdText.setFillColor(Color::Black);
            bugIdText.setString(to_string(bug->getId()));
            bugIdText.setPosition(pos.x * cellSize + 15, pos.y * cellSize + 15);
            bugTexts.push_back(bugIdText);
        }

        window.clear();

        // Draw grid
        for (RectangleShape &rect : rectangles) {
            window.draw(rect);
        }

        // Draw bugs
        for (CircleShape &bug : bugShapes) {
            window.draw(bug);
        }

        // Draw da text
        for (Text &text : bugTexts) {
            window.draw(text);
        }

        window.display();

        if (board.isGameOver()) {
            sleep(seconds(2));
            window.close();
        }
    }
}