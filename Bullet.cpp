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

    depth = 5;
    speed = 0.1;

    
    // Finding movement values based on looking angle.
    double angle_x = graphics->anglex_diff;
    double angle_y = graphics->angley_diff;

    // center_x_move = sin(angle_x) * speed;
    // center_y_move = sin(angle_y) * speed;
    // center_z_move = sqrt(speed * speed - center_x_move * center_x_move - center_y_move * center_y_move);

    // Copied from chatgpt. I do not understand the 3D math behind it, but it is based on a unit circle and my method did not work because it treated each dimension independently.
    center_x_move = cos(angle_y) * sin(angle_x) * speed;
    center_y_move = sin(angle_y) * speed;
    center_z_move = cos(angle_y) * cos(angle_x) * speed;



    box_points_3D = graphics->make_box({graphics->playerx, graphics->playery, graphics->playerz}, 1, 1, depth);

}


void Bullet::move(Graphics* graphics){

    for (int i = 0; i < box_points_3D.size(); i++){

        box_points_3D[i][0] += center_x_move;
        box_points_3D[i][1] += center_y_move;
        box_points_3D[i][2] += center_z_move;

    }

}
