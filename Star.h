#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>


#ifndef star_H
#define star_H

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

        std::vector<std::vector<double>> rect_points_3D_body;

        Star(Graphics* graphics, double x, double y, double z, int lower_bound, int upper_bound);

        void render(Graphics* graphics);

        void move(Graphics* graphics);
};

#endif