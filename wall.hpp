#ifndef WALL_HPP
#define WALL_HPP

#include <vector>

class Line {
    private:
        std::vector<int> coordinates;
    public:
        static int startx;
        static int starty;
        static int endx;
        static int endy;
        Line(int a, int b, int c, int d);
        const std::vector<int>& getCoordinates();
};

#endif