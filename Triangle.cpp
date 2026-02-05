#include <GL/glut.h>
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <list>
#include <functional>
#include <numeric>


#include "Graphics.h"

        
Triangle::Triangle(Graphics* graphics, std::vector<double> start_point1, std::vector<double> start_point2, std::vector<double> start_point3, std::string given_draw_type, std::vector<double> given_full_color, std::vector<double> given_outline_color, int given_line_scale){

    points = {start_point1, start_point2, start_point3};
    dist;
    draw_type = given_draw_type;
    full_color = {given_full_color[0], given_full_color[1], given_full_color[2]};
    outline_color = {given_outline_color[0], given_outline_color[1], given_outline_color[2]};

    line_scale = given_line_scale;
}

//void Triangle::class_name(Graphics* graphics){