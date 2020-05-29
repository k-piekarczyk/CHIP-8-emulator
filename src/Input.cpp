//
// Created by Krzysiek on 02.04.2020.
//

#include "Input.hpp"

Input::Input(unsigned char *keys, sf::RenderWindow *window) : keys(keys), window(window) {}

void Input::update() {
    sf::Event event{};
    while (window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;

            case sf::Event::KeyPressed:
                handleKeyPressedEvents(event);
                break;

            case sf::Event::KeyReleased:
                handleKeyReleasedEvents(event);
                break;
            default:
                break;
        }
    }
}

void Input::await() {
    sf::Event event{};
    do {
        window->waitEvent(event);
        if (event.type == sf::Event::Closed){
            window->close();
            break;
        }
    }
    while (!(event.type == sf::Event::KeyPressed && handleKeyPressedEvents(event)));
}

bool Input::handleKeyPressedEvents(sf::Event &event) {
    if (event.key.code == sf::Keyboard::Escape) {
        window->close();
        return true;
    }
    else
        for (int i = 0; i < 0x10; i++) {
            if (event.key.code == keyMap[i]) {
                keys[i] = 0xFF;
                return true;
            }
        }

    return false;
}

bool Input::handleKeyReleasedEvents(sf::Event &event) {
    for (int i = 0; i < 0x10; i++)
        if (event.key.code == keyMap[i]) {
            keys[i] = 0;
            return true;
        }

    return false;
}