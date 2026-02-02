#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

#include "Bullet.h"
#include "Graphics.h"
#include "main.h"

#include <GL/glut.h>

#include "Triangle.h"

Bullet::Bullet(Graphics* graphics, int click_x, int click_y){

    origin_x = graphics->playerx;
    origin_y = graphics->playery;
    origin_z = graphics->playerz;

    depth = 5;

    double x_diff_screen = click_x / double(glutGet(GLUT_WINDOW_WIDTH)) * 1920.0 - 1920 / 2;
    double y_diff_screen = click_y / double(glutGet(GLUT_WINDOW_HEIGHT)) * 1080.0 - 1080 / 2;

    anglex = atan2(0.0, graphics->zscreendiff) - graphics->anglex_diff;
    angley = atan2(0.0, graphics->zscreendiff) - graphics->angley_diff;

    double x_diff_3D = tan(anglex) * (origin_z - origin_z);
    double y_diff_3D = tan(angley) * (origin_z - origin_z);

    box_points_3D = graphics->make_box({origin_x + x_diff_3D, origin_y + y_diff_3D, (double)origin_z}, 1, 1, depth);
    box_triangles_3D = graphics->test_find_triangles_box(box_points_3D);

}


void Bullet::render(Graphics* graphics){
    
    // box_points_3D = graphics->make_box({(double)x, (double)y, (double)z}, 1, 1, depth);
    // std::vector<std::vector<std::vector<double>>> clipped_box_points_3D = graphics->clip_box(box_points_3D);
    // std::vector<std::vector<std::vector<int>>> clipped_box_points_2D = graphics->compute_2D_box_as_lines(clipped_box_points_3D);
    // graphics->set_color(0, 0, 0);
    // graphics->draw_full_box_as_lines(clipped_box_points_2D);
    // graphics->set_color(1, 1, 1);
    // graphics->draw_hollow_box_as_lines(clipped_box_points_2D);

}


void Bullet::move(Graphics* graphics){

    for (int i = 0; i < box_triangles_3D.size(); i++){

        for (int j = 0; j < box_triangles_3D[i].points.size(); j++){

            box_triangles_3D[i].points[j][2] += 1;
            double z = box_triangles_3D[i].points[j][2];

            double x_diff_origin_3D = tan(anglex) * (z - origin_z);
            double y_diff_origin_3D = tan(angley) * (z - origin_z);

            double x = x_diff_origin_3D + origin_x;
            double y = y_diff_origin_3D + origin_y;

            box_triangles_3D[i].points[j][0] = x;
            box_triangles_3D[i].points[j][1] = y;
            box_triangles_3D[i].points[j][2] = z;
        }
    }

}