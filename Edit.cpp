#include <GL/glut.h>
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <list>

#include "World.h"
#include "Graphics.h"
#include "Triangle.h"
#include "Edit.h"


bool Edit::edit_mode = false;

std::vector<std::vector<double>> Edit::points_3D = {};

int Edit::points_3D_main_index = -1;
int Edit::points_3D_sub1_index = -2;
int Edit::points_3D_sub2_index = -3;

std::vector<std::vector<std::vector<double>>> Edit::points_points_3D = {};

std::vector<Triangle> Edit::triangles_3D = {};

std::string Edit::edit_click_mouse_button = "none";

bool Edit::first_click_move = true;
double Edit::prev_anglex_diff = 0;
double Edit::prev_angley_diff = 0;

bool Edit::edit_draw_points = true;

void Edit::toggle_edit_mode(){

    if (!Edit::edit_mode){
        Edit::edit_mode = true;

    }else{
        Edit::edit_mode = false;
        Edit::points_3D = {};
        Edit::points_3D_main_index = -1;
        Edit::points_3D_sub1_index = -2;
        Edit::points_3D_sub2_index = -3;
        Edit::points_points_3D = {};
        Edit::triangles_3D = {};
        Edit::edit_click_mouse_button = "none";
    }

}

void Edit::move_point(int coor, int dir){

    double move_amount = 0.025;

    Edit::points_3D[Edit::points_3D_main_index][coor] += move_amount * dir;
    for (int i = 0; i < Edit::points_points_3D[Edit::points_3D_main_index].size(); i++){
        Edit::points_points_3D[Edit::points_3D_main_index][i][coor] += move_amount * dir;
    }

    if (Edit::triangles_3D.size() > 0){
        double dist1 = sqrt(abs(Edit::points_3D[Edit::points_3D_main_index][0] - Edit::points_3D[Edit::points_3D_sub1_index][0]) + 
                            abs(Edit::points_3D[Edit::points_3D_main_index][1] - Edit::points_3D[Edit::points_3D_sub1_index][1]) +
                            abs(Edit::points_3D[Edit::points_3D_main_index][2] - Edit::points_3D[Edit::points_3D_sub1_index][2]));

        double dist2 = sqrt(abs(Edit::points_3D[Edit::points_3D_main_index][0] - Edit::points_3D[Edit::points_3D_sub2_index][0]) + 
                            abs(Edit::points_3D[Edit::points_3D_main_index][1] - Edit::points_3D[Edit::points_3D_sub2_index][1]) +
                            abs(Edit::points_3D[Edit::points_3D_main_index][2] - Edit::points_3D[Edit::points_3D_sub2_index][2]));

        double average_dist = (dist1 + dist2) / 2;

        for (int i = 0; i < Edit::triangles_3D.size(); i++){
            for (int j = 0; j < Edit::triangles_3D[i].points.size(); j++){
                if (Edit::triangles_3D[i].points[j][0] > Edit::points_3D[Edit::points_3D_main_index][0] - average_dist * 0.1 && Edit::triangles_3D[i].points[j][0] < Edit::points_3D[Edit::points_3D_main_index][0] + average_dist * 0.1 &&
                        Edit::triangles_3D[i].points[j][1] > Edit::points_3D[Edit::points_3D_main_index][1] - average_dist * 0.1 && Edit::triangles_3D[i].points[j][1] < Edit::points_3D[Edit::points_3D_main_index][1] + average_dist * 0.1 &&
                        Edit::triangles_3D[i].points[j][2] > Edit::points_3D[Edit::points_3D_main_index][2] - average_dist * 0.1 && Edit::triangles_3D[i].points[j][2] < Edit::points_3D[Edit::points_3D_main_index][2] + average_dist * 0.1){
                            
                    Edit::triangles_3D[i].points[j][coor] += move_amount * dir;
                }
            }
        }
    }
}


void Edit::click_point(Graphics* graphics){

    if (Edit::points_3D.size() > 0){

        double speed = 0.1;

        std::vector<double> sense_point = {graphics->playerx, graphics->playery, graphics->playerz};

        
        // Finding movement values based on looking angle.
        double angle_x = graphics->anglex_diff * -1;
        double angle_y = graphics->angley_diff * -1;

        // Copied from chatgpt. I do not understand the 3D math behind it, but it is based on a unit circle and my method did not work because it treated each dimension independently.
        double sense_point_x_move = cos(angle_y) * sin(angle_x) * speed;
        double sense_point_y_move = sin(angle_y) * speed;
        double sense_point_z_move = cos(angle_y) * cos(angle_x) * speed;


        // Shooting out invisible point that checks location for each edit point until a match is found or it runs out (1000 steps).
        bool done = false;
        for (int i = 0; i < 1000; i++){

            sense_point[0] += sense_point_x_move;
            sense_point[1] += sense_point_y_move;
            sense_point[2] += sense_point_z_move;

            for (int j = 0; j < Edit::points_3D.size(); j++){
                if (sense_point[0] > Edit::points_3D[j][0] - 0.25 && sense_point[0] < Edit::points_3D[j][0] + 0.25 &&
                        sense_point[1] > Edit::points_3D[j][1] - 0.25 && sense_point[1] < Edit::points_3D[j][1] + 0.25 &&
                        sense_point[2] > Edit::points_3D[j][2] - 0.25 && sense_point[2] < Edit::points_3D[j][2] + 0.25){
                    if (edit_click_mouse_button == "left") Edit::points_3D_main_index = j;
                    else if (edit_click_mouse_button == "middle") Edit::points_3D_sub1_index = j;
                    else if (edit_click_mouse_button == "right") Edit::points_3D_sub2_index = j;
                    done = true;
                    break;
                }
            }

            if (done){
                break;
            }

        }
    }

}


