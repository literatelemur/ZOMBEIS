#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

//#include "Graphics.h"

#ifndef zombie_H
#define zombie_H

class Graphics;

class Zombie {

    public:

        int speed;

        std::vector<std::vector<double>> sphere_points_3D_head;
        std::vector<std::vector<double>> rect_points_3D_body;
        std::vector<std::vector<double>> rect_points_3D_arm1;
        std::vector<std::vector<double>> rect_points_3D_arm2;
        std::vector<std::vector<double>> rect_points_3D_leg1;
        std::vector<std::vector<double>> rect_points_3D_leg2;


        Zombie(Graphics* graphics, int given_x, int given_y, int given_z);

        void render(Graphics* graphics);

        void move(int dir);
};

#endif
