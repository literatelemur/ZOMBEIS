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

        std::vector<std::vector<double>> rect_points_3D_body;

        Arrow(Graphics* graphics);

        void render_arrow(Graphics* graphics);

        void move(Graphics* graphics);
};

#endif
