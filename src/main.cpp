//#include <iostream>
//#include "CHIP8.h"
//#include "Graphics.h"
//#include "Input.h"
//#include "Beeper.h"
//#include "Timer.h"
//
//int main(int argc, char **argv) {
//    CHIP8 chip;
//
//    chip.initialize();
//
//    Graphics g = Graphics(chip.getGFX());
//    Input input = Input(chip.getKeys());
//
//    Beeper beeper = Beeper();
//    Timer soundTimer = Timer(*chip.getSoundTimerPtr(), &beeper);
//    Timer delayTimer = Timer(*chip.getDelayTimerPtr());
//
//    chip.loadRom("../roms/slipperyslope.ch8");
//
//    chip.loadInputHandler(&input);
//
//    while (!input.isFinished()) {
//
//        for(int i=0;i<30;i++) {
//            soundTimer.update();
//            delayTimer.update();
//
//            input.update();
//            chip.next();
//            g.draw();
//        }
//        SDL_Delay(2);
//    }
//
//    return 0;
//}

#include <iostream>
#include "SFML/Graphics.hpp"

int main(int argc, char ** argv){
    sf::RenderWindow renderWindow(sf::VideoMode(640, 480), "Thingie");

    sf::Event event;

    sf::CircleShape circleShape(200);
    circleShape.setFillColor(sf::Color::Blue);

    std::cout << "hello world!" << std::endl;

    while (renderWindow.isOpen()){
        while (renderWindow.pollEvent(event)){
            if (event.type == sf::Event::EventType::Closed)
                renderWindow.close();
        }

        renderWindow.clear();
        renderWindow.draw(circleShape);
        renderWindow.display();
    }
}

