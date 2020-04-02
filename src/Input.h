//
// Created by Krzysiek on 02.04.2020.
//

#ifndef PROJEKT_INDYWIDUALNY_INPUT_H
#define PROJEKT_INDYWIDUALNY_INPUT_H

class Input {
    unsigned char * keys;
    bool quit = false;

public:
    explicit Input(unsigned char * keys);

    void update();
    bool isFinished();

private:
    void clearKeys();
};


#endif //PROJEKT_INDYWIDUALNY_INPUT_H
