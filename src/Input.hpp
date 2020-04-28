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

public:
    explicit Input(unsigned char * keys, sf::RenderWindow *window);

    void update();
    void await();

private:
    bool handleKeyPressedEvents(sf::Event &event);
    bool handleKeyReleasedEvents(sf::Event &event);


};


#endif //PROJEKT_INDYWIDUALNY_INPUT_HPP
