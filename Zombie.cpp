#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

#include "Zombie.h"
#include "Graphics.h"
#include "main.h"


Zombie::Zombie(Graphics* graphics, int x, int y, int z){

    speed = 10;
    leg_angle1 = 0;
    leg_inner_dir = 1;
    arm_phase = 0;
    pi = 3.14159265358979323846;

    sphere_points_3D_head = graphics->make_sphere({(double)x, (double)y - 20, (double)z}, 5, 12);
    rect_points_3D_body = graphics->make_box({(double)x, (double)y, (double)z}, 10, 20, 5);


    rect_points_3D_arm1 = graphics->make_box({(double)x - 7, (double)y - 7, (double)z - 2}, 4, 4, 10);
    rect_points_3D_arm2 = graphics->make_box({(double)x + 7, (double)y - 7, (double)z - 2}, 4, 4, 10);
    rect_points_3D_leg1 = graphics->make_box({(double)x - 3, (double)y + 13, (double)z}, 4, 6, 5);
    rect_points_3D_leg2 = graphics->make_box({(double)x + 3, (double)y + 13, (double)z}, 4, 6, 5);

    
    leg_length = rect_points_3D_leg1[2][1] - rect_points_3D_leg1[0][1];
    leg_depth = rect_points_3D_leg1[0][2] - rect_points_3D_leg1[4][2];

}


