#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

#include "Arrow.h"
#include "Graphics.h"
#include "main.h"

#include <GL/glut.h>

Arrow::Arrow(Graphics* graphics, int click_x, int click_y){

    count = 0;
    origin_x = graphics->playerx;
    origin_y = graphics->playery;
    origin_z = graphics->playerz;

    z = graphics->playerz;

    depth = 5;


    double x_diff_screen = click_x - glutGet(GLUT_WINDOW_WIDTH) / 2;
    double y_diff_screen = click_y - glutGet(GLUT_WINDOW_HEIGHT) / 2;

    x_diff_screen = click_x / double(glutGet(GLUT_WINDOW_WIDTH)) * 1920.0 - 1920 / 2;
    y_diff_screen = click_y / double(glutGet(GLUT_WINDOW_HEIGHT)) * 1080.0 - 1080 / 2;

    anglex = atan2(x_diff_screen, graphics->zscreendiff);
    angley = atan2(y_diff_screen, graphics->zscreendiff);

    double x_diff_3D = tan(anglex) * (z - origin_z);
    double y_diff_3D = tan(angley) * (z - origin_z);

    rect_points_3D_body = graphics->make_box({origin_x + x_diff_3D, origin_y + y_diff_3D, (double)z}, 1, 1, depth);

}


void Arrow::render(Graphics* graphics){
    
    rect_points_3D_body = graphics->make_box({(double)x, (double)y, (double)z}, 1, 1, depth);
    std::vector<std::vector<int>> rect_points_2D_body = graphics->compute_2D_box(rect_points_3D_body);
    graphics->set_color(1, 1, 1);
    graphics->draw_hollow_box(rect_points_2D_body);

}


void Arrow::move(Graphics* graphics){

    z+=1;

    double x_diff_origin_3D = tan(anglex) * (z - origin_z);
    double y_diff_origin_3D = tan(angley) * (z - origin_z);
    //double z_diff_origin_3D = z - origin_z;

    x = (int) (x_diff_origin_3D + origin_x);
    y = (int) (y_diff_origin_3D + origin_y);

}