#include <GL/glut.h>
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

#include "Graphics.h"

        
Graphics::Graphics(){

    zscreendiff = 1000;
    playerx = 960;
    playery = 1060;
    //playery = 900;
    playerz = 1000;
    near_plane = 0.01;

    anglex_adj = 0;
    // double fov = 90.0; // Field of view in degrees
    pi = 3.141592653589793;
    // zscreendiff = 1920 / (2 * tan(fov * 0.5 * pi / 180.0));

    double x_start = -19040;
    double x_stop = 20960;
    //double z_start = 100;
    double z_start = 500;
    double z_stop = 40500;

    // x_start = -100;
    // x_stop = 1000;
    // z_start = 500;
    // z_stop = 1000;

    floor_points_3D.emplace_back();

    int i = 0;
    for (double x = x_start; x < x_stop; x += 100){
        floor_points_3D[0].emplace_back();
        floor_points_3D[0][i].emplace_back();
        floor_points_3D[0][i][0].emplace_back(0);
        floor_points_3D[0][i][0].emplace_back(0);
        floor_points_3D[0][i][0].emplace_back(0);
        floor_points_3D[0][i][0][0] = x;
        floor_points_3D[0][i][0][1] = 1080;
        floor_points_3D[0][i][0][2] = z_start;

        floor_points_3D[0][i].emplace_back();
        floor_points_3D[0][i][1].emplace_back(0);
        floor_points_3D[0][i][1].emplace_back(0);
        floor_points_3D[0][i][1].emplace_back(0);
        floor_points_3D[0][i][1][0] = x;
        floor_points_3D[0][i][1][1] = 1080;
        floor_points_3D[0][i][1][2] = z_stop;

        i++;
    }


    floor_points_3D.emplace_back();

    i = 0;
    for (double z = z_start; z < z_stop; z += 100){
        floor_points_3D[1].emplace_back();
        floor_points_3D[1][i].emplace_back();
        floor_points_3D[1][i][0].emplace_back(0);
        floor_points_3D[1][i][0].emplace_back(0);
        floor_points_3D[1][i][0].emplace_back(0);
        floor_points_3D[1][i][0][0] = x_start;
        floor_points_3D[1][i][0][1] = 1080;
        floor_points_3D[1][i][0][2] = z;

        floor_points_3D[1][i].emplace_back();
        floor_points_3D[1][i][1].emplace_back(0);
        floor_points_3D[1][i][1].emplace_back(0);
        floor_points_3D[1][i][1].emplace_back(0);
        floor_points_3D[1][i][1][0] = x_stop;
        floor_points_3D[1][i][1][1] = 1080;
        floor_points_3D[1][i][1][2] = z;

        i++;
    }

}


