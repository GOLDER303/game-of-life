#include <SDL2/SDL.h>
#include <iostream>

#include "Application.hpp"

int main(int argv, char **args)
{
    Application application;

    application.init();
    application.run();
    application.clean();

    return 0;
}