void Zombie::render(Graphics* graphics){

    std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> sphere_triangle_points_3D_head = graphics->find_triangle_points_sphere(sphere_points_3D_head);
    std::vector<std::vector<std::vector<std::vector<std::vector<int>>>>> sphere_triangle_points_2D_head = graphics->compute_2D_triangles(sphere_triangle_points_3D_head);
    graphics->set_color(0, 0, 0);
    graphics->draw_full_triangles_sphere(sphere_triangle_points_2D_head);
    graphics->set_color(0, 0, 1);
    graphics->draw_hollow_triangles_sphere(sphere_triangle_points_2D_head);

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

    // Moving all zombei points towards player (negative z direction).

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



    
    if (leg_angle1 > 89) leg_inner_dir = 0;
    else if (leg_angle1 < -89) leg_inner_dir = 1;


    if (leg_inner_dir == 1) {
            leg_angle1 += 20;
            leg_angle2 -= 20;
    } else {
            leg_angle1 -= 20;
            leg_angle2 += 20;
    }


    // Turning the first leg.

    double leg_angle1_rad = leg_angle1 * (pi / 180.0);

    double z_diff = sin(leg_angle1_rad) * leg_length;
    double y_diff = cos(leg_angle1_rad) * leg_length;

    rect_points_3D_leg1[6][1] = rect_points_3D_leg1[4][1] + y_diff;
    rect_points_3D_leg1[6][2] = rect_points_3D_leg1[4][2] - z_diff;
    
    rect_points_3D_leg1[7][1] = rect_points_3D_leg1[5][1] + y_diff;
    rect_points_3D_leg1[7][2] = rect_points_3D_leg1[5][2] - z_diff;


    
    double same_tri_other_angle = 90 - leg_angle1;
    double tri2_angle = 90 - same_tri_other_angle;

    double tri2_angle_rad = tri2_angle * (pi / 180.0);

    double z2_diff = cos(tri2_angle_rad) * leg_depth;
    double y2_diff = sin(tri2_angle_rad) * leg_depth;

    rect_points_3D_leg1[2][1] = rect_points_3D_leg1[6][1] + y2_diff;
    rect_points_3D_leg1[2][2] = rect_points_3D_leg1[6][2] + z2_diff;
    
    rect_points_3D_leg1[3][1] = rect_points_3D_leg1[7][1] + y2_diff;
    rect_points_3D_leg1[3][2] = rect_points_3D_leg1[7][2] + z2_diff;



    double same_tri2_other_angle = 180 - (tri2_angle + 90);
    double tri3_angle = 90 - same_tri2_other_angle;

    double tri3_angle_rad = tri3_angle * (pi / 180.0);

    double z3_diff = sin(tri3_angle_rad) * leg_length;
    double y3_diff = cos(tri3_angle_rad) * leg_length;

    rect_points_3D_leg1[0][1] = rect_points_3D_leg1[2][1] - y3_diff;
    rect_points_3D_leg1[0][2] = rect_points_3D_leg1[2][2] + z3_diff;
    
    rect_points_3D_leg1[1][1] = rect_points_3D_leg1[3][1] - y3_diff;
    rect_points_3D_leg1[1][2] = rect_points_3D_leg1[3][2] + z3_diff;





    // Turning the second leg.

    double leg_angle2_rad = leg_angle2 * (pi / 180.0);

    z_diff = sin(leg_angle2_rad) * leg_length;
    y_diff = cos(leg_angle2_rad) * leg_length;

    rect_points_3D_leg2[6][1] = rect_points_3D_leg2[4][1] + y_diff;
    rect_points_3D_leg2[6][2] = rect_points_3D_leg2[4][2] - z_diff;
    
    rect_points_3D_leg2[7][1] = rect_points_3D_leg2[5][1] + y_diff;
    rect_points_3D_leg2[7][2] = rect_points_3D_leg2[5][2] - z_diff;


    
    same_tri_other_angle = 90 - leg_angle2;
    tri2_angle = 90 - same_tri_other_angle;

    tri2_angle_rad = tri2_angle * (pi / 180.0);

    z2_diff = cos(tri2_angle_rad) * leg_depth;
    y2_diff = sin(tri2_angle_rad) * leg_depth;

    rect_points_3D_leg2[2][1] = rect_points_3D_leg2[6][1] + y2_diff;
    rect_points_3D_leg2[2][2] = rect_points_3D_leg2[6][2] + z2_diff;
    
    rect_points_3D_leg2[3][1] = rect_points_3D_leg2[7][1] + y2_diff;
    rect_points_3D_leg2[3][2] = rect_points_3D_leg2[7][2] + z2_diff;



    same_tri2_other_angle = 180 - (tri2_angle + 90);
    tri3_angle = 90 - same_tri2_other_angle;

    tri3_angle_rad = tri3_angle * (pi / 180.0);

    z3_diff = sin(tri3_angle_rad) * leg_length;
    y3_diff = cos(tri3_angle_rad) * leg_length;

    rect_points_3D_leg2[0][1] = rect_points_3D_leg2[2][1] - y3_diff;
    rect_points_3D_leg2[0][2] = rect_points_3D_leg2[2][2] + z3_diff;
    
    rect_points_3D_leg2[1][1] = rect_points_3D_leg2[3][1] - y3_diff;
    rect_points_3D_leg2[1][2] = rect_points_3D_leg2[3][2] + z3_diff;



    // // Moving arms
    // if (arm_phase >= 0 && arm_phase <= 1){
    //     for (int i = 0; i < rect_points_3D_arm1.size(); i++){
    //         rect_points_3D_arm1[i][1]++;
    //         rect_points_3D_arm2[i][1]++;
    //     }
    // }else if (arm_phase >= 2 && arm_phase <= 3){
    //     for (int i = 0; i < rect_points_3D_arm1.size(); i++){
    //         rect_points_3D_arm1[i][1]--;
    //         rect_points_3D_arm2[i][1]--;
    //     }
    // }else if (arm_phase >= 4 && arm_phase <= 5){
    //     for (int i = 0; i < rect_points_3D_arm1.size(); i++){
    //         rect_points_3D_arm1[i][0]--;
    //         rect_points_3D_arm2[i][0]++;
    //     }
    // }else if (arm_phase >= 6 && arm_phase <= 7){
    //     for (int i = 0; i < rect_points_3D_arm1.size(); i++){
    //         rect_points_3D_arm1[i][0]++;
    //         rect_points_3D_arm2[i][0]--;
    //     }
    // }



    // Moving arms
    if (arm_phase >= 0 && arm_phase <= 3){
        for (int i = 4; i < rect_points_3D_arm1.size(); i++){
            rect_points_3D_arm1[i][1]++;
            rect_points_3D_arm2[i][1]++;
        }
    }else if (arm_phase >= 4 && arm_phase <= 7){
        for (int i = 4; i < rect_points_3D_arm1.size(); i++){
            rect_points_3D_arm1[i][1]--;
            rect_points_3D_arm2[i][1]--;
        }
    }



    arm_phase++;

    if (arm_phase == 8){
        arm_phase = 0;
    }
        
}