std::vector<std::vector<double>> Graphics::make_sphere(std::vector<double> center, int radius, int num_points){

    //(x - 960)^2 + (y - 540)^2 + (z - 10)^2 = radius^2

    std::vector<std::vector<double>> sphere_points_3D;

    if (num_points == 6){

        // 6-sided geodesic dome

        sphere_points_3D = std::vector<std::vector<double>>(6, std::vector<double>(3, 0));

        sphere_points_3D[0][0] = 960 - radius;
        sphere_points_3D[0][1] = 540;
        sphere_points_3D[0][2] = 25;

        sphere_points_3D[1][0] = 960 + radius;
        sphere_points_3D[1][1] = 540;
        sphere_points_3D[1][2] = 25;

        sphere_points_3D[2][0] = 960;
        sphere_points_3D[2][1] = 540 - radius;
        sphere_points_3D[2][2] = 25;

        sphere_points_3D[3][0] = 960;
        sphere_points_3D[3][1] = 540 + radius;
        sphere_points_3D[3][2] = 25;

        sphere_points_3D[4][0] = 960;
        sphere_points_3D[4][1] = 540;
        sphere_points_3D[4][2] = 25 + radius;

        sphere_points_3D[5][0] = 960;
        sphere_points_3D[5][1] = 540;
        sphere_points_3D[5][2] = 25 - radius;

    } else if (num_points == 12){

        // copied attempt at 12-sided geodesic sphere (based on golden ratio):

        double phi = 1.61803;
        sphere_points_3D = { {center[0] + -1 * radius,  center[1] + phi * radius,  center[2] + 0 * radius}, {center[0] + 1 * radius,  center[1] + phi * radius,  center[2] + 0 * radius}, {center[0] + -1 * radius, center[1] + -phi * radius,  center[2] + 0 * radius}, {center[0] + 1 * radius, center[1] + -phi * radius,  center[2] + 0 * radius},
            {center[0] + 0 * radius, center[1] + -1 * radius,  center[2] + phi * radius}, {center[0] + 0 * radius,  center[1] + 1 * radius,  center[2] + phi * radius}, {center[0] + 0 * radius, center[1] + -1 * radius, center[2] + -phi * radius}, {center[0] + 0 * radius,  center[1] + 1 * radius, center[2] + -phi * radius},
            {center[0] + phi * radius,  center[1] + 0 * radius, center[2] + -1 * radius}, {center[0] + phi * radius,  center[1] + 0 * radius,  center[2] + 1 * radius}, {center[0] + -phi * radius,  center[1] + 0 * radius, center[2] + -1 * radius}, {center[0] + -phi * radius,  center[1] + 0 * radius,  center[2] + 1 * radius} };
    }

    return sphere_points_3D;
}


std::vector<std::vector<double>> Graphics::make_box(std::vector<double> center, double top_length, double side_length, double depth){
    std::vector<std::vector<double>> rect_points_3D(8, std::vector<double>(3, 0));

    rect_points_3D[0][0] = center[0] - top_length / 2;
    rect_points_3D[0][1] = center[1] - side_length / 2;
    rect_points_3D[0][2] = center[2] + depth / 2;

    rect_points_3D[1][0] = center[0] + top_length / 2;
    rect_points_3D[1][1] = center[1] - side_length / 2;
    rect_points_3D[1][2] = center[2] + depth / 2;

    rect_points_3D[2][0] = center[0] - top_length / 2;
    rect_points_3D[2][1] = center[1] + side_length / 2;
    rect_points_3D[2][2] = center[2] + depth / 2;

    rect_points_3D[3][0] = center[0] + top_length / 2;
    rect_points_3D[3][1] = center[1] + side_length / 2;
    rect_points_3D[3][2] = center[2] + depth / 2;

    rect_points_3D[4][0] = center[0] - top_length / 2;
    rect_points_3D[4][1] = center[1] - side_length / 2;
    rect_points_3D[4][2] = center[2] - depth / 2;

    rect_points_3D[5][0] = center[0] + top_length / 2;
    rect_points_3D[5][1] = center[1] - side_length / 2;
    rect_points_3D[5][2] = center[2] - depth / 2;

    rect_points_3D[6][0] = center[0] - top_length / 2;
    rect_points_3D[6][1] = center[1] + side_length / 2;
    rect_points_3D[6][2] = center[2] - depth / 2;

    rect_points_3D[7][0] = center[0] + top_length / 2;
    rect_points_3D[7][1] = center[1] + side_length / 2;
    rect_points_3D[7][2] = center[2] - depth / 2;

    return rect_points_3D;
}


