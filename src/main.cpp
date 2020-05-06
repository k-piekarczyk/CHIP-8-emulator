#include <fstream>
#include "Runner.hpp"

int main(int argc, char **argv) {

    if (argc > 1) {
        std::ifstream rom = std::ifstream(argv[1], std::ios_base::binary);

        Runner runner(rom);
        runner.start();
    } else {
        std::cout << "Diagnostic run here" << std::endl;
    }

    return 0;
}

