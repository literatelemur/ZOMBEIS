#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

#include "Bullet.h"
#include "Graphics.h"

#include <GL/glut.h>

#include "Triangle.h"


Bullet::Bullet(Graphics* graphics, int click_x, int click_y){

    origin_x = graphics->playerx;
    origin_y = graphics->playery;
    origin_z = graphics->playerz;

    center_x = origin_x;
    center_y = origin_y;
    center_z = origin_z;

    depth = 5;
    speed = 1;

    double x_diff_screen = click_x / double(glutGet(GLUT_WINDOW_WIDTH)) * 1920.0 - 1920 / 2;
    double y_diff_screen = click_y / double(glutGet(GLUT_WINDOW_HEIGHT)) * 1080.0 - 1080 / 2;

    anglex = atan2(0.0, graphics->zscreendiff) - graphics->anglex_diff;
    angley = atan2(0.0, graphics->zscreendiff) - graphics->angley_diff;

    double x_diff_3D = tan(anglex) * (origin_z - origin_z);
    double y_diff_3D = tan(angley) * (origin_z - origin_z);

    box_points_3D = graphics->make_box({origin_x + x_diff_3D, origin_y + y_diff_3D, (double)origin_z}, 1, 1, depth);
    box_triangles_3D = graphics->find_triangles_box(box_points_3D);
    find_movement_values(graphics);

}


void Bullet::find_movement_values(Graphics* graphics){

    center_z += speed;

    double x_diff_origin_3D = tan(anglex) * (center_z - origin_z);
    double y_diff_origin_3D = tan(angley) * (center_z - origin_z);

    double x = x_diff_origin_3D + origin_x;
    double y = y_diff_origin_3D + origin_y;

    double last_center_x = center_x;
    double last_center_y = center_y;
    double last_center_z = center_z;

    center_x = x;
    center_y = y;

    center_x_move = center_x - last_center_x;
    center_y_move = center_y - last_center_y;

}


void Bullet::move(Graphics* graphics){

    for (int i = 0; i < box_triangles_3D.size(); i++){

        for (int j = 0; j < box_triangles_3D[i].points.size(); j++){

            box_triangles_3D[i].points[j][0] += center_x_move;
            box_triangles_3D[i].points[j][1] += center_y_move;
            box_triangles_3D[i].points[j][2] += speed;
        }
    }

}
