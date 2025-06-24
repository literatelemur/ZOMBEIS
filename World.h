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

        std::vector<std::vector<double>> floor_sphere_points_3D;

        World(Graphics* graphics); // Constructor

        void render(Graphics* graphics);
        
};

#endif