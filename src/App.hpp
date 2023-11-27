#include "Ant.hpp"
#include "Colors.hpp"
#include "utils.hpp"
#include <vector>

class App {
  sf::RenderWindow window;
  sf::RenderTexture renderTexture;
  sf::Sprite canvasSprite;
  sf::Font font;
  sf::Text iterTitle;
  sf::Text antStepsText;

  std::vector<int> grid;
  Ant* ant;

  void setupSFML() {
    // create the window
    window.create(sf::VideoMode(WIDTH, HEIGHT), "Langton's ant");
    window.setFramerateLimit(75);

    renderTexture.create(WIDTH, HEIGHT);

    // Get the render texture and make sprite of it
    const sf::Texture &canvasTexture = renderTexture.getTexture();
    canvasSprite.setTexture(canvasTexture);

    font.loadFromFile("Minecraft rus.ttf");

    iterTitle.setFont(font);
    iterTitle.setString("Iter: ");
    iterTitle.setCharacterSize(20);
    iterTitle.setFillColor(sf::Color::White);
    iterTitle.setOutlineColor(colors[SOFT_BLACK]);
    iterTitle.setOutlineThickness(4.f);
    iterTitle.setPosition(sf::Vector2f(20.f, 20.f));

    antStepsText.setFont(font);
    antStepsText.setString("0");
    antStepsText.setCharacterSize(20);
    antStepsText.setFillColor(sf::Color::White);
    antStepsText.setOutlineColor(colors[SOFT_BLACK]);
    antStepsText.setOutlineThickness(4.f);
    antStepsText.setPosition(sf::Vector2f(90.f, 20.f));
  }

  void setupProgram() {
    srand((unsigned)time(NULL));

    ant = new Ant({WIDTH / 2, HEIGHT / 2});

    grid.resize(COLUMNS * ROWS);
    grid.reserve(COLUMNS * ROWS);

    for (int& cell : grid)
      cell = SOFT_BLACK;
  }

  public:
    App() {};

    ~App() {
      delete ant;
    }

    void setup() {
      setupSFML();
      setupProgram();
    }

    void run() {
      while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
          if (event.type == sf::Event::Closed)
              window.close();

          if (event.type == sf::Event::KeyReleased)
            switch (event.key.code) {
              case sf::Keyboard::Key::Q:
                window.close();
                break;
              default:
                break;
            }
        }

        window.clear(colors[SOFT_BLACK]);

        for (size_t step = 0; step < STEPS_PER_FRAME; step++) {
          const sf::Vector2i& antPos = ant->getPosition();
          int x = antPos.x / SCALE;
          int y = antPos.y / SCALE;
          int& cell = grid[x + y * ROWS];

          switch (cell) {
            case GRAY:
              ant->turnRight();
              cell = RED;
              break;
            case SOFT_BLACK:
              ant->turnRight();
              cell = RED;
              break;
            case RED:
              ant->turnRight();
              cell = GREEN;
              break;
            case GREEN:
              ant->turnLeft();
              cell = BLUE;
              break;
            case BLUE:
              ant->turnLeft();
              cell = YELLOW;
              break;
            case YELLOW:
              ant->turnLeft();
              cell = ORANGE;
              break;
            case ORANGE:
              ant->turnRight();
              cell = PURPLE;
              break;
            case PURPLE:
              ant->turnLeft();
              cell = MAGENTA;
              break;
            case MAGENTA:
              ant->turnLeft();
              cell = CYAN;
              break;
            case CYAN:
              ant->turnLeft();
              cell = RUBBY_PINK;
              break;
            case RUBBY_PINK:
              ant->turnLeft();
              cell = BROWN;
              break;
            case BROWN:
              ant->turnLeft();
              cell = LIME;
              break;
            case LIME:
              ant->turnLeft();
              cell = LIGHT_BLUE;
              break;
            case LIGHT_BLUE:
              ant->turnLeft();
              cell = YUKON_GOLD;
              break;
            case YUKON_GOLD:
              ant->turnLeft();
              cell = SCIENCE_BLUE;
              break;
            case SCIENCE_BLUE:
              ant->turnLeft();
              cell = GRAY;
              break;
          }

          // A rectangle with color to draw
          sf::RectangleShape rect;
          rect.setSize(sf::Vector2f(SCALE, SCALE));
          rect.setPosition(antPos.x, antPos.y);
          rect.setFillColor(colors[grid[x + y * ROWS]]);

          // Draw the rectangle on the render texture
          renderTexture.draw(rect);
          ant->move();
        }

        antStepsText.setString(formatWithDots(ant->getSteps()));

        renderTexture.display();

        window.draw(canvasSprite);
        window.draw(iterTitle);
        window.draw(antStepsText);

        // end the current frame
        window.display();
      }
    }
};

