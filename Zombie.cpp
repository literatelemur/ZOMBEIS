#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

#include "Zombie.h"
#include "Graphics.h"


Zombie::Zombie(Graphics* graphics, int x, int y, int z){

    speed = 1;

    sphere_points_3D_head = graphics->make_sphere({(double)x, (double)y - 20, (double)z}, 5, 12);
    rect_points_3D_body = graphics->make_box({(double)x, (double)y, (double)z}, 10, 20, 5);


    rect_points_3D_arm1 = graphics->make_box({(double)x - 7, (double)y - 7, (double)z - 2}, 4, 4, 10);
    rect_points_3D_arm2 = graphics->make_box({(double)x + 7, (double)y - 7, (double)z - 2}, 4, 4, 10);
    rect_points_3D_leg1 = graphics->make_box({(double)x - 3, (double)y + 13, (double)z}, 4, 6, 5);
    rect_points_3D_leg2 = graphics->make_box({(double)x + 3, (double)y + 13, (double)z}, 4, 6, 5);
}


void Zombie::render_zombie(Graphics* graphics){

    std::vector<std::vector<std::vector<std::vector<double>>>> sphere_triangle_points_3D_head = graphics->find_triangle_points_sphere(sphere_points_3D_head);
    std::vector<std::vector<std::vector<std::vector<int>>>> sphere_triangle_points_2D_head = graphics->compute_2D_triangles(sphere_triangle_points_3D_head);
    graphics->draw_triangles_sphere(sphere_triangle_points_2D_head);

    std::vector<std::vector<int>> rect_points_2D_body = graphics->compute_2D_box(rect_points_3D_body);
    graphics->draw_box(rect_points_2D_body);

    std::vector<std::vector<int>> rect_points_2D_arm1 = graphics->compute_2D_box(rect_points_3D_arm1);
    graphics->draw_box(rect_points_2D_arm1);

    std::vector<std::vector<int>> rect_points_2D_arm2 = graphics->compute_2D_box(rect_points_3D_arm2);
    graphics->draw_box(rect_points_2D_arm2);

    std::vector<std::vector<int>> rect_points_2D_leg1 = graphics->compute_2D_box(rect_points_3D_leg1);
    graphics->draw_box(rect_points_2D_leg1);

    std::vector<std::vector<int>> rect_points_2D_leg2 = graphics->compute_2D_box(rect_points_3D_leg2);
    graphics->draw_box(rect_points_2D_leg2);

}

void Zombie::move(int dir){

    for (int i = 0; i < sphere_points_3D_head.size(); i++){
        sphere_points_3D_head[i][2] -= speed * dir;
    }

    for (int i = 0; i < rect_points_3D_body.size(); i++){
        rect_points_3D_body[i][2] -= speed * dir;
        rect_points_3D_arm1[i][2] -= speed * dir;
        rect_points_3D_arm2[i][2] -= speed * dir;
        rect_points_3D_leg1[i][2] -= speed * dir;
        rect_points_3D_leg2[i][2] -= speed * dir;
    }
}