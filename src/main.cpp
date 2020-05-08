#include <fstream>
#include <string>
#include "Runner.hpp"

int main(int argc, char **argv) {
    bool delay = false;

    if (argc > 1) {
        std::ifstream rom = std::ifstream(argv[1], std::ios_base::binary);

        if (argc > 2) {
            std::string arg = argv[2];
            if (arg == "--delay") delay = true;
        }

        if(rom.good()) {
            Runner runner(rom, delay);
            runner.start();
        } else {
            std::cout << "Unable to open \"" << argv[1] << "\"!"<< std::endl;
        }
    } else {
        std::cout << "Diagnostic run here" << std::endl;
    }

    return 0;
}

