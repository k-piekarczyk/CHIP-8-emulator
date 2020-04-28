//
// Created by Krzysiek on 02.04.2020.
//

#include "Input.hpp"

Input::Input(unsigned char * keys, sf::RenderWindow *window) : keys(keys), window(window) {}

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
    do window->waitEvent(event);
    while(!handleKeyPressedEvents(event));
}

bool Input::handleKeyPressedEvents(sf::Event &event) {
    bool legalKey = true;

    switch (event.key.code) {
        case sf::Keyboard::Escape:
            window->close();
            break;
        case sf::Keyboard::Num1:
            keys[0x1] = 0xFF;
            break;
        case sf::Keyboard::Num2:
            keys[0x2] = 0xFF;
            break;
        case sf::Keyboard::Num3:
            keys[0x3] = 0xFF;
            break;
        case sf::Keyboard::Num4:
            keys[0xC] = 0xFF;
            break;
        case sf::Keyboard::Q:
            keys[0x4] = 0xFF;
            break;
        case sf::Keyboard::W:
            keys[0x5] = 0xFF;
            break;
        case sf::Keyboard::E:
            keys[0x6] = 0xFF;
            break;
        case sf::Keyboard::R:
            keys[0xD] = 0xFF;
            break;
        case sf::Keyboard::A:
            keys[0x7] = 0xFF;
            break;
        case sf::Keyboard::S:
            keys[0x8] = 0xFF;
            break;
        case sf::Keyboard::D:
            keys[0x9] = 0xFF;
            break;
        case sf::Keyboard::F:
            keys[0xE] = 0xFF;
            break;
        case sf::Keyboard::Z:
            keys[0xA] = 0xFF;
            break;
        case sf::Keyboard::X:
            keys[0x0] = 0xFF;
            break;
        case sf::Keyboard::C:
            keys[0xB] = 0xFF;
            break;
        case sf::Keyboard::V:
            keys[0xF] = 0xFF;
            break;
        default:
            legalKey = false;
            break;
    }

    return legalKey;
}

bool Input::handleKeyReleasedEvents(sf::Event &event) {
    bool legalKey = true;

    switch (event.key.code) {
        case sf::Keyboard::Num1:
            keys[0x1] = 0;
            break;
        case sf::Keyboard::Num2:
            keys[0x2] = 0;
            break;
        case sf::Keyboard::Num3:
            keys[0x3] = 0;
            break;
        case sf::Keyboard::Num4:
            keys[0xC] = 0;
            break;
        case sf::Keyboard::Q:
            keys[0x4] = 0;
            break;
        case sf::Keyboard::W:
            keys[0x5] = 0;
            break;
        case sf::Keyboard::E:
            keys[0x6] = 0;
            break;
        case sf::Keyboard::R:
            keys[0xD] = 0;
            break;
        case sf::Keyboard::A:
            keys[0x7] = 0;
            break;
        case sf::Keyboard::S:
            keys[0x8] = 0;
            break;
        case sf::Keyboard::D:
            keys[0x9] = 0;
            break;
        case sf::Keyboard::F:
            keys[0xE] = 0;
            break;
        case sf::Keyboard::Z:
            keys[0xA] = 0;
            break;
        case sf::Keyboard::X:
            keys[0x0] = 0;
            break;
        case sf::Keyboard::C:
            keys[0xB] = 0;
            break;
        case sf::Keyboard::V:
            keys[0xF] = 0;
            break;
        default:
            legalKey = false;
            break;
    }

    return legalKey;
}