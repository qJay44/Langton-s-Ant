#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

enum Direction {
  UP,
  RIGHT,
  DOWN,
  LEFT,
};

enum State {
  SOFT_BLACK,
  BLACK,
  RED,
  GREEN,
  BLUE,
  YELLOW,
  ORANGE,
  PURPLE,
  MAGENTA,
  CYAN,
  RUBBY_PINK,
  BROWN,
  LIME,
  LIGHT_BLUE,
  YUKON_GOLD,
  DARK_BLUE
};

class Ant {
  private:
    int windowWidth, windowHeight;
    Direction dir = UP;

  public:
    int x, y;
    int steps = 0;

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
      else if (x < 0) x = windowWidth - 1;

      if (y > windowHeight - 1) y = 0;
      else if (y < 0) y = windowHeight - 1;
    }
};

sf::Color getColor(State state) {
  switch (state) {
    case SOFT_BLACK: return sf::Color(31, 30, 31);
    case BLACK:      return sf::Color::Black;
    case RED:        return sf::Color::Red;
    case GREEN:      return sf::Color::Green;
    case BLUE:       return sf::Color::Blue;
    case YELLOW:     return sf::Color::Yellow;
    case ORANGE:     return sf::Color(255, 165, 0);
    case PURPLE:     return sf::Color(138, 43, 226);
    case MAGENTA:    return sf::Color::Magenta;
    case CYAN:       return sf::Color::Cyan;
    case RUBBY_PINK: return sf::Color(207, 142, 146);
    case BROWN:      return sf::Color(165, 42, 42);
    case LIME:       return sf::Color(50, 205, 50);
    case LIGHT_BLUE: return sf::Color(173, 216, 230);
    case YUKON_GOLD: return sf::Color(107, 106, 8);
    case DARK_BLUE:  return sf::Color(0, 0, 139);
  }
};

// Custom locale separator
struct separated : std::numpunct<char> {
  char do_thousands_sep() const { return ' '; }
  std::string do_grouping() const { return "\03"; }
};

// Separate thousands
std::string formatWithDots(int value) {
  static std::locale ourLocal(std::cout.getloc(), new separated);
  std::stringstream ss;
  ss.imbue(ourLocal);
  ss << std::fixed << value;

  return ss.str();
};

int main() {
  const int width = 1200;
  const int height = 900;
  const int squareSize = 1;
  const int amountX = width / squareSize;
  const int amountY = height / squareSize;
  const int stepsPerFrame = 20000;

  srand((unsigned)time(NULL));

  Ant ant = Ant(amountX / 2, amountY / 2, amountX, amountY);

  // grid
  std::vector<std::vector<State>> grid(amountX, std::vector<State>(amountY, SOFT_BLACK));

  // create the window
  sf::RenderWindow window(sf::VideoMode(width, height), "Langton's ant");
  window.setFramerateLimit(75);

  sf::RenderTexture renderTexture;
  renderTexture.create(width, height);

  // Get the render texture and make sprite of it
  const sf::Texture &canvasTexture = renderTexture.getTexture();
  sf::Sprite canvasSprite(canvasTexture);

  sf::Font font;
  font.loadFromFile("Minecraft rus.ttf");

  sf::Text iterTitle;
  iterTitle.setFont(font);
  iterTitle.setString("Iter: ");
  iterTitle.setCharacterSize(20);
  iterTitle.setFillColor(sf::Color::White);
  iterTitle.setPosition(sf::Vector2f(20.f, 20.f));

  sf::Text antStepsText;
  antStepsText.setFont(font);
  antStepsText.setString("0");
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
    window.clear(getColor(SOFT_BLACK));

    // draw everything here...
    for (size_t step = 0; step < stepsPerFrame; step++) {

      // A rectangle with color to draw
      sf::RectangleShape rect;
      rect.setSize(sf::Vector2f(squareSize, squareSize));
      rect.setPosition(ant.x, ant.y);
      rect.setFillColor(getColor(grid[ant.x][ant.y]));

      // Draw the rectangle on the render texture
      renderTexture.draw(rect);

      switch (grid[ant.x][ant.y]) {
        case SOFT_BLACK:
          ant.turnRight();
          grid[ant.x][ant.y] = BLACK;
          break;
        case BLACK:
          ant.turnRight();
          grid[ant.x][ant.y] = RED;
          break;
        case RED:
          ant.turnLeft();
          grid[ant.x][ant.y] = GREEN;
          break;
        case GREEN:
          ant.turnLeft();
          grid[ant.x][ant.y] = BLUE;
          break;
        case BLUE:
          ant.turnLeft();
          grid[ant.x][ant.y] = YELLOW;
          break;
        case YELLOW:
          ant.turnRight();
          grid[ant.x][ant.y] = ORANGE;
          break;
        case ORANGE:
          ant.turnLeft();
          grid[ant.x][ant.y] = PURPLE;
          break;
        case PURPLE:
          ant.turnLeft();
          grid[ant.x][ant.y] = MAGENTA;
          break;
        case MAGENTA:
          ant.turnLeft();
          grid[ant.x][ant.y] = DARK_BLUE;
          break;
        case DARK_BLUE:
          ant.turnLeft();
          grid[ant.x][ant.y] = YUKON_GOLD;
          break;
        case YUKON_GOLD:
          ant.turnLeft();
          grid[ant.x][ant.y] = LIGHT_BLUE;
          break;
        case LIGHT_BLUE:
          ant.turnLeft();
          grid[ant.x][ant.y] = LIME;
          break;
        case LIME:
          ant.turnLeft();
          grid[ant.x][ant.y] = BROWN;
          break;
        case BROWN:
          ant.turnLeft();
          grid[ant.x][ant.y] = RUBBY_PINK;
          break;
        case RUBBY_PINK:
          ant.turnLeft();
          grid[ant.x][ant.y] = CYAN;
          break;
        case CYAN:
          ant.turnRight();
          grid[ant.x][ant.y] = BLACK;
          break;
      }
      ant.moveForward();
      ant.steps++;
    }

    antStepsText.setString(formatWithDots(ant.steps));
    window.draw(iterTitle);
    window.draw(antStepsText);
    window.draw(canvasSprite);

    // end the current frame
    window.display();
  }

  return 0;
}

