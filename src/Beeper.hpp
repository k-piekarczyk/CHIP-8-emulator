//
// Created by Krzysiek on 02.04.2020.
//

#ifndef PROJEKT_INDYWIDUALNY_BEEPER_H
#define PROJEKT_INDYWIDUALNY_BEEPER_H

#include <SFML/Audio.hpp>
#include <cmath>
#include <iostream>

class Beeper {
    sf::Sound sound;
    sf::SoundBuffer buffer;

public:
    Beeper();

    ~Beeper();

    void start();

    void stop();
};


#endif //PROJEKT_INDYWIDUALNY_BEEPER_H
