#include "wall.hpp"

int Line::startx = 0;
int Line::starty = 0;
int Line::endx = 0;
int Line::endy = 0;

Line::Line(int a, int b, int c, int d) {
    coordinates = std::vector<int>(4);
    coordinates[0] = a;
    coordinates[1] = b;
    coordinates[2] = c;
    coordinates[3] = d;
}

const std::vector<int>& Line::getCoordinates() {
    return coordinates;
}