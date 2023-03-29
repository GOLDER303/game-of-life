#include <SDL2/SDL.h>
#include <iostream>
#include <time.h>

#include "Application.hpp"

int main(int argv, char **args)
{
    srand(time(nullptr));

    Application application;

    application.init();
    application.run();
    application.clean();

    return 0;
}
