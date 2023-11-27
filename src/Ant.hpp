#include "pch.h"
#include "myutils.hpp"

class Ant {
  enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT,
  };

  Direction direction = UP;
  sf::Vector2i position;
  int steps = 0;

  public:
    Ant(sf::Vector2i pos) : position(pos) {}

    const sf::Vector2i& getPosition() const { return position; }
    const int& getSteps() const { return steps; }

    void turnRight() { direction = (Direction)((direction + 1) % 4); }
    void turnLeft()  { direction = (Direction)(((direction - 1) % 4 + 4) % 4); }

    void move() {
      int& x = position.x;
      int& y = position.y;

      switch (direction) {
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

      x = (x % WIDTH + WIDTH) % WIDTH;
      y = (y % HEIGHT + HEIGHT) % HEIGHT;

      steps++;
    }
};

