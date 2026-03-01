#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

#include "Triangle.h"
#include "Camera.h"

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
        double speed;

        double center_x_move;
        double center_y_move;
        double center_z_move;

        std::vector<std::vector<double>> box_points_3D;
        std::vector<Triangle> box_triangles_3D;

        Bullet(Graphics* graphics, Camera* camera, int x, int y);

        void move();
};

#endif
