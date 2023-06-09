#ifndef MAZE_HPP
#define MAZE_HPP

#include "wall.hpp"
#include <SDL2/SDL.h>
#include <vector>
#include <fstream>
#include <iostream>

class Maze {
    private:
        std::vector<Line> map;
    public:
        bool check_crossed(SDL_Rect agent) {
            for (Line wall: map) {
                if (SDL_IntersectRectAndLine(&agent, &wall.startx, &wall.starty, &wall.endx, &wall.endy) == SDL_TRUE) {
                    return true;
                }
            }
            return false;
        }
        void load(std::string filePath) {
            std::ifstream file{filePath};
            if (!file) {std::cout << "file could not be opened";}
            while(file) {
                std::string line;
                std::getline(file, line);
                map.emplace_back(std::stoi(line.substr(0,2)), std::stoi(line.substr(2,4)), std::stoi(line.substr(4,6)), std::stoi(line.substr(6,8)));
            }
        }
        void render(SDL_Renderer* target) {
            SDL_SetRenderDrawColor(target, 255, 0, 255, 255);
            for (auto& wall : map) {
                SDL_RenderDrawLine(target, wall.getCoordinates()[0], wall.getCoordinates()[1], wall.getCoordinates()[2], wall.getCoordinates()[3]);
            }
        }
};

#endif