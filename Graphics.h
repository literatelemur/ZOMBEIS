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
        

        std::vector<std::vector<double>> floor_sphere_points_3D;

        std::vector<std::vector<std::vector<std::vector<double>>>> test_points_3D;

        Graphics(); // Constructor

        std::vector<std::vector<double>> make_sphere(std::vector<double> center, int radius, int num_points);

        std::vector<std::vector<double>> make_box(std::vector<double> center, double top_length, double side_length, double depth);
        
        std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> find_triangle_points_sphere(std::vector<std::vector<double>> sphere_points_3D);

        std::vector<std::vector<std::vector<std::vector<double>>>> find_floor_lines_on_globe(std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> floor_points_3D);

        std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> order_sphere_triangle_points(std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> sphere_triangle_points_3D);

        std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>>> clip_triangle_points_sphere(std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> triangle_points_3D_sphere);

        std::vector<std::vector<std::vector<std::vector<double>>>> clip_sphere_lines(std::vector<std::vector<std::vector<std::vector<double>>>> lines_points_3D);

        std::vector<std::vector<std::vector<double>>> clip_box(std::vector<std::vector<double>> box_points_3D);

        std::vector<double> clip_3D_line(std::vector<std::vector<double>> line_points_3D);

        std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<int>>>>>> compute_2D_sphere_triangles_as_lines(std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>>> triangle_points);

        std::vector<std::vector<std::vector<std::vector<int>>>> compute_2D_sphere_lines(std::vector<std::vector<std::vector<std::vector<double>>>> clipped_lines_points_3D);

        std::vector<std::vector<std::vector<int>>> compute_2D_box_as_lines(std::vector<std::vector<std::vector<double>>> clipped_box_points_3D);

        std::vector<int> compute_2D_point(std::vector<double> point_3D);

        void clear_draw_screen();

        void draw_full_triangles_sphere_as_lines(std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<int>>>>>> sphere_triangle_points_2D_as_lines);

        void draw_hollow_triangles_sphere_as_lines(std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<int>>>>>> triangle_points_as_lines);

        void draw_floor_lines(std::vector<std::vector<std::vector<std::vector<int>>>> floor_points_2D);

        void draw_full_box_as_lines(std::vector<std::vector<std::vector<int>>> clipped_box_points_2D);

        void draw_hollow_box_as_lines(std::vector<std::vector<std::vector<int>>> clipped_box_points_2D);

        void draw_hud();

        void set_color(int r, int g, int b);

        void present_frame();
        
};

#endif // graphics_H