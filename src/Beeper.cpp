//
// Created by Krzysiek on 02.04.2020.
//

#include "Beeper.hpp"


Beeper::Beeper() {
    const unsigned short SAMPLES = 44100;
    const unsigned short SAMPLE_RATE = 44100;
    const unsigned short AMPLITUDE = 30000;

    sf::Int16 raw[SAMPLES];

    const double TWO_PI = 6.28318;
    const double increment = 440./44100;
    double x = 0;

    for (unsigned short i = 0; i < SAMPLES; i++) {
        raw[i] = AMPLITUDE * sin(x*TWO_PI);
        x += increment;
    }

    if (!buffer.loadFromSamples(raw, SAMPLES, 1, SAMPLE_RATE)) {
        std::cerr << "Loading failed!" << std::endl;
        exit(EXIT_FAILURE);
    }

    sound.setBuffer(buffer);
    sound.setLoop(true);
}

void Beeper::start() {
    if (sound.getStatus() == sf::SoundSource::Status::Stopped)
        sound.play();
}

void Beeper::stop() {
    if (sound.getStatus() == sf::SoundSource::Status::Playing)
        sound.stop();
}
