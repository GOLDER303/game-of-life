#pragma once

#include <SDL2/SDL.h>
#include <vector>

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
    void populateGrid();
    void drawGrid();

private:
    int gridCellSize = 10;
    int gridWidth = 60;
    int gridHeight = 50;

    const int WINDOW_WIDTH;
    const int WINDOW_HEIGHT;

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    bool isRunning;

    SDL_Color gridBackground = {22, 22, 22, 255};
    SDL_Color gridLineColor = {44, 44, 44, 255};

    std::vector<std::vector<int>> grid;
};