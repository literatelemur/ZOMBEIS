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


        double origin_x;
        double origin_y;
        double origin_z;

        double center_x;
        double center_y;
        double center_z;

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
