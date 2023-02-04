#include <SFML/Graphics.hpp>

enum Direction {
  UP,
  RIGHT,
  DOWN,
  LEFT,
};

class Ant {
  public:
    int x, y, windowWidth, windowHeight;
    Direction dir = UP;

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

      if (x > windowWidth) x = 0;
      if (x < 0) x = windowWidth - 1;

      if (y > windowHeight) y = 0;
      if (y < 0) y = windowHeight - 1;
    }
};

void draw(int[][10] , Ant);

int main() {

  const int width = 400;
  const int height = 400;
  int grid[width][height] = {};

  Ant ant = Ant(200, 200, 400, 400);

  grid[ant.x][ant.y] = 1;

  // create the window
  sf::RenderWindow window(sf::VideoMode(width, height), "My window");

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
      const int state = grid[ant.x][ant.y];

      switch (state) {
        case 0:
          ant.turnRight();
          grid[ant.x][ant.y] = 1;
          ant.moveForward();
          break;
        case 1:
          ant.turnLeft();
          grid[ant.x][ant.y] = 0;
          ant.moveForward();
          break;
      }

      // end the current frame
      window.display();
  }

  return 0;
}

