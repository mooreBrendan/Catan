#include "main.hpp"

using namespace CATAN;

int main() {
  sf::Mouse mouse;
  sf::RenderWindow window(sf::VideoMode(640, 480), "Catan");
  sf::View view = window.getView();
  sf::CircleShape temp(80, 6);
  DEBUG_MSG("done sfml init");

  // create game object & setup
  Game g;
  DEBUG_MSG("done game init");

  // prompt users for initial setup
  g.playerBoardSetup();

  // handle turns until game over
  while (!g.isOver() && window.isOpen()) {
    // reset variables
    sf::Event event;
    DEBUG_MSG("main loop");

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {  // check if window is closed
        window.close();                       // actually close the window
      } else if (event.type == sf::Event::MouseButtonPressed) {  // check mouse
        if (event.mouseButton.button == sf::Mouse::Left) {  // check left mouse
          // TODO: handle mouse press
        }
      } else if (event.type == sf::Event::Resized) {  // check resize
        sf::Vector2f resize(event.size.width, event.size.height);

        // set minimum size
        resize.x = resize.x < MIN_X_SIZE ? MIN_X_SIZE : resize.x;
        resize.y = resize.y < MIN_Y_SIZE ? MIN_Y_SIZE : resize.y;

        // resize the window to min size and center window
        window.setSize(sf::Vector2u(resize.x, resize.y));
        view.setSize(resize);
        view.setCenter(resize.x / 2.0f, resize.y / 2.0f);
        DEBUG_MSG("resize: x: " << resize.x << ", y: " << resize.y);
        window.setView(view);
      }
    }
    DEBUG_MSG("event loop done");

    // DEBUG: uncomment
    // g.run();

    if (window.isOpen()) {
      window.clear();
      // TODO: game draw
      window.draw(temp);
      window.display();
    }
  }
  DEBUG_MSG("out of main loop");

  // display who won
  g.handleWinner();
  return 0;
}