std::vector<std::vector<std::vector<std::vector<double>>>> Graphics::find_triangle_points_sphere(std::vector<std::vector<double>> sphere_points_3D){

    std::vector<std::vector<std::vector<std::vector<double>>>> triangle_points_3D;


    for (int i = 0; i < sphere_points_3D.size(); i++){

        triangle_points_3D.emplace_back();

        // Determining shortest line between each point and all other points.
        double shortest = 99999;
        double dist1;

        for (int j = 0; j < sphere_points_3D.size(); j++){
            if (i == j){continue;}
            double xdist = std::abs(sphere_points_3D[j][0] - sphere_points_3D[i][0]);
            double ydist = std::abs(sphere_points_3D[j][1] - sphere_points_3D[i][1]);
            double zdist = std::abs(sphere_points_3D[j][2] - sphere_points_3D[i][2]);

            // int largest = std::max(xdist, std::max(ydist, zdist));
            // int second_largest = std::max(xdist == largest ? -1 : xdist, std::max(ydist == largest ? -1 : ydist, zdist == largest ? -1 : zdist));

            double larger1 = 0;
            double larger2 = 0;
            if (xdist <= ydist && xdist <= zdist){
                larger1 = ydist;
                larger2 = zdist;
            } else if(ydist <= xdist && ydist <= zdist){
                larger1 = xdist;
                larger2 = zdist;
            } else if(zdist <= xdist && zdist <= ydist){
                larger1 = xdist;
                larger2 = ydist;
            }

            dist1 = std::sqrt(larger1*larger1 + larger2*larger2);

            if (dist1 < shortest){
                shortest = dist1;
            }
        }

        // Finding all adjacent points with shortest line between points.
        std::vector<double> adj_points;
        for (int j = 0; j < sphere_points_3D.size(); j++){
            if (i == j){continue;}
            double xdist = std::abs(sphere_points_3D[j][0] - sphere_points_3D[i][0]);
            double ydist = std::abs(sphere_points_3D[j][1] - sphere_points_3D[i][1]);
            double zdist = std::abs(sphere_points_3D[j][2] - sphere_points_3D[i][2]);

            double larger1 = 0;
            double larger2 = 0;
            if (xdist <= ydist && xdist <= zdist){
                larger1 = ydist;
                larger2 = zdist;
            } else if(ydist <= xdist && ydist <= zdist){
                larger1 = xdist;
                larger2 = zdist;
            } else if(zdist <= xdist && zdist <= ydist){
                larger1 = xdist;
                larger2 = ydist;
            }

            dist1 = std::sqrt(larger1*larger1 + larger2*larger2);
            if (dist1 > shortest - 1 && dist1 < shortest + 1){
                adj_points.emplace_back(j);
            }
        }

        // Determining if adjacent points have same shortest line between adjacent point's adjcent points so that a full equilateral triangle is found.
        double dist2;
        double dist3;

        for (int a = 0; a < adj_points.size(); a++){
            triangle_points_3D[i].emplace_back();

            for (int k = 0; k < sphere_points_3D.size(); k++){
                if (k == i || k == adj_points[a] || i == adj_points[a]){continue;}
                double xdist = std::abs(sphere_points_3D[k][0] - sphere_points_3D[adj_points[a]][0]);
                double ydist = std::abs(sphere_points_3D[k][1] - sphere_points_3D[adj_points[a]][1]);
                double zdist = std::abs(sphere_points_3D[k][2] - sphere_points_3D[adj_points[a]][2]);

                double larger1 = 0;
                double larger2 = 0;
                if (xdist <= ydist && xdist <= zdist){
                    larger1 = ydist;
                    larger2 = zdist;
                } else if(ydist <= xdist && ydist <= zdist){
                    larger1 = xdist;
                    larger2 = zdist;
                } else if(zdist <= xdist && zdist <= ydist){
                    larger1 = xdist;
                    larger2 = ydist;
                }

                dist2 = std::sqrt(larger1*larger1 + larger2*larger2);

                xdist = std::abs(sphere_points_3D[k][0] - sphere_points_3D[i][0]);
                ydist = std::abs(sphere_points_3D[k][1] - sphere_points_3D[i][1]);
                zdist = std::abs(sphere_points_3D[k][2] - sphere_points_3D[i][2]);

                larger1 = 0;
                larger2 = 0;
                if (xdist <= ydist && xdist <= zdist){
                    larger1 = ydist;
                    larger2 = zdist;
                } else if(ydist <= xdist && ydist <= zdist){
                    larger1 = xdist;
                    larger2 = zdist;
                } else if(zdist <= xdist && zdist <= ydist){
                    larger1 = xdist;
                    larger2 = ydist;
                }

                dist3 = std::sqrt(larger1*larger1 + larger2*larger2);

                if (dist2 > shortest - 1 && dist2 < shortest + 1 && dist3 > shortest - 1 && dist3 < shortest + 1){
                    
                    triangle_points_3D[i][triangle_points_3D[i].size()-1].emplace_back(std::vector<double>(3, 0));
                    triangle_points_3D[i][triangle_points_3D[i].size()-1][0][0] = sphere_points_3D[i][0];
                    triangle_points_3D[i][triangle_points_3D[i].size()-1][0][1] = sphere_points_3D[i][1];
                    triangle_points_3D[i][triangle_points_3D[i].size()-1][0][2] = sphere_points_3D[i][2];

                    triangle_points_3D[i][triangle_points_3D[i].size()-1].emplace_back(std::vector<double>(3, 0));
                    triangle_points_3D[i][triangle_points_3D[i].size()-1][1][0] = sphere_points_3D[adj_points[a]][0];
                    triangle_points_3D[i][triangle_points_3D[i].size()-1][1][1] = sphere_points_3D[adj_points[a]][1];
                    triangle_points_3D[i][triangle_points_3D[i].size()-1][1][2] = sphere_points_3D[adj_points[a]][2];

                    triangle_points_3D[i][triangle_points_3D[i].size()-1].emplace_back(std::vector<double>(3, 0));
                    triangle_points_3D[i][triangle_points_3D[i].size()-1][2][0] = sphere_points_3D[k][0];
                    triangle_points_3D[i][triangle_points_3D[i].size()-1][2][1] = sphere_points_3D[k][1];
                    triangle_points_3D[i][triangle_points_3D[i].size()-1][2][2] = sphere_points_3D[k][2];
                    break;
                }
            }
        }
    }
    
    return triangle_points_3D;
}


