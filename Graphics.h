#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <list>


#ifndef graphics_H
#define graphics_H

class Graphics {

    public:

        int zscreendiff;
        int playerx;
        int playery;
        int playerz;
        double near_plane;

        double anglex_diff;
        double angley_diff;
        double pi;

        std::vector<std::vector<double>> floor_sphere_points_3D;

        std::vector<std::vector<std::vector<std::vector<double>>>> test_points_3D;

        Graphics(); // Constructor

        std::vector<std::vector<double>> make_sphere(std::vector<double> center, int radius, int num_points);

        std::vector<std::vector<double>> make_box(std::vector<double> center, double top_length, double side_length, double depth);

        std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> find_triangle_points_sphere(std::vector<std::vector<double>> sphere_points_3D);

        std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>>> clip_triangle_points_sphere(std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> triangle_points_sphere);

        std::vector<std::vector<std::vector<std::vector<double>>>> find_floor_lines_on_globe(std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> floor_points_3D);

        std::vector<std::vector<std::vector<std::vector<int>>>> clip_and_compute_2D_sphere_lines(std::vector<std::vector<std::vector<std::vector<double>>>> lines_points_3D);

        std::vector<int> compute_2D_point(std::vector<double> point_3D);

        std::vector<double> clip_3D_line(std::vector<std::vector<double>> line_points_3D);

        std::vector<std::vector<int>> compute_2D_box(std::vector<std::vector<double>> rect_points_3D);

        std::vector<std::vector<std::vector<std::vector<std::vector<int>>>>> compute_2D_sphere_triangles(std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> triangle_points);

        std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<int>>>>>> compute_2D_sphere_triangles_as_lines(std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>>> triangle_points);

        void clear_draw_screen();

        void draw_horizon();

        void draw_floor_lines(std::vector<std::vector<std::vector<std::vector<int>>>> floor_points_2D);

        void draw_full_triangles_sphere(std::vector<std::vector<std::vector<std::vector<std::vector<int>>>>> triangle_points);

        void draw_hollow_triangles_sphere(std::vector<std::vector<std::vector<std::vector<std::vector<int>>>>> triangle_points);

        void draw_hollow_triangles_sphere_as_lines(std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<int>>>>>> triangle_points_as_lines);

        void draw_full_box(std::vector<std::vector<int>> rect_points);

        void draw_full_polygon(std::vector<std::vector<int>> polygon_points_2D);

        void draw_hollow_polygon(std::vector<std::vector<int>> polygon_points_2D);

        void draw_hollow_box(std::vector<std::vector<int>> rect_points);

        void set_color(int r, int g, int b);

        void present_frame();

        void test();
        
};

#endif // graphics_H