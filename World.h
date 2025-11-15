#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <list>


#ifndef world_H
#define world_H

class Graphics;

class World {

    public:

        int center_x;
        int center_y;
        int center_z;
        int gravity_dist;

        std::vector<float> surface_color;

        std::vector<std::vector<double>> floor_sphere_points_3D;

        World(Graphics* graphics, int x, int y, int z, std::vector<float> surface_color); // Constructor

        void render(Graphics* graphics);
        
};

#endif