std::vector<std::vector<std::vector<std::vector<int>>>> Graphics::compute_2D_lines(std::vector<std::vector<std::vector<std::vector<double>>>> floor_points_3D){

    std::vector<std::vector<std::vector<std::vector<int>>>> floor_points_2D;

    // Iterating through all points on an object to compute the 2D window view point counterparts for a 3D object as observed by an eye behind the window.
    for (int i = 0; i < floor_points_3D.size(); i++){
        floor_points_2D.emplace_back();

        for (int j = 0; j < floor_points_3D[i].size(); j++){
            floor_points_2D[i].emplace_back();
            

            double x_diff1 = floor_points_3D[i][j][0][0] - playerx;
            double y_diff1 = floor_points_3D[i][j][0][1] - playery;
            double z_diff1 = floor_points_3D[i][j][0][2] - playerz;

            double x_diff2 = floor_points_3D[i][j][1][0] - playerx;
            double y_diff2 = floor_points_3D[i][j][1][1] - playery;
            double z_diff2 = floor_points_3D[i][j][1][2] - playerz;



            floor_points_2D[i][j].emplace_back();
            floor_points_2D[i][j][0].emplace_back(0);
            floor_points_2D[i][j][0].emplace_back(0);

            double anglex1 = atan2(x_diff1, z_diff1);
            //int x1 = (int) (tan(anglex1) * zscreendiff);

            double angley1 = atan2(y_diff1, z_diff1);
            //int y1 = (int) (tan(angley1) * zscreendiff);

            double anglex1_turn = anglex_adj - anglex1;


            floor_points_2D[i][j].emplace_back();
            floor_points_2D[i][j][1].emplace_back(0);
            floor_points_2D[i][j][1].emplace_back(0);

            double anglex2 = atan2(x_diff2, z_diff2);
            //int x2 = (int) (tan(anglex2) * zscreendiff);

            double angley2 = atan2(y_diff2, z_diff2);
            //int y2 = (int) (tan(angley2) * zscreendiff);

            double anglex2_turn = anglex_adj - anglex2;


            double hyp1 = sqrt(x_diff1 * x_diff1 + z_diff1 * z_diff1);
            double hyp2 = sqrt(x_diff2 * x_diff2 + z_diff2 * z_diff2);


            double x1_turn_clip = sin(anglex1_turn) * hyp1;
            double y1_turn_clip = y_diff1;
            double z1_turn_clip = cos(anglex1_turn) * hyp1;

            double x2_turn_clip = sin(anglex2_turn) * hyp2;
            double y2_turn_clip = y_diff2;
            double z2_turn_clip = cos(anglex2_turn) * hyp2;



            // Determining if clipping is necessary (when z value reaches behind player).
            if (z1_turn_clip < near_plane && z2_turn_clip < near_plane){
                floor_points_2D[i][j][0][0] = -10000;
                floor_points_2D[i][j][0][1] = -10000;

                floor_points_2D[i][j][1][0] = -10000;
                floor_points_2D[i][j][1][1] = -10000;

            } else if (z1_turn_clip < near_plane){

                double t = (near_plane - z1_turn_clip) / (z2_turn_clip - z1_turn_clip); // Calculate interpolation factor
                x1_turn_clip = x1_turn_clip + t * (x2_turn_clip - x1_turn_clip);        // Interpolate x
                z1_turn_clip = near_plane;                                              // Set z to near plane

            } else if (z2_turn_clip < near_plane){
                
                double t = (near_plane - z2_turn_clip) / (z1_turn_clip - z2_turn_clip); // Calculate interpolation factor
                x2_turn_clip = x2_turn_clip + t * (x1_turn_clip - x2_turn_clip);        // Interpolate x
                z2_turn_clip = near_plane;                                              // Set z to near plane

            }


            anglex1 = atan2(x1_turn_clip, z1_turn_clip);
            int x1_turn_2D = (int) (tan(anglex1) * zscreendiff);

            angley1 = atan2(y1_turn_clip, z1_turn_clip);
            int y1_turn_2D = (int) (tan(angley1) * zscreendiff);


            anglex2 = atan2(x2_turn_clip, z2_turn_clip);
            int x2_turn_2D = (int) (tan(anglex2) * zscreendiff);

            angley2 = atan2(y2_turn_clip, z2_turn_clip);
            int y2_turn_2D = (int) (tan(angley2) * zscreendiff);


            if (z1_turn_clip >= near_plane && z2_turn_clip >= near_plane){
                floor_points_2D[i][j][0][0] = (int) (960 - x1_turn_2D);
                floor_points_2D[i][j][0][1] = (int) (540 + y1_turn_2D);

                floor_points_2D[i][j][1][0] = (int) (960 - x2_turn_2D);
                floor_points_2D[i][j][1][1] = (int) (540 + y2_turn_2D);
            }
        }
    }


    return floor_points_2D;

}


