//
// Created by Krzysiek on 01.04.2020.
//

#ifndef PROJEKT_INDYWIDUALNY_GRAPHICS_H
#define PROJEKT_INDYWIDUALNY_GRAPHICS_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include "spec.hpp"

class Display {
    unsigned char *frame;
    sf::Color backgroundColor = sf::Color::Black;
    sf::Color foregroundColor = sf::Color::White;

public:
    sf::RenderWindow *window;

    explicit Display(unsigned char *gfx);

    ~Display();

    void draw();
};


#endif //PROJEKT_INDYWIDUALNY_GRAPHICS_H
