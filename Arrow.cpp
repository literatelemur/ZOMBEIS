#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

#include "Arrow.h"
#include "Graphics.h"

Arrow::Arrow(Graphics* graphics, int click_x, int click_y){

    count = 0;
    origin_x = graphics->playerx;
    origin_y = graphics->playery;
    origin_z = graphics->playerz;

    z = graphics->playerz;

    double x_diff_screen = click_x - 960;
    double y_diff_screen = click_y - 540;

    anglex = atan2(x_diff_screen, graphics->zscreendiff);
    angley = atan2(y_diff_screen, graphics->zscreendiff);

    double x_diff_3D = tan(anglex) * (z - origin_z);
    double y_diff_3D = tan(angley) * (z - origin_z);

    rect_points_3D_body = graphics->make_box({origin_x + x_diff_3D, origin_y + y_diff_3D, (double)z}, 1, 1, 4);

}


void Arrow::render_arrow(Graphics* graphics){
    // count++;
    // if (count % 10 == 0){
    //     z++;
    // }    
    z++;
    
    double x_diff_3D = sin(anglex) * (z - origin_z);
    double y_diff_3D = sin(angley) * (z - origin_z);
    double z_diff_3D = x_diff_3D / tan(anglex);

    for (int i = 0; i < rect_points_3D_body.size(); i++){

        int x_pos_diff_3D = (int) (x_diff_3D + origin_x - rect_points_3D_body[i][0]);
        int y_pos_diff_3D = (int) (y_diff_3D + origin_y - rect_points_3D_body[i][1]);
        int z_pos_diff_3D = (int) (z_diff_3D + origin_z - rect_points_3D_body[i][2]);

        rect_points_3D_body[i][0] = rect_points_3D_body[i][0] + x_pos_diff_3D;
        rect_points_3D_body[i][1] = rect_points_3D_body[i][1] + y_pos_diff_3D;
        rect_points_3D_body[i][2] = rect_points_3D_body[i][2] + z_pos_diff_3D;

    }


    std::vector<std::vector<int>> rect_points_2D_body = graphics->compute_2D_box(rect_points_3D_body);
    graphics->draw_box(rect_points_2D_body);

}


void Arrow::move(Graphics* graphics){
    for (int i = 0; i < rect_points_3D_body.size(); i++){
        rect_points_3D_body[i][2] += 15;
    }
}