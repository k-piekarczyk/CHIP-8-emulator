//
// Created by Krzysiek on 02.04.2020.
//

#ifndef PROJEKT_INDYWIDUALNY_INPUT_HPP
#define PROJEKT_INDYWIDUALNY_INPUT_HPP

#include <iostream>

#include <SFML/Graphics.hpp>

class Input {
    unsigned char * keys;
    sf::RenderWindow *window;
    sf::Keyboard::Key keyMap[0x10] = {
        sf::Keyboard::X,
        sf::Keyboard::Num1,
        sf::Keyboard::Num2,
        sf::Keyboard::Num3,
        sf::Keyboard::Q,
        sf::Keyboard::W,
        sf::Keyboard::E,
        sf::Keyboard::A,
        sf::Keyboard::S,
        sf::Keyboard::D,
        sf::Keyboard::Z,
        sf::Keyboard::C,
        sf::Keyboard::Num4,
        sf::Keyboard::R,
        sf::Keyboard::F,
        sf::Keyboard::V
    };

public:
    explicit Input(unsigned char * keys, sf::RenderWindow *window);

    void update();
    void await();

private:
    bool handleKeyPressedEvents(sf::Event &event);
    bool handleKeyReleasedEvents(sf::Event &event);


};


#endif //PROJEKT_INDYWIDUALNY_INPUT_HPP
