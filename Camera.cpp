#include <GL/glut.h>
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <list>

#include "Camera.h"
#include "Graphics.h"
#include "Triangle.h"


Camera::Camera(){

    playerx = 960;
    playery = 1060;
    playerz = 0;

    anglex_diff = 0;
    angley_diff = 0;


}

std::vector<double> Camera::rotate_point(std::vector<double> point){


    double x_diff = point[0] - playerx;
    double y_diff = point[1] - playery;
    double z_diff = point[2] - playerz;


    // Yaw rotation
    double cos_x = cos(anglex_diff);
    double sin_x = sin(anglex_diff);

    double turned_x = x_diff * cos_x - z_diff * sin_x;
    double turned_z_partly = x_diff * sin_x + z_diff * cos_x;

    // Pitch rotation
    double cos_y = cos(angley_diff);
    double sin_y = sin(angley_diff);

    double turned_y = y_diff * cos_y - turned_z_partly * sin_y;
    double turned_z_final = y_diff * sin_y + turned_z_partly * cos_y;

    return {turned_x, turned_y, turned_z_final};

}

std::vector<double> Camera::rotate_point_backwards(std::vector<double> point){


    double x_diff = point[0] - playerx;
    double y_diff = point[1] - playery;
    double z_diff = point[2] - playerz;


    // Yaw rotation
    double cos_x = cos(anglex_diff * -1);
    double sin_x = sin(anglex_diff * -1);

    double turned_x = x_diff * cos_x - z_diff * sin_x;
    double turned_z_partly = x_diff * sin_x + z_diff * cos_x;

    // Pitch rotation
    double cos_y = cos(angley_diff * -1);
    double sin_y = sin(angley_diff * -1);

    double turned_y = y_diff * cos_y - turned_z_partly * sin_y;
    double turned_z_final = y_diff * sin_y + turned_z_partly * cos_y;

    return {turned_x, turned_y, turned_z_final};

}