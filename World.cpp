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


World::World(Graphics* graphics){

    // center_x = graphics->playerx;
    // center_y = graphics->playery + 1500;
    // center_z = graphics->playerz + 1500;

    center_x = 960;
    center_y = 1060 + 1500;
    center_z = 1000 + 1500;

    gravity_dist = 5000;

    floor_sphere_points_3D = graphics->make_sphere({(double)center_x, (double)center_y, (double)center_z}, 1000, 12);
    //floor_sphere_points_3D = make_sphere({(double)playerx, (double)playery + 5000, (double)playerz + 15000}, 5000, 12);
    //floor_sphere_points_3D = make_sphere({(double)960, (double)560, (double)5000}, 1000, 12);


}

void World::render(Graphics* graphics){

    std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> floor_sphere_triangle_points_3D = graphics->find_triangle_points_sphere(floor_sphere_points_3D);
    std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>>> clipped_floor_sphere_triangle_points_3D_as_lines = graphics->clip_triangle_points_sphere(floor_sphere_triangle_points_3D);
    std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<int>>>>>> clipped_floor_sphere_triangle_points_2D_as_lines = graphics->compute_2D_sphere_triangles_as_lines(clipped_floor_sphere_triangle_points_3D_as_lines);

    graphics->set_color(0.0f, 0.0f, 0.0f);

    //graphics->draw_full_triangles_sphere(floor_sphere_triangle_points_2D);


    graphics->set_color(1.0f, 0.0f, 0.0f);

    graphics->draw_hollow_triangles_sphere_as_lines(clipped_floor_sphere_triangle_points_2D_as_lines);


    // Drawing floor lines

    std::vector<std::vector<std::vector<std::vector<double>>>> floor_points_3D = graphics->find_floor_lines_on_globe(floor_sphere_triangle_points_3D);

    std::vector<std::vector<std::vector<std::vector<int>>>> floor_points_2D = graphics->clip_and_compute_2D_sphere_lines(floor_points_3D);

    graphics->draw_floor_lines(floor_points_2D);
}