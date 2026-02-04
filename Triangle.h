#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <list>


#ifndef TRIANGLE_H
#define TRIANGLE_H

class Graphics;

class Triangle {

    public:

        std::vector<std::vector<double>> points;
        double dist;
        std::string draw_type;
        std::vector<double> full_color;
        std::vector<double> outline_color;

        Triangle(Graphics* graphics, std::vector<double> start_point1, std::vector<double> start_point2, std::vector<double> start_point3, std::string given_draw_type, std::vector<double> given_full_color, std::vector<double> given_outline_color); // Constructor
        
};

#endif