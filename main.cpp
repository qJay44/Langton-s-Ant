#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <iostream>
#include <stdlib.h>
#include <vector>

enum Direction {
  UP,
  RIGHT,
  DOWN,
  LEFT,
};

enum State {
  WHITE,
  BLACK,
  RED,
  GREEN,
  CYAN,
  YELLOW,
  PURPLE,
  BLUE,
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

sf::Color getColor(State state) {
  switch (state) {
    case WHITE:  return sf::Color::White;
    case RED:    return sf::Color::Red;
    case GREEN:  return sf::Color::Green;
    case CYAN:   return sf::Color::Cyan;
    case YELLOW: return sf::Color::Yellow;
    case PURPLE: return sf::Color::Magenta;
    case BLACK:  return sf::Color::Black;
    case BLUE:   return sf::Color::Blue;
  }
};


int main() {

  const int width = 800;
  const int height = 800;
  const int squareSize = 5;
  const int amount = width / squareSize;
  const int stepsPerFrame = 200;
  srand((unsigned)time(NULL));

  Ant ant = Ant(amount / 2, amount / 2, amount, amount);

  std::vector<std::vector<State>> grid(amount, std::vector<State>(amount, WHITE));
  grid[ant.x][ant.y] = RED;

  // create the window
  sf::RenderWindow window(sf::VideoMode(width, height), "Langton's ant");
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
        case WHITE:
          ant.turnRight();
          grid[ant.x][ant.y] = RED;
          break;
        case RED:
          ant.turnRight();
          grid[ant.x][ant.y] = GREEN;
          break;
        case GREEN:
          ant.turnRight();
          grid[ant.x][ant.y] = CYAN;
          break;
        case CYAN:
          ant.turnLeft();
          grid[ant.x][ant.y] = YELLOW;
          break;
        case YELLOW:
          ant.turnRight();
          grid[ant.x][ant.y] = PURPLE;
          break;
        case PURPLE:
          ant.turnLeft();
          grid[ant.x][ant.y] = BLACK;
          break;
        case BLACK:
          ant.turnLeft();
          grid[ant.x][ant.y] = BLUE;
          break;
        case BLUE:
          ant.turnRight();
          grid[ant.x][ant.y] = WHITE;
          break;
      }
      ant.moveForward();
    }

    for (int i = 0; i < amount; i++) {
      for (int j = 0; j < amount; j++) {
        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(squareSize, squareSize));
        rect.setPosition(i * squareSize, j * squareSize);
        rect.setFillColor(getColor(grid[i][j]));

        window.draw(rect);
      }
    }

    // end the current frame
    window.display();
}

  return 0;
}