std::vector<std::vector<int>> Graphics::compute_2D_box(std::vector<std::vector<double>> rect_points_3D){

    std::vector<std::vector<int>> rect_points_2D;

    // Iterating through all points on an object to compute the 2D window view point counterparts for a 3D object as observed by an eye behind the window.
    for (int i = 0; i < rect_points_3D.size(); i++){
        rect_points_2D.emplace_back();

        rect_points_2D[i].emplace_back(0);
        rect_points_2D[i].emplace_back(0);

        double anglex = atan2(rect_points_3D[i][0] - playerx, rect_points_3D[i][2] - playerz);
        //int x = (int) (tan(anglex) * zscreendiff);

        double angley = atan2(rect_points_3D[i][1] - playery, rect_points_3D[i][2] - playerz);
        int y = (int) (tan(angley) * zscreendiff);


        double anglex_turn = anglex_adj - anglex;
        double hyp = (rect_points_3D[i][0] - playerx) / sin(anglex);
        double z_turn_diff = cos(anglex_turn) * hyp;

        if (z_turn_diff < near_plane){
            rect_points_2D[i][0] = -10000;
            rect_points_2D[i][1] = -10000;    

        } else{

            int x = (int) (tan(anglex_turn) * zscreendiff);

            rect_points_2D[i][0] = (int) (960 - x);
            rect_points_2D[i][1] = (int) (540 + y);
        }
    }

    return rect_points_2D;

}


