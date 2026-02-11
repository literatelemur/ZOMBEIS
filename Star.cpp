#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

#include "Star.h"
#include "Graphics.h"

#include <GL/glut.h>

Star::Star(Graphics* graphics, double given_x, double given_y, double given_z, int given_lower_bound, int given_upper_bound){

    count = 0;
    depth = 5;

    origin_x = given_x;
    origin_y = given_y;
    origin_z = given_z;

    upper_bound = given_upper_bound;
    lower_bound = given_lower_bound;
    osc = 1;
    y_wait = 0;

    x = given_x;
    y = given_y;
    z = given_z;

    box_points_3D = graphics->make_box({x, y, z}, 1, 1, depth);

}


void Star::find_movement_value(Graphics* graphics){

    if (osc){
        y_wait++;
        if (y_wait % 5 == 0){
            y++;
            y_move = 1;
        }            
        if (y > upper_bound) osc = 0;
    }else if (!osc){
        y_wait--;
        if (y_wait % 5 == 0){
            y--;
            y_move = -1;
        }
        if (y < lower_bound) osc = 1;
    }

}


void Star::move(Graphics* graphics){

    for (int i = 0; i < box_points_3D.size(); i++){
        box_points_3D[i][1] += y_move;
    }

}