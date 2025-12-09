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
#include "main.h"


World::World(Graphics* graphics, int x, int y, int z, std::vector<float> color){

    center_x = x;
    center_y = y;
    center_z = z;

    surface_color = color;

    gravity_dist = 5000;

    floor_sphere_points_3D = graphics->make_sphere({(double)center_x, (double)center_y, (double)center_z}, 1000, 12);


}

void World::render(Graphics* graphics){

    std::vector<std::vector<double>> ordered_sphere_points_3D = graphics->order_sphere_points(floor_sphere_points_3D);
    std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> floor_sphere_triangle_points_3D = graphics->find_triangle_points_sphere(ordered_sphere_points_3D);
    std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>>> clipped_floor_sphere_triangle_points_3D_as_lines = graphics->clip_triangle_points_sphere(floor_sphere_triangle_points_3D);
    std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<int>>>>>> clipped_floor_sphere_triangle_points_2D_as_lines = graphics->compute_2D_sphere_triangles_as_lines(clipped_floor_sphere_triangle_points_3D_as_lines);

    graphics->set_color(0, 0, 0);

    graphics->draw_full_triangles_sphere_as_lines(clipped_floor_sphere_triangle_points_2D_as_lines);


    graphics->set_color(surface_color[0], surface_color[1], surface_color[2]);

    graphics->draw_hollow_triangles_sphere_as_lines(clipped_floor_sphere_triangle_points_2D_as_lines);


    // Drawing floor lines

    std::vector<std::vector<std::vector<std::vector<double>>>> floor_points_3D = graphics->find_floor_lines_on_globe(floor_sphere_triangle_points_3D);

    std::vector<std::vector<std::vector<std::vector<double>>>> clipped_floor_points_3D = graphics->clip_sphere_lines(floor_points_3D);

    std::vector<std::vector<std::vector<std::vector<int>>>> clipped_floor_points_2D = graphics->compute_2D_sphere_lines(clipped_floor_points_3D);

    graphics->draw_floor_lines(clipped_floor_points_2D);
}