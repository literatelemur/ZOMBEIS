#include <GL/glut.h>
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <list>

#include "World.h"
#include "Graphics.h"
#include "Triangle.h"


World::World(Graphics* graphics, int x, int y, int z, std::vector<double> color){

    center_x = x;
    center_y = y;
    center_z = z;

    surface_color = color;

    gravity_dist = 5000;

    sphere_points_3D = graphics->make_sphere({(double)center_x, (double)center_y, (double)center_z}, 1000, 12);

}