std::vector<std::vector<std::vector<std::vector<int>>>> Graphics::compute_2D_triangles(std::vector<std::vector<std::vector<std::vector<double>>>> triangle_points_3D){
    std::vector<std::vector<std::vector<std::vector<int>>>> object_2D(
        triangle_points_3D.size(), std::vector<std::vector<std::vector<int>>>(
                triangle_points_3D[0].size(), std::vector<std::vector<int>>(
                            3, std::vector<int>(2, 0))));

    // Iterating through all points on an object to compute the 2D window view point counterparts for a 3D object as observed by an eye behind the window.
    for (int i = 0; i < triangle_points_3D.size(); i++){
        for (int j = 0; j < triangle_points_3D[0].size(); j++){
            for (int k = 0; k < 3; k++){
                
                double anglex = atan2(triangle_points_3D[i][j][k][0] - playerx, triangle_points_3D[i][j][k][2] - playerz);
                //int x = (int) (tan(anglex) * zscreendiff);

                double angley = atan2(triangle_points_3D[i][j][k][1] - playery, triangle_points_3D[i][j][k][2] - playerz);
                int y = (int) (tan(angley) * zscreendiff);

                double anglex_turn = anglex_adj - anglex;
                double hyp = (triangle_points_3D[i][j][k][0] - playerx) / sin(anglex);
                double z_turn_diff = cos(anglex_turn) * hyp;

                if (z_turn_diff < near_plane){
                    object_2D[i][j][k][0] = -10000;
                    object_2D[i][j][k][1] = -10000;

                } else{
                    int x = (int) (tan(anglex_turn) * zscreendiff);

                    object_2D[i][j][k][0] = (int) (960 - x);
                    object_2D[i][j][k][1] = (int) (540 + y);
                }
            }
        }
    }

    return object_2D;

}


void Graphics::clear_draw_screen(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
    glClear(GL_COLOR_BUFFER_BIT);
}


void Graphics::draw_horizon(){

    glBegin(GL_LINES);
        glVertex2i(0, 540);
        glVertex2i(1920, 540);
    glEnd();

}


void Graphics::draw_floor_lines(std::vector<std::vector<std::vector<std::vector<int>>>> floor_points_2D){

    for (int i = 0; i < floor_points_2D.size(); i++){
        for (int j = 0; j < floor_points_2D[i].size(); j++){
            if (floor_points_2D[i][j][0][0] != -10000 && floor_points_2D[i][j][1][0] != -10000 &&
                    floor_points_2D[i][j][0][1] != -10000 && floor_points_2D[i][j][1][1] != -10000){
                

                glBegin(GL_LINES);
                    glVertex2i(floor_points_2D[i][j][0][0], floor_points_2D[i][j][0][1]);
                    glVertex2i(floor_points_2D[i][j][1][0], floor_points_2D[i][j][1][1]);
                glEnd();
            }
        }
    }

}


