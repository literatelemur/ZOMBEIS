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
        std::vector<double> color;

        Triangle(Graphics* graphics, std::vector<double> start_point1, std::vector<double> start_point2, std::vector<double> start_point3, std::string given_draw_type, std::vector<double> given_color); // Constructor
        
};

#endif