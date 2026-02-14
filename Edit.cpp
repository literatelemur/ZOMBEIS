#include <GL/glut.h>
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <list>

#include "World.h"
#include "Graphics.h"
#include "Triangle.h"
#include "Edit.h"


bool Edit::edit_mode = false;

std::vector<std::vector<double>> Edit::points_3D = {};

int Edit::points_3D_index = -1;

std::vector<std::vector<std::vector<double>>> Edit::points_points_3D = {};

std::vector<Triangle> Edit::triangles_3D = {};

void Edit::toggle_edit_mode(){

    if (!Edit::edit_mode){
        Edit::edit_mode = true;

    }else{
        Edit::edit_mode = false;
        Edit::points_3D = {};
        Edit::points_points_3D = {};
        Edit::triangles_3D = {};
    }

}