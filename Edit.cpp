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

void Edit::move_point(int coor, int dir){

    double move_amount = 0.025;

    Edit::points_3D[Edit::points_3D_index][coor] += move_amount * dir;
    for (int i = 0; i < Edit::points_points_3D[Edit::points_3D_index].size(); i++){
        Edit::points_points_3D[Edit::points_3D_index][i][coor] += move_amount * dir;
    }

    double dist = sqrt(abs(Edit::points_3D[Edit::points_3D_index][0] - Edit::points_3D[Edit::points_3D_index - 1][0]) + 
                        abs(Edit::points_3D[Edit::points_3D_index][1] - Edit::points_3D[Edit::points_3D_index - 1][1]) +
                        abs(Edit::points_3D[Edit::points_3D_index][2] - Edit::points_3D[Edit::points_3D_index - 1][2]));

    for (int i = 0; i < Edit::triangles_3D.size(); i++){
        for (int j = 0; j < Edit::triangles_3D[i].points.size(); j++){
            if (Edit::triangles_3D[i].points[j][0] > Edit::points_3D[Edit::points_3D_index][0] - dist * 0.1 && Edit::triangles_3D[i].points[j][0] < Edit::points_3D[Edit::points_3D_index][0] + dist * 0.1 &&
                    Edit::triangles_3D[i].points[j][1] > Edit::points_3D[Edit::points_3D_index][1] - dist * 0.1 && Edit::triangles_3D[i].points[j][1] < Edit::points_3D[Edit::points_3D_index][1] + dist * 0.1 &&
                    Edit::triangles_3D[i].points[j][2] > Edit::points_3D[Edit::points_3D_index][2] - dist * 0.1 && Edit::triangles_3D[i].points[j][2] < Edit::points_3D[Edit::points_3D_index][2] + dist * 0.1){
                        
                Edit::triangles_3D[i].points[j][coor] += move_amount * dir;
            }
        }
    }
}