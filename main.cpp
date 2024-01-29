#include <exception>
#include <iostream>

#include "engine/engine.h"

int main(int argc, char* argv[])
{
    Engine engine(800, 600);

    try {
        engine.run();
    } catch (std::exception& e) {
        std::cout << e.what() << '\n';
        return 1;
    }


    return 0;
}
