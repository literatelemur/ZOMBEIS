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

        
Triangle::Triangle(Graphics* graphics, std::vector<double> start_point1, std::vector<double> start_point2, std::vector<double> start_point3){

    point1 = start_point1;
    point2 = start_point2;
    point3 = start_point3;
    dist;

}

//void Triangle::class_name(Graphics* graphics){