#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <list>

#include "Triangle.h"


#ifndef GRAPHICS_H
#define GRAPHICS_H

class Graphics {

    public:

        int zscreendiff;
        int playerx;
        int playery;
        int playerz;
        double near_plane;

        double anglex_diff;
        double angley_diff;

        std::vector<Triangle> all_triangles;
        

        std::vector<std::vector<double>> floor_sphere_points_3D;

        Graphics(); // Constructor

        std::vector<std::vector<double>> make_sphere(std::vector<double> center, int radius, int num_points);

        std::vector<std::vector<double>> make_box(std::vector<double> center, double top_length, double side_length, double depth);

        std::vector<Triangle> find_triangles_sphere(std::vector<std::vector<double>> sphere_points_3D);

        std::vector<Triangle> find_triangles_box(std::vector<std::vector<double>> box_points_3D);

        std::vector<Triangle> order_triangles(std::vector<Triangle> triangles);
        
        void store_all_triangles(std::vector<Triangle> all_triangles);

        void find_lines_on_triangles();

        std::vector<std::vector<std::vector<std::vector<double>>>> clip_triangles();

        std::vector<double> clip_line(std::vector<std::vector<double>> line_points_3D);

        std::vector<std::vector<std::vector<std::vector<double>>>> compute_2D_triangles_as_lines(std::vector<std::vector<std::vector<std::vector<double>>>> clipped_triangles_as_lines); 

        std::vector<double> compute_2D_point(std::vector<double> point_3D);

        void clear_draw_screen();

        void draw_triangles_as_lines(std::vector<std::vector<std::vector<std::vector<double>>>> triangles_2D_as_lines);

        void draw_hud();

        void set_color(int r, int g, int b);

        void present_frame();
        
};

#endif // graphics_H