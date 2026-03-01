#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <list>

#include "Triangle.h"

#ifndef CAMERA_H
#define CAMERA_H

class Graphics;

class Camera {

    public:

        double playerx;
        double playery;
        double playerz;

        double anglex_diff;
        double angley_diff;
        

        Camera(); // Constructor

        std::vector<double> rotate_point(std::vector<double> point);
        
};

#endif