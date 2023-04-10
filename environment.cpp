#include "agent.hpp"
#include "target.hpp"
#include "maze.hpp"
#include <SDL2/SDL.h>
#include <iostream>

const int WIDTH = 960;
const int HEIGHT = 640;

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Environment", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderTarget = nullptr;
    renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (window == nullptr) 
    {
        std::cout << "COULD NOT CREATE WINDOW\n";
        return 1;
    }
    std::string mapFilePath;
    std::cout << "Enter map to load: ";
    std::cin >> mapFilePath;
    Maze environment;
    environment.load(mapFilePath);
    SDL_Event windowEvent;
    Agent bear(100,500,100,100);
    bool quit = false;
    const Uint8* keyState;
    while (!quit){
        if (SDL_PollEvent(&windowEvent)){
            if (windowEvent.type == SDL_QUIT){
                quit = true;
            } 
        }
        keyState = SDL_GetKeyboardState(NULL);
        bear.move(keyState, environment, renderTarget);
        SDL_SetRenderDrawColor(renderTarget, 255, 255, 255, 255);
        SDL_RenderClear(renderTarget);
        bear.render(renderTarget);
        SDL_RenderPresent(renderTarget);
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderTarget);
    window = nullptr;
    renderTarget = nullptr;
    SDL_Quit();
}