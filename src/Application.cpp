#include "Application.hpp"

#include <iostream>

Application::Application()
    : isRunning(true), window(nullptr), renderer(nullptr), WINDOW_WIDTH((gridWidth * gridCellSize) + 1), WINDOW_HEIGHT((gridHeight * gridCellSize) + 1), grid(std::vector<std::vector<int>>(gridWidth, std::vector<int>(gridHeight, 0)))
{
}

void Application::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        isRunning = false;
    }
    else
    {
        window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
        if (window == nullptr)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            isRunning = false;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer == nullptr)
        {
            printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
            isRunning = false;
        }
    }

    populateGrid();
}

void Application::run()
{
    while (isRunning)
    {
        handleEvents();
        render();
        updateGrid();
    }
}

void Application::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;

        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                isRunning = false;
            }
        }
    }
}

void Application::render()
{
    SDL_RenderClear(renderer);

    drawGrid();

    SDL_RenderPresent(renderer);
}

void Application::clean()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Application::populateGrid()
{
    for (int i = 0; i < gridWidth; i++)
    {
        for (int j = 0; j < gridHeight; j++)
        {
            grid[i][j] = rand() % 2;
        }
    }
}

void Application::drawGrid()
{
    SDL_SetRenderDrawColor(renderer, gridBackground.r, gridBackground.g, gridBackground.b, gridBackground.a);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, gridLineColor.r, gridLineColor.g, gridLineColor.b, gridLineColor.a);

    for (int x = 0; x < 1 + (gridWidth * gridCellSize); x += gridCellSize)
    {
        SDL_RenderDrawLine(renderer, x, 0, x, WINDOW_HEIGHT);
    }

    for (int y = 0; y < 1 + gridHeight * gridCellSize; y += gridCellSize)
    {
        SDL_RenderDrawLine(renderer, 0, y, WINDOW_WIDTH, y);
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < gridWidth; i++)
    {
        for (int j = 0; j < gridHeight; j++)
        {
            if (grid[i][j])
            {
                SDL_Rect cellRect = {i * gridCellSize + 1, j * gridCellSize + 1, gridCellSize - 1, gridCellSize - 1};
                SDL_RenderFillRect(renderer, &cellRect);
            }
        }
    }
}

void Application::updateGrid()
{
    std::vector<std::vector<int>> updatedGrid(gridWidth, std::vector<int>(gridHeight, 0));

    for (int i = 0; i < gridWidth; i++)
    {
        for (int j = 0; j < gridHeight; j++)
        {
            int neighbors = countNeighbors(i, j);

            if (neighbors < 2)
            {
                updatedGrid[i][j] = 0;
            }
            else if (neighbors > 3)
            {
                updatedGrid[i][j] = 0;
            }
            else if (neighbors == 3 || (neighbors == 2 && grid[i][j]))
            {
                updatedGrid[i][j] = 1;
            }
        }
    }

    grid = updatedGrid;
}

int Application::countNeighbors(int x, int y)
{
    int neighbors = 0;

    for (int i = std::max(0, x - 1); i <= std::min(x + 1, gridWidth - 1); i++)
    {
        for (int j = std::max(0, y - 1); j <= std::min(y + 1, gridHeight - 1); j++)
        {
            neighbors += grid[i][j];
        }
    }

    return neighbors - grid[x][y];
}
