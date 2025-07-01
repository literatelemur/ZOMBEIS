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
class World;

class Zombie {

    public:

        int center_x;
        int center_y;
        int center_z;
        int speed;
        int leg_angle1;
        int leg_angle2;
        int leg_inner_dir;
        int arm_phase;

        int leg_length;
        int leg_depth;
        double pi;

        std::vector<std::vector<double>> sphere_points_3D_head;
        std::vector<std::vector<double>> rect_points_3D_body;
        std::vector<std::vector<double>> rect_points_3D_arm1;
        std::vector<std::vector<double>> rect_points_3D_arm2;
        std::vector<std::vector<double>> rect_points_3D_leg1;
        std::vector<std::vector<double>> rect_points_3D_leg2;


        Zombie(Graphics* graphics, int given_x, int given_y, int given_z);

        void render(Graphics* graphics);

        void move(int dir);

        void gravitate(World world);

};

#endif