void Graphics::draw_full_triangles_sphere(std::vector<std::vector<std::vector<std::vector<int>>>> triangle_points_2D){

    for (int i = 0; i < triangle_points_2D.size(); i++){

        bool skip = false;
        for (int j = 0; j < triangle_points_2D[0].size(); j++){
            for (int k = 0; k < triangle_points_2D[0][0].size(); k++){
                if (triangle_points_2D[i][j][k][0] == -10000 && triangle_points_2D[i][j][k][1] == -10000 ) skip = true;
            }
        }

        if (!skip){

            for (int j = 0; j < triangle_points_2D[0].size(); j++){
                glBegin(GL_POLYGON);
                    glVertex2i(triangle_points_2D[i][j][0][0], triangle_points_2D[i][j][0][1]);
                    glVertex2i(triangle_points_2D[i][j][1][0], triangle_points_2D[i][j][1][1]);
                    glVertex2i(triangle_points_2D[i][j][2][0], triangle_points_2D[i][j][2][1]);
                glEnd();
            }
        }
    }
}


void Graphics::draw_hollow_triangles_sphere(std::vector<std::vector<std::vector<std::vector<int>>>> triangle_points_2D){

    for (int i = 0; i < triangle_points_2D.size(); i++){

        bool skip = false;
        for (int j = 0; j < triangle_points_2D[0].size(); j++){
            for (int k = 0; k < triangle_points_2D[0][0].size(); k++){
                if (triangle_points_2D[i][j][k][0] == -10000 && triangle_points_2D[i][j][k][1] == -10000 ) skip = true;
            }
        }

        if (!skip){

            for (int j = 0; j < triangle_points_2D[0].size(); j++){
                glBegin(GL_LINES);
                    glVertex2i(triangle_points_2D[i][j][0][0], triangle_points_2D[i][j][0][1]);
                    glVertex2i(triangle_points_2D[i][j][1][0], triangle_points_2D[i][j][1][1]);
                glEnd();

                glBegin(GL_LINES);
                    glVertex2i(triangle_points_2D[i][j][1][0], triangle_points_2D[i][j][1][1]);
                    glVertex2i(triangle_points_2D[i][j][2][0], triangle_points_2D[i][j][2][1]);
                glEnd();

                glBegin(GL_LINES);
                    glVertex2i(triangle_points_2D[i][j][2][0], triangle_points_2D[i][j][2][1]);
                    glVertex2i(triangle_points_2D[i][j][0][0], triangle_points_2D[i][j][0][1]);
                glEnd();
            }
        }
    }
}


void Graphics::draw_full_box(std::vector<std::vector<int>> rect_points_2D){

    bool skip = false;

    for (int i = 0; i < rect_points_2D.size(); i++){
        if (rect_points_2D[i][0] == -10000 && rect_points_2D[i][1] == -10000) skip = true;
    }

    if (!skip){

        glBegin(GL_POLYGON);
            glVertex2i(rect_points_2D[0][0], rect_points_2D[0][1]);
            glVertex2i(rect_points_2D[1][0], rect_points_2D[1][1]);
            glVertex2i(rect_points_2D[3][0], rect_points_2D[3][1]);
            glVertex2i(rect_points_2D[2][0], rect_points_2D[2][1]);
        glEnd();

        glBegin(GL_POLYGON);
            glVertex2i(rect_points_2D[2][0], rect_points_2D[2][1]);
            glVertex2i(rect_points_2D[0][0], rect_points_2D[0][1]);
            glVertex2i(rect_points_2D[4][0], rect_points_2D[4][1]);
            glVertex2i(rect_points_2D[6][0], rect_points_2D[6][1]);
        glEnd();

        glBegin(GL_POLYGON);
            glVertex2i(rect_points_2D[0][0], rect_points_2D[0][1]);
            glVertex2i(rect_points_2D[1][0], rect_points_2D[1][1]);
            glVertex2i(rect_points_2D[5][0], rect_points_2D[5][1]);
            glVertex2i(rect_points_2D[4][0], rect_points_2D[4][1]);
        glEnd();

        glBegin(GL_POLYGON);
            glVertex2i(rect_points_2D[5][0], rect_points_2D[5][1]);
            glVertex2i(rect_points_2D[1][0], rect_points_2D[1][1]);
            glVertex2i(rect_points_2D[3][0], rect_points_2D[3][1]);
            glVertex2i(rect_points_2D[7][0], rect_points_2D[7][1]);
        glEnd();

        glBegin(GL_POLYGON);
            glVertex2i(rect_points_2D[2][0], rect_points_2D[2][1]);
            glVertex2i(rect_points_2D[3][0], rect_points_2D[3][1]);
            glVertex2i(rect_points_2D[7][0], rect_points_2D[7][1]);
            glVertex2i(rect_points_2D[6][0], rect_points_2D[6][1]);
        glEnd();

        glBegin(GL_POLYGON);
            glVertex2i(rect_points_2D[4][0], rect_points_2D[4][1]);
            glVertex2i(rect_points_2D[5][0], rect_points_2D[5][1]);
            glVertex2i(rect_points_2D[7][0], rect_points_2D[7][1]);
            glVertex2i(rect_points_2D[6][0], rect_points_2D[6][1]);
        glEnd();
    }

}


