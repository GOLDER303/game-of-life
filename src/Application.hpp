#pragma once

#include <SDL2/SDL.h>

class Application
{
public:
    Application();

    void init();
    void run();
    void handleEvents();

    void render();
    void clean();

private:
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    bool isRunning;
};