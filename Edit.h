#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <list>

#include "Triangle.h"

#ifndef EDIT_H
#define EDIT_H

class Graphics;
class main;

class Edit {

    public:

        // int center_x;
        // int center_y;
        // int center_z;
        // int gravity_dist;

        // std::vector<double> surface_color;

        // std::vector<std::vector<double>> sphere_points_3D;
        // std::vector<Triangle> sphere_triangles_3D;

        //World(Graphics* graphics, int x, int y, int z, std::vector<double> surface_color); // Constructor


        static bool edit_mode;

        static std::vector<std::vector<double>> points_3D;

        static int points_3D_main_index;
        static int points_3D_sub1_index;
        static int points_3D_sub2_index;

        static std::vector<std::vector<std::vector<double>>> points_points_3D;

        static std::vector<Triangle> triangles_3D;

        static std::string edit_click_mouse_button;

        static bool first_click_move;
        static double prev_anglex_diff;
        static double prev_angley_diff;

        static bool edit_draw_points;
        

        static void toggle_edit_mode();

        static void move_point(int coor, int dir);

        static void click_point(Graphics* graphics);

        static void move_point_with_mouse(Graphics* graphics);

        Edit() = delete;
        
};

#endif