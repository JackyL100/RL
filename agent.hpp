#ifndef AGENT_HPP
#define AGENT_HPP
#include <SDL2/SDL.h>
#include "random.hpp"
#include "maze.hpp"

class Agent {
    private:
        SDL_Scancode keys[4];
        std::vector<Line> nearestWalls;
    public:
        enum class Move {
            UP, 
            DOWN,
            LEFT,
            RIGHT,
            UPLEFT,
            UPRIGHT,
            DOWNLEFT,
            DOWNRIGHT
        };
        SDL_Rect box;
        int y_speed;
        int x_speed;
        Agent(int x, int y, int w, int h);
        void move(const Uint8 *keyState, const Maze& map, SDL_Renderer* target);
        Move move();
        void render(SDL_Renderer* target); 
        void updateNearestWalls(const Maze& map);
};

#endif