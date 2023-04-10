#include <SDL2/SDL.h>

class Target {
    public:
        SDL_Rect box;
        Target(int x, int y) {
            box.x = x;
            box.y = y;
            box.w = 100;
            box.h = 100;
        }
};