void Graphics::draw_hollow_box(std::vector<std::vector<int>> rect_points_2D){

    bool skip = false;

    for (int i = 0; i < rect_points_2D.size(); i++){
        if (rect_points_2D[i][0] == -10000 && rect_points_2D[i][1] == -10000) skip = true;
    }

    if (!skip){

        glBegin(GL_LINE_LOOP);
            glVertex2i(rect_points_2D[0][0], rect_points_2D[0][1]);
            glVertex2i(rect_points_2D[1][0], rect_points_2D[1][1]);
            glVertex2i(rect_points_2D[3][0], rect_points_2D[3][1]);
            glVertex2i(rect_points_2D[2][0], rect_points_2D[2][1]);
        glEnd();

        glBegin(GL_LINE_LOOP);
            glVertex2i(rect_points_2D[2][0], rect_points_2D[2][1]);
            glVertex2i(rect_points_2D[0][0], rect_points_2D[0][1]);
            glVertex2i(rect_points_2D[4][0], rect_points_2D[4][1]);
            glVertex2i(rect_points_2D[6][0], rect_points_2D[6][1]);
        glEnd();

        glBegin(GL_LINE_LOOP);
            glVertex2i(rect_points_2D[0][0], rect_points_2D[0][1]);
            glVertex2i(rect_points_2D[1][0], rect_points_2D[1][1]);
            glVertex2i(rect_points_2D[5][0], rect_points_2D[5][1]);
            glVertex2i(rect_points_2D[4][0], rect_points_2D[4][1]);
        glEnd();

        glBegin(GL_LINE_LOOP);
            glVertex2i(rect_points_2D[5][0], rect_points_2D[5][1]);
            glVertex2i(rect_points_2D[1][0], rect_points_2D[1][1]);
            glVertex2i(rect_points_2D[3][0], rect_points_2D[3][1]);
            glVertex2i(rect_points_2D[7][0], rect_points_2D[7][1]);
        glEnd();

        glBegin(GL_LINE_LOOP);
            glVertex2i(rect_points_2D[2][0], rect_points_2D[2][1]);
            glVertex2i(rect_points_2D[3][0], rect_points_2D[3][1]);
            glVertex2i(rect_points_2D[7][0], rect_points_2D[7][1]);
            glVertex2i(rect_points_2D[6][0], rect_points_2D[6][1]);
        glEnd();

        glBegin(GL_LINE_LOOP);
            glVertex2i(rect_points_2D[4][0], rect_points_2D[4][1]);
            glVertex2i(rect_points_2D[5][0], rect_points_2D[5][1]);
            glVertex2i(rect_points_2D[7][0], rect_points_2D[7][1]);
            glVertex2i(rect_points_2D[6][0], rect_points_2D[6][1]);
        glEnd();
    }

}


void Graphics::set_color(int r, int g, int b){
    glColor3f(r, g, b); // Red color
}

void Graphics::present_frame(){
    // Present the rendered frame
    //glutSwapBuffers();
    glFlush();
}