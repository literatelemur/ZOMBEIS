#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <list>

#include "Triangle.h"

#ifndef WORLD_H
#define WORLD_H

class Graphics;

class World {

    public:

        int center_x;
        int center_y;
        int center_z;
        int gravity_dist;

        std::vector<float> surface_color;

        std::vector<std::vector<double>> sphere_points_3D;
        std::vector<Triangle> sphere_triangles_3D;

        World(Graphics* graphics, int x, int y, int z, std::vector<float> surface_color); // Constructor
        
};

#endif