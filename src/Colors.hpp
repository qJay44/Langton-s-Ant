#include <array>
#include "pch.h"

#define GRAY         0
#define SOFT_BLACK   1
#define RED          3
#define GREEN        4
#define BLUE         5
#define YELLOW       6
#define ORANGE       7
#define PURPLE       8
#define MAGENTA      9
#define CYAN         10
#define RUBBY_PINK   11
#define BROWN        12
#define LIME         13
#define LIGHT_BLUE   14
#define YUKON_GOLD   15
#define SCIENCE_BLUE 16

const std::array<sf::Color, 16> colors {
  sf::Color(220,220,220),
  sf::Color(31, 30, 31),
  sf::Color::Red,
  sf::Color::Green,
  sf::Color::Blue,
  sf::Color::Yellow,
  sf::Color(255, 165, 0),
  sf::Color(107, 6, 208),
  sf::Color::Magenta,
  sf::Color(0, 0, 139),
  sf::Color(107, 106, 8),
  sf::Color(8, 105, 207),
  sf::Color(50, 205, 50),
  sf::Color(165, 42, 42),
  sf::Color(207, 142, 146),
  sf::Color::Cyan
};