void Edit::move_point_with_mouse(Graphics* graphics){

    if (Edit::points_3D.size() > 0){

        if (!Edit::first_click_move){

            double anglex_diff_diff = graphics->anglex_diff - Edit::prev_anglex_diff;
            double angley_diff_diff = graphics->angley_diff - Edit::prev_angley_diff;


            double move_amountx = cos(anglex_diff_diff) * anglex_diff_diff * -5;
            double move_amounty = cos(angley_diff_diff) * angley_diff_diff * -5;
            double move_amountz = sin(anglex_diff_diff) * anglex_diff_diff * -5;


            if (Edit::triangles_3D.size() > 0){
                double dist1 = sqrt(abs(Edit::points_3D[Edit::points_3D_main_index][0] - Edit::points_3D[Edit::points_3D_sub1_index][0]) * abs(Edit::points_3D[Edit::points_3D_main_index][0] - Edit::points_3D[Edit::points_3D_sub1_index][0]) + 
                                    abs(Edit::points_3D[Edit::points_3D_main_index][1] - Edit::points_3D[Edit::points_3D_sub1_index][1]) * abs(Edit::points_3D[Edit::points_3D_main_index][1] - Edit::points_3D[Edit::points_3D_sub1_index][1]) +
                                    abs(Edit::points_3D[Edit::points_3D_main_index][2] - Edit::points_3D[Edit::points_3D_sub1_index][2]) * abs(Edit::points_3D[Edit::points_3D_main_index][2] - Edit::points_3D[Edit::points_3D_sub1_index][2]));

                double dist2 = sqrt(abs(Edit::points_3D[Edit::points_3D_main_index][0] - Edit::points_3D[Edit::points_3D_sub2_index][0]) * abs(Edit::points_3D[Edit::points_3D_main_index][0] - Edit::points_3D[Edit::points_3D_sub2_index][0]) + 
                                    abs(Edit::points_3D[Edit::points_3D_main_index][1] - Edit::points_3D[Edit::points_3D_sub2_index][1]) * abs(Edit::points_3D[Edit::points_3D_main_index][1] - Edit::points_3D[Edit::points_3D_sub2_index][1]) +
                                    abs(Edit::points_3D[Edit::points_3D_main_index][2] - Edit::points_3D[Edit::points_3D_sub2_index][2]) * abs(Edit::points_3D[Edit::points_3D_main_index][2] - Edit::points_3D[Edit::points_3D_sub2_index][2]));

                double average_dist = (dist1 + dist2) / 2;

                for (int i = 0; i < Edit::triangles_3D.size(); i++){
                    for (int j = 0; j < Edit::triangles_3D[i].points.size(); j++){
                        if (Edit::triangles_3D[i].points[j][0] > Edit::points_3D[Edit::points_3D_main_index][0] - average_dist * 0.1 && Edit::triangles_3D[i].points[j][0] < Edit::points_3D[Edit::points_3D_main_index][0] + average_dist * 0.1 &&
                                Edit::triangles_3D[i].points[j][1] > Edit::points_3D[Edit::points_3D_main_index][1] - average_dist * 0.1 && Edit::triangles_3D[i].points[j][1] < Edit::points_3D[Edit::points_3D_main_index][1] + average_dist * 0.1 &&
                                Edit::triangles_3D[i].points[j][2] > Edit::points_3D[Edit::points_3D_main_index][2] - average_dist * 0.1 && Edit::triangles_3D[i].points[j][2] < Edit::points_3D[Edit::points_3D_main_index][2] + average_dist * 0.1){
                                    
                            Edit::triangles_3D[i].points[j][0] += move_amountx;
                            Edit::triangles_3D[i].points[j][1] += move_amounty;
                            Edit::triangles_3D[i].points[j][2] += move_amountz;
                        }
                    }
                }
            }
            

            Edit::points_3D[Edit::points_3D_main_index][0] += move_amountx;
            Edit::points_3D[Edit::points_3D_main_index][1] += move_amounty;
            Edit::points_3D[Edit::points_3D_main_index][2] += move_amountz;

            for (int i = 0; i < Edit::points_points_3D[Edit::points_3D_main_index].size(); i++){
                Edit::points_points_3D[Edit::points_3D_main_index][i][0] += move_amountx;
                Edit::points_points_3D[Edit::points_3D_main_index][i][1] += move_amounty;
                Edit::points_points_3D[Edit::points_3D_main_index][i][2] += move_amountz;
            }

            

        }



    }

    Edit::prev_anglex_diff = graphics->anglex_diff;
    Edit::prev_angley_diff = graphics->angley_diff;

}