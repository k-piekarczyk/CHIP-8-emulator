//
// Created by Krzysiek on 01.04.2020.
//


#include "Display.hpp"

Display::Display(unsigned char *gfx) : frame(gfx) {
    window = new sf::RenderWindow(
            sf::VideoMode(Spec::H_SIZE * Spec::SCALE, Spec::V_SIZE * Spec::SCALE),
            "8mu", sf::Style::Close | sf::Style::Titlebar);
}

Display::~Display() {
    frame = nullptr;
    window->close();
}

void Display::draw() {
    window->clear(backgroundColor);

    sf::RectangleShape pixel(sf::Vector2f(Spec::SCALE, Spec::SCALE));
    pixel.setFillColor(foregroundColor);

    for (int y = 0; y < Spec::V_SIZE; y++) {
        for (int x = 0; x < Spec::H_SIZE; x++) {

            if (frame[(y * Spec::H_SIZE) + x]) {
                pixel.setPosition(x * Spec::SCALE, y * Spec::SCALE);
                window->draw(pixel);
            }
        }
    }

    window->display();
}