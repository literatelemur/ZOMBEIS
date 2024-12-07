#include <SDL2/SDL.h>
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>


#ifndef graphics_H
#define graphics_H

class Graphics {

    public:

        int zscreendiff;
        int playerx;
        int playery;
        int playerz;

        SDL_Window* window;
        SDL_Renderer* renderer;

        Graphics(); // Constructor

        std::vector<std::vector<double>> make_sphere(std::vector<double> center, int radius, int num_points);

        std::vector<std::vector<double>> make_rectangle(std::vector<double> center, double top_length, double side_length, double depth);

        std::vector<std::vector<std::vector<std::vector<double>>>> find_triangle_points_sphere(std::vector<std::vector<double>> sphere_points_3D);

        std::vector<std::vector<std::vector<std::vector<double>>>> find_triangle_points_rectangle(std::vector<std::vector<double>> rect_points_3D);

        std::vector<std::vector<std::vector<std::vector<int>>>> compute_2D(std::vector<std::vector<std::vector<std::vector<double>>>> triangle_points);

        void clear_draw_screen();

        void draw_horizon();

        void draw_triangles_sphere(std::vector<std::vector<std::vector<std::vector<int>>>> triangle_points);

        void draw_triangles_rectangle(std::vector<std::vector<std::vector<std::vector<int>>>> triangle_points);

        void set_color(int r, int g, int b);

        void present_frame();
        
};

#endif // graphics_H