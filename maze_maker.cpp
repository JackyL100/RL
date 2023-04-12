#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <fstream>
#include "wall.hpp"

const int WIDTH = 960;
const int HEIGHT = 640;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Environment", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderTarget = nullptr;
    renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (window == nullptr) 
    {
        std::cout << "COULD NOT CREATE WINDOW\n";
        return 1;
    }
    
    SDL_Event windowEvent;
    bool quit = false;
    bool creatingLine = false;
    const Uint8* keyState;
    int mouseX, mouseY;
    std::vector<Line> mazeLines;
    mazeLines.push_back(Line(100,100,200,200));
    while (!quit){
        if (SDL_PollEvent(&windowEvent)){
            if (windowEvent.type == SDL_QUIT){
                quit = true;
            } else if (windowEvent.type == SDL_MOUSEBUTTONDOWN) {
                creatingLine = !creatingLine;
                if (creatingLine) {
                    SDL_GetMouseState(&Line::startx, &Line::starty);
                } else {
                    SDL_GetMouseState(&Line::endx, &Line::endy);
                    //mazeLines.push_back(new Line(Line::startx, Line::starty, Line::endx, Line::endy));
                    mazeLines.push_back(Line(Line::startx, Line::starty, Line::endx, Line::endy));
                    std::cout << Line::startx << " " << Line::starty << " " << Line::endx << " " << Line::endy << "\n";
                    creatingLine = false;
                }
            } else if (windowEvent.type == SDL_KEYDOWN) {
                switch(windowEvent.key.keysym.sym) {
                    case SDLK_s:{
                        std::ofstream map{"map.txt"};
                        for (int i = 0; i < mazeLines.size(); i++) {
                            //map << mazeLines[i].startx << " " << mazeLines[i].starty << " " << mazeLines[i].endx << " " << mazeLines[i].endy << "\n";
                            for (int coor : mazeLines[i].getCoordinates()) {
                                map << coor << " ";
                            }
                            map << "\n";
                        }
                        quit = true;
                        map.close();
                        break;
                    }
                    case SDLK_SPACE:
                        for (auto line : mazeLines) {
                            for (int i : line.getCoordinates()) {
                                std::cout << i << " ";
                            }
                            std::cout << "\n";
                        }
                        break;
                }
            }
        }
        SDL_SetRenderDrawColor(renderTarget, 255, 255, 255, 255);
        SDL_RenderClear(renderTarget);
        SDL_SetRenderDrawColor(renderTarget, 255, 0, 255, 255);
        for (auto l : mazeLines) {
            SDL_RenderDrawLine(renderTarget, l.getCoordinates()[0], l.getCoordinates()[1], l.getCoordinates()[2], l.getCoordinates()[3]);
        }
        if (creatingLine) {
            SDL_GetMouseState(&mouseX, &mouseY);
            SDL_RenderDrawLine(renderTarget, Line::startx, Line::starty, mouseX, mouseY);
        }
        SDL_RenderPresent(renderTarget);
    }
    /*for (auto& l: mazeLines) {
        delete l;
        l = nullptr;
    }*/
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderTarget);
    window = nullptr;
    renderTarget = nullptr;
    SDL_Quit();
}