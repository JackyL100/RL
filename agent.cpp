#include "agent.hpp"

Agent::Agent(int x, int y, int w, int h) {
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;
    keys[0] = SDL_SCANCODE_D;
    keys[1] = SDL_SCANCODE_A;
    keys[2] = SDL_SCANCODE_W; 
    keys[3] = SDL_SCANCODE_S;
    x_speed = 5;
    y_speed = 5;
}

void Agent::move(const Uint8* keyState, const Maze& map, SDL_Renderer* target) {
    if (keyState[keys[0]]) {
        box.x += x_speed;
    } else if (keyState[keys[1]]) {
        box.x -= x_speed;
    }
    if (keyState[keys[2]]) {
        box.y -= y_speed;
    } else if (keyState[keys[3]]) {
        box.y += y_speed;
    }
}

void Agent::render(SDL_Renderer* target) {
    SDL_SetRenderDrawColor(target, 255, 0, 0, 255);
    SDL_RenderDrawRect(target, &box);
    SDL_RenderFillRect(target, &box);
}

void Agent::updateNearestWalls(const Maze& map) {
    
}

Agent::Move move() {
    static std::uniform_int_distribution randomMove{1,8};
    switch (randomMove(Random::mt)) {
        case 1:
            return Agent::Move::DOWN;
        case 2:
            return Agent::Move::UP;
        case 3:
            return Agent::Move::LEFT;
        case 4:
            return Agent::Move::RIGHT;
        case 5:
            return Agent::Move::UPLEFT;
        case 6:
            return Agent::Move::UPRIGHT;
        case 7:
            return Agent::Move::DOWNRIGHT;
        case 8:
            return Agent::Move::DOWNLEFT;
        default:
            return Agent::Move::UP;
    }
}