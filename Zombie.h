#include <SDL2/SDL.h>
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

        Zombie(Graphics graphics, int x, int y, int z); // Constructor

        void render_zombie(Graphics graphics);


        int x;
        int y;
        int z;
        int speed;

        std::vector<std::vector<double>> sphere_points_3D_head;
        std::vector<std::vector<double>> rect_points_3D_body;
        std::vector<std::vector<double>> rect_points_3D_arm1;
        std::vector<std::vector<double>> rect_points_3D_arm2;
        std::vector<std::vector<double>> rect_points_3D_leg1;
        std::vector<std::vector<double>> rect_points_3D_leg2;
};

#endif // zombie_H
