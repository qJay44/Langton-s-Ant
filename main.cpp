#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>
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
  const int width = 1200;
  const int height = 900;
  const int squareSize = 4;
  const int amountX = width / squareSize;
  const int amountY = height / squareSize;
  const int stepsPerFrame = 200;

  srand((unsigned)time(NULL));

  Ant ant = Ant(amountX / 2, amountY / 2, amountX, amountY);

  // grid
  std::vector<std::vector<State>> grid(amountX, std::vector<State>(amountY, WHITE));
  grid[ant.x][ant.y] = RED;

  // create the window
  sf::RenderWindow window(sf::VideoMode(width, height), "Langton's ant");
  window.setFramerateLimit(75);

  sf::RenderTexture renderTexture;
  renderTexture.create(width, height);

  sf::Font font;
  font.loadFromFile("Minecraft rus.ttf");

  sf::Text iterTitle;
  iterTitle.setFont(font);
  iterTitle.setString("Iter: ");
  iterTitle.setCharacterSize(20);
  iterTitle.setFillColor(sf::Color::White);
  iterTitle.setPosition(sf::Vector2f(20.f, 20.f));

  int antSteps = 0;
  sf::Text antStepsText;
  antStepsText.setFont(font);
  antStepsText.setString(std::to_string(antSteps));
  antStepsText.setCharacterSize(20);
  antStepsText.setFillColor(sf::Color::White);
  antStepsText.setPosition(sf::Vector2f(90.f, 20.f));

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
    window.clear(sf::Color::Black);

    // draw everything here...

    for (int step = 0; step < stepsPerFrame; step++) {

      // A rectangle with color to draw
      sf::RectangleShape rect;
      rect.setSize(sf::Vector2f(squareSize, squareSize));
      rect.setPosition(ant.x * squareSize, ant.y * squareSize);
      rect.setFillColor(getColor(grid[ant.x][ant.y]));

      // Draw the rectangle on the render texture
      renderTexture.draw(rect);
      renderTexture.display();

      // Get the render texture and draw it on the window
      const sf::Texture &texture = renderTexture.getTexture();
      sf::Sprite sprite(texture);
      window.draw(sprite);

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
      antSteps++;
    }

    antStepsText.setString(std::to_string(antSteps));
    window.draw(iterTitle);
    window.draw(antStepsText);

    // end the current frame
    window.display();
  }

  return 0;
}

