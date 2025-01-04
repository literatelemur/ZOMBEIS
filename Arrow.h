#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>


#ifndef arrow_H
#define arrow_H

class Graphics;

class Arrow {

    public:


        int count;
        int origin_x;
        int origin_y;
        int origin_z;
        int z;
        double anglex;
        double angley;

        std::vector<std::vector<double>> rect_points_3D_body;

        Arrow(Graphics* graphics, int x, int y);

        void render_arrow(Graphics* graphics);

        void move(Graphics* graphics);
};

#endif
