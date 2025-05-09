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
    leg_angle = 0;
    double pi = 3.14159265358979323846;

    sphere_points_3D_head = graphics->make_sphere({(double)x, (double)y - 20, (double)z}, 5, 12);
    rect_points_3D_body = graphics->make_box({(double)x, (double)y, (double)z}, 10, 20, 5);


    rect_points_3D_arm1 = graphics->make_box({(double)x - 7, (double)y - 7, (double)z - 2}, 4, 4, 10);
    rect_points_3D_arm2 = graphics->make_box({(double)x + 7, (double)y - 7, (double)z - 2}, 4, 4, 10);
    rect_points_3D_leg1 = graphics->make_box({(double)x - 3, (double)y + 13, (double)z}, 4, 6, 5);
    rect_points_3D_leg2 = graphics->make_box({(double)x + 3, (double)y + 13, (double)z}, 4, 6, 5);

    
    leg_length = rect_points_3D_leg1[2][1] - rect_points_3D_leg1[0][1];


    orig_points_3D_leg1 = std::vector<std::vector<double>>(8, std::vector<double>(3, 0.0));
    for (int i = 2; i < 4; i++){
        for (int j = 0; j < 3; j++){
            orig_points_3D_leg1[i][j] = rect_points_3D_leg1[i][j];
        }
    }
            

}


void Zombie::render(Graphics* graphics){

    graphics->set_color(0, 0, 1);
    std::vector<std::vector<std::vector<std::vector<double>>>> sphere_triangle_points_3D_head = graphics->find_triangle_points_sphere(sphere_points_3D_head);
    std::vector<std::vector<std::vector<std::vector<int>>>> sphere_triangle_points_2D_head = graphics->compute_2D_triangles(sphere_triangle_points_3D_head);
    graphics->draw_triangles_sphere(sphere_triangle_points_2D_head);

    std::vector<std::vector<int>> rect_points_2D_body = graphics->compute_2D_box(rect_points_3D_body);
    graphics->set_color(0, 0, 0);
    graphics->draw_full_box(rect_points_2D_body);
    graphics->set_color(0, 0, 1);
    graphics->draw_hollow_box(rect_points_2D_body);

    std::vector<std::vector<int>> rect_points_2D_arm1 = graphics->compute_2D_box(rect_points_3D_arm1);
    graphics->set_color(0, 0, 0);
    graphics->draw_full_box(rect_points_2D_arm1);
    graphics->set_color(0, 0, 1);
    graphics->draw_hollow_box(rect_points_2D_arm1);

    std::vector<std::vector<int>> rect_points_2D_arm2 = graphics->compute_2D_box(rect_points_3D_arm2);
    graphics->set_color(0, 0, 0);
    graphics->draw_full_box(rect_points_2D_arm2);
    graphics->set_color(0, 0, 1);
    graphics->draw_hollow_box(rect_points_2D_arm2);

    std::vector<std::vector<int>> rect_points_2D_leg1 = graphics->compute_2D_box(rect_points_3D_leg1);
    graphics->set_color(0, 0, 0);
    graphics->draw_full_box(rect_points_2D_leg1);
    graphics->set_color(0, 0, 1);
    graphics->draw_hollow_box(rect_points_2D_leg1);

    std::vector<std::vector<int>> rect_points_2D_leg2 = graphics->compute_2D_box(rect_points_3D_leg2);
    graphics->set_color(0, 0, 0);
    graphics->draw_full_box(rect_points_2D_leg2);
    graphics->set_color(0, 0, 1);
    graphics->draw_hollow_box(rect_points_2D_leg2);

}

void Zombie::move(int dir){

    // Moving all zombei points towards player (negative z direction)

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



    // if (dir == 1) leg_angle += 1;
    // else leg_angle -= 1;

    // double other_angle = (180 - leg_angle) / 2.0;

    // double leg_angle_rad = leg_angle * (pi / 180.0);
    // double other_angle_rad = other_angle * (pi / 180.0);



    // double leg_tri_opp_side;

    // // avoid divide by zero
    // // if (std::abs(sin(other_angle_rad)) < 1e-6) {
    // //     leg_tri_opp_side = 0;
    // // } else {
    // //     leg_tri_opp_side = sin(leg_angle_rad) * leg_length / sin(other_angle_rad);
    // // }


    // leg_tri_opp_side = sin(leg_angle_rad) * leg_length / sin(other_angle_rad);


    // double other_tri_angle = 90 - other_angle;
    // double other_tri_angle_rad = other_tri_angle * (pi / 180.0);

    // double y_diff = sin(other_tri_angle_rad) * leg_tri_opp_side;
    // double z_diff = cos(other_tri_angle_rad) * leg_tri_opp_side;

    // rect_points_3D_leg1[6][1] = orig_points_3D_leg1[6][1] - y_diff;
    // rect_points_3D_leg1[6][2] = orig_points_3D_leg1[6][2] - z_diff;
    
    // rect_points_3D_leg1[7][1] = orig_points_3D_leg1[7][1] - y_diff;
    // rect_points_3D_leg1[7][2] = orig_points_3D_leg1[7][2] - z_diff;




    // rect_points_3D_leg1[6][1] = rect_points_3D_leg1[6][1] - 0;
    // rect_points_3D_leg1[6][2] = rect_points_3D_leg1[6][2] - 0;
    
    // rect_points_3D_leg1[7][1] = rect_points_3D_leg1[7][1] - 0;
    // rect_points_3D_leg1[7][2] = rect_points_3D_leg1[7][2] - 0;



    // std::cout << "--------\n";
    // std::cout << leg_tri_opp_side;
    // std::cout << "\n";
    // std::cout << y_diff;
    // std::cout << "\n"; 
    // std::cout << z_diff;
    // std::cout << "\n";

    // std::cout << "----------\n";
    // std::cout << leg_angle;
    // std::cout << "\n";

    // std::cout << y_diff;
    // std::cout << "\n";

    // std::cout << z_diff;
    // std::cout << "\n";

    // for (int i = 0; i < rect_points_3D_leg1.size(); i++){
        
    // }

    
}