#include "Controller.h"

void Controller::run() {
    m_level.buildLevel(m_my_board);

    std::cout << m_level.getRows() << std::endl;
    std::cout << m_level.getCols() << std::endl;

    sf::RenderWindow window(sf::VideoMode(PIXELS * m_level.getCols(), PIXELS * m_level.getRows()), "Pacman Game");

    while (window.isOpen()) {
        window.clear(DarkBlue);
        m_level.draw(window);

        if (auto event = sf::Event{}; window.waitEvent(event))
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
            }
        window.display();
    }
}