#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

#include "Arrow.h"
#include "Graphics.h"

Arrow::Arrow(Graphics* graphics){

    rect_points_3D_body = graphics->make_box({(double)961, (double)1060, (double)5}, 1, 1, 4);

}


void Arrow::render_arrow(Graphics* graphics){

    std::vector<std::vector<int>> rect_points_2D_body = graphics->compute_2D_box(rect_points_3D_body);
    graphics->draw_box(rect_points_2D_body);

}


void Arrow::move(Graphics* graphics){
    for (int i = 0; i < rect_points_3D_body.size(); i++){
        rect_points_3D_body[i][2] += 15;
    }
}