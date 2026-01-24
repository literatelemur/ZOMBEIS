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

        std::vector<double> point1;
        std::vector<double> point2;
        std::vector<double> point3;
        double dist;
        std::string draw_type;


        Triangle(Graphics* graphics, std::vector<double> start_point1, std::vector<double> start_point2, std::vector<double> start_point3, std::string given_draw_type); // Constructor
        
};

#endif