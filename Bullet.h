#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

#include "Triangle.h"

#ifndef BULLET_H
#define BULLET_H

class Graphics;

class Bullet {

    public:


        int count;
        int origin_x;
        int origin_y;
        int origin_z;
        int center_x;
        int center_y;
        int center_z;
        double anglex;
        double angley;
        int depth;

        std::vector<std::vector<double>> box_points_3D;
        std::vector<Triangle> box_triangles_3D;

        Bullet(Graphics* graphics, int x, int y);

        void render(Graphics* graphics);

        void move(Graphics* graphics);
};

#endif
