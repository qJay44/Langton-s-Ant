#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <stdlib.h>

enum Direction {
  UP,
  RIGHT,
  DOWN,
  LEFT,
};

class Ant {
  private:
    int windowWidth, windowHeight;
    Direction dir = UP;

  public:
    int x, y;

    Ant(int x, int y, int windowWidth, int windowHeight) {
      this->x = x;
      this->y = y;
      this->windowWidth = windowWidth;
      this->windowHeight = windowHeight;
    }

    void turnRight() {
      switch (dir) {
        case UP:
          dir = RIGHT;
          break;
        case RIGHT:
          dir = DOWN;
          break;
        case DOWN:
          dir = LEFT;
          break;
        case LEFT:
          dir = UP;
          break;
      }
    }

    void turnLeft() {
      switch (dir) {
        case LEFT:
          dir = DOWN;
          break;
        case DOWN:
          dir = RIGHT;
          break;
        case RIGHT:
          dir = UP;
          break;
        case UP:
          dir = LEFT;
          break;
      }
    }

    void moveForward() {
      switch (dir) {
        case UP:
          y--;
          break;
        case RIGHT:
          x++;
          break;
        case DOWN:
          y++;
          break;
        case LEFT:
          x--;
          break;
      }

      if (x > windowWidth - 1) x = 0;
      if (x < 0) x = windowWidth - 1;

      if (y > windowHeight - 1) y = 0;
      if (y < 0) y = windowHeight - 1;
    }
};

int main() {

  const int width = 800;
  const int height = 800;
  const int squareSize = 8;
  const int amount = width / squareSize;
  const int stepsPerFrame = 5;
  srand((unsigned)time(NULL));

  int grid[amount][amount] = {};

  Ant ant = Ant(amount / 2, amount / 2, amount, amount);

  grid[ant.x][ant.y] = 1;

  // create the window
  sf::RenderWindow window(sf::VideoMode(width, height), "My window");
  window.setFramerateLimit(75);

  // run the program as long as the window is open
  while (window.isOpen())
  {
      // check all the window's events that were triggered since the last iteration of the loop
      sf::Event event;
      while (window.pollEvent(event))
      {
          // "close requested" event: we close the window
          if (event.type == sf::Event::Closed)
              window.close();
      }

      // clear the window with black color
      window.clear(sf::Color::White);

      // draw everything here...

      for (int step = 0; step < stepsPerFrame; step++) {
        switch (grid[ant.x][ant.y]) {
          case 0:
            ant.turnRight();
            grid[ant.x][ant.y] = 1;
            break;
          case 1:
            ant.turnLeft();
            grid[ant.x][ant.y] = 0;
            break;
        }
        ant.moveForward();
      }

      for (int i = 0; i < amount; i++) {
        for (int j = 0; j < amount; j++) {
          sf::RectangleShape rect;
          rect.setSize(sf::Vector2f(squareSize, squareSize));
          rect.setPosition(i * squareSize, j * squareSize);
          rect.setFillColor((grid[i][j] == 0) ? sf::Color(0) : sf::Color(255));

          window.draw(rect);
        }
      }

      // end the current frame
      window.display();
  }

  return 0;
}

