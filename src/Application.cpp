#include "Application.hpp"

Application::Application()
    : isRunning(true), window(nullptr), renderer(nullptr)
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
        window = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
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
}

void Application::run()
{
    while (isRunning)
    {
        handleEvents();
        render();
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
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);

    SDL_RenderPresent(renderer);
}

void Application::clean()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
