#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

#include "Triangle.h"


#ifndef STAR_H
#define STAR_H

class Graphics;

class Star {

    public:


        int count;
        int origin_x;
        int origin_y;
        int origin_z;
        double x;
        double y;
        double z;
        double anglex;
        double angley;
        int depth;

        int upper_bound;
        int lower_bound;
        int osc;
        int y_wait;
        double y_move;

        std::vector<std::vector<double>> box_points_3D;
        std::vector<Triangle> box_triangles_3D;

        Star(Graphics* graphics, double x, double y, double z, int lower_bound, int upper_bound);

        void find_movement_value(Graphics* graphics);

        void move(Graphics* graphics);
};

#endif