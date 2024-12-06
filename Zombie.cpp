#include <SDL2/SDL.h>
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

#include "Zombie.h"
#include "Graphics.h"

class Zombie {

    public:

        int x;
        int y;
        int z;
        int speed;

        std::vector<std::vector<double>> sphere_points_3D_head;
        std::vector<std::vector<double>> rect_points_3D_body;
        std::vector<std::vector<double>> rect_points_3D_arm1;
        std::vector<std::vector<double>> rect_points_3D_arm2;
        std::vector<std::vector<double>> rect_points_3D_leg1;
        std::vector<std::vector<double>> rect_points_3D_leg2;

        Zombie(Graphics graphics, int given_x, int given_y, int given_z){

            x = given_x;
            y = given_y;
            z = given_z;
            speed = 1;

            sphere_points_3D_head = graphics.make_sphere({(double)x, (double)y - 20, (double)z}, 5, 12);
            rect_points_3D_body = graphics.make_rectangle({(double)x, (double)y, (double)z}, 10, 20, 5);


            rect_points_3D_arm1 = graphics.make_rectangle({(double)x - 7, (double)y - 5, (double)z}, 2, 2, 25);
            rect_points_3D_arm2 = graphics.make_rectangle({(double)x + 7, (double)y - 5, (double)z}, 2, 2, 25);
            rect_points_3D_leg1 = graphics.make_rectangle({(double)x - 2, (double)y + 12, (double)z}, 2, 5, 5);
            rect_points_3D_leg2 = graphics.make_rectangle({(double)x + 2, (double)y + 12, (double)z}, 2, 5, 5);
        }


        void render_zombie(Graphics graphics){

            std::vector<std::vector<std::vector<std::vector<double>>>> sphere_triangle_points_3D_head = graphics.find_triangle_points_sphere(sphere_points_3D_head);
            std::vector<std::vector<std::vector<std::vector<int>>>> sphere_triangle_points_2D_head = graphics.compute_2D(sphere_triangle_points_3D_head);

            std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_body = graphics.find_triangle_points_rectangle(rect_points_3D_body);
            std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_body = graphics.compute_2D(rect_triangle_points_3D_body);


            std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_arm1 = graphics.find_triangle_points_rectangle(rect_points_3D_arm1);
            std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_arm1 = graphics.compute_2D(rect_triangle_points_3D_arm1);

            std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_arm2 = graphics.find_triangle_points_rectangle(rect_points_3D_arm2);
            std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_arm2 = graphics.compute_2D(rect_triangle_points_3D_arm2);

            std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_leg1 = graphics.find_triangle_points_rectangle(rect_points_3D_leg1);
            std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_leg1 = graphics.compute_2D(rect_triangle_points_3D_leg1);

            std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_leg2 = graphics.find_triangle_points_rectangle(rect_points_3D_leg2);
            std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_leg2 = graphics.compute_2D(rect_triangle_points_3D_leg2);


            graphics.draw_triangles_sphere(sphere_triangle_points_2D_head);
            graphics.draw_triangles_rectangle(rect_triangle_points_2D_body);

            graphics.draw_triangles_rectangle(rect_triangle_points_2D_arm1);
            graphics.draw_triangles_rectangle(rect_triangle_points_2D_arm2);
            graphics.draw_triangles_rectangle(rect_triangle_points_2D_leg1);
            graphics.draw_triangles_rectangle(rect_triangle_points_2D_leg2);

        }
};