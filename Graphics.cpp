#include <GL/glut.h>
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <list>

#include "Graphics.h"

        
Graphics::Graphics(){

    zscreendiff = 1000;
    playerx = 960;
    playery = 1060;
    playerz = 1000;
    // playerz = 0;
    near_plane = 0.1;

    anglex_diff = 0;
    angley_diff = 0;

    //double fov = 90.0; // Field of view in degrees
    pi = 3.141592653589793;
    //zscreendiff = 1920 / (2 * tan(fov * 0.5 * pi / 180.0));

    double x_start = -19040;
    double x_stop = 20960;

    //double z_start = 100;
    double z_start = 500;
    double z_stop = 40500;

    // x_start = -100;
    // x_stop = 1000;
    // z_start = 500;
    // z_stop = 1000;


    // Horizontal plane floor points
    // floor_points_3D.emplace_back();

    // int i = 0;
    // for (double x = x_start; x < x_stop; x += 100){
    //     floor_points_3D[0].emplace_back();
    //     floor_points_3D[0][i].emplace_back();
    //     floor_points_3D[0][i][0].emplace_back(0);
    //     floor_points_3D[0][i][0].emplace_back(0);
    //     floor_points_3D[0][i][0].emplace_back(0);
    //     floor_points_3D[0][i][0][0] = x;
    //     floor_points_3D[0][i][0][1] = 1080;
    //     floor_points_3D[0][i][0][2] = z_start;

    //     floor_points_3D[0][i].emplace_back();
    //     floor_points_3D[0][i][1].emplace_back(0);
    //     floor_points_3D[0][i][1].emplace_back(0);
    //     floor_points_3D[0][i][1].emplace_back(0);
    //     floor_points_3D[0][i][1][0] = x;
    //     floor_points_3D[0][i][1][1] = 1080;
    //     floor_points_3D[0][i][1][2] = z_stop;

    //     i++;
    // }


    // floor_points_3D.emplace_back();

    // i = 0;
    // for (double z = z_start; z < z_stop; z += 100){
    //     floor_points_3D[1].emplace_back();
    //     floor_points_3D[1][i].emplace_back();
    //     floor_points_3D[1][i][0].emplace_back(0);
    //     floor_points_3D[1][i][0].emplace_back(0);
    //     floor_points_3D[1][i][0].emplace_back(0);
    //     floor_points_3D[1][i][0][0] = x_start;
    //     floor_points_3D[1][i][0][1] = 1080;
    //     floor_points_3D[1][i][0][2] = z;

    //     floor_points_3D[1][i].emplace_back();
    //     floor_points_3D[1][i][1].emplace_back(0);
    //     floor_points_3D[1][i][1].emplace_back(0);
    //     floor_points_3D[1][i][1].emplace_back(0);
    //     floor_points_3D[1][i][1][0] = x_stop;
    //     floor_points_3D[1][i][1][1] = 1080;
    //     floor_points_3D[1][i][1][2] = z;

    //     i++;
    // }

    





    // test_points_3D.emplace_back();

    // test_points_3D[0].emplace_back();
    // test_points_3D[0][0].emplace_back();
    
    //test_points_3D[0][0] = make_sphere({(double)playerx, (double)playery, (double)playerz}, 3, 12);
    //test_points_3D[0][0] = make_sphere({(double)0, (double)0, (double)0}, 3, 12);

}


std::vector<std::vector<double>> Graphics::make_sphere(std::vector<double> center, int radius, int num_points){

    //(x - 960)^2 + (y - 540)^2 + (z - 10)^2 = radius^2

    std::vector<std::vector<double>> sphere_points_3D;

    if (num_points == 6){

        // 6-sided geodesic dome

        sphere_points_3D = std::vector<std::vector<double>>(6, std::vector<double>(3, 0));

        sphere_points_3D[0][0] = center[0] - radius;
        sphere_points_3D[0][1] = center[1];
        sphere_points_3D[0][2] = center[2];

        sphere_points_3D[1][0] = center[0] + radius;
        sphere_points_3D[1][1] = center[1];
        sphere_points_3D[1][2] = center[2];

        sphere_points_3D[2][0] = center[0];
        sphere_points_3D[2][1] = center[1] - radius;
        sphere_points_3D[2][2] = center[2];

        sphere_points_3D[3][0] = center[0];
        sphere_points_3D[3][1] = center[1] + radius;
        sphere_points_3D[3][2] = center[2];

        sphere_points_3D[4][0] = center[0];
        sphere_points_3D[4][1] = center[1];
        sphere_points_3D[4][2] = center[2] + radius;

        sphere_points_3D[5][0] = center[0];
        sphere_points_3D[5][1] = center[1];
        sphere_points_3D[5][2] = center[2] - radius;

    } else if (num_points == 12){

        // copied attempt at 12-sided geodesic sphere AKA icosaphere (based on golden ratio):

        double phi = 1.6180339887;
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


std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> Graphics::find_triangle_points_sphere(std::vector<std::vector<double>> sphere_points_3D){

    std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> triangle_points_3D_sphere;

    for (int i = 0; i < sphere_points_3D.size(); i++){

        triangle_points_3D_sphere.emplace_back();

        // Determining shortest line between each point and all other points.
        double shortest = 99999999;
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
            }else if (ydist <= xdist && ydist <= zdist){
                larger1 = xdist;
                larger2 = zdist;
            }else if (zdist <= xdist && zdist <= ydist){
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
            }else if (ydist <= xdist && ydist <= zdist){
                larger1 = xdist;
                larger2 = zdist;
            }else if (zdist <= xdist && zdist <= ydist){
                larger1 = xdist;
                larger2 = ydist;
            }

            dist1 = std::sqrt(larger1*larger1 + larger2*larger2);
            if (dist1 > shortest - shortest * 0.1 && dist1 < shortest + shortest * 0.1){
                adj_points.emplace_back(j);
            }
        }

        // Determining if adjacent points have same shortest line between adjacent point's adjcent points so that a full equilateral triangle is found.
        double dist2;
        double dist3;

        for (int a = 0; a < adj_points.size(); a++){

            triangle_points_3D_sphere[i].emplace_back();

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
                }else if (ydist <= xdist && ydist <= zdist){
                    larger1 = xdist;
                    larger2 = zdist;
                }else if (zdist <= xdist && zdist <= ydist){
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
                }else if (ydist <= xdist && ydist <= zdist){
                    larger1 = xdist;
                    larger2 = zdist;
                }else if (zdist <= xdist && zdist <= ydist){
                    larger1 = xdist;
                    larger2 = ydist;
                }

                dist3 = std::sqrt(larger1*larger1 + larger2*larger2);
                    
                if (dist2 > shortest - shortest * 0.1 && dist2 < shortest + shortest * 0.1 && dist3 > shortest - shortest * 0.1 && dist3 < shortest + shortest * 0.1){

                    triangle_points_3D_sphere[i][triangle_points_3D_sphere[i].size()-1].emplace_back();

                    triangle_points_3D_sphere[i][triangle_points_3D_sphere[i].size()-1][triangle_points_3D_sphere[i][triangle_points_3D_sphere[i].size()-1].size()-1].emplace_back(std::vector<double>(3, 0));
                    triangle_points_3D_sphere[i][triangle_points_3D_sphere[i].size()-1][triangle_points_3D_sphere[i][triangle_points_3D_sphere[i].size()-1].size()-1][0][0] = sphere_points_3D[i][0];
                    triangle_points_3D_sphere[i][triangle_points_3D_sphere[i].size()-1][triangle_points_3D_sphere[i][triangle_points_3D_sphere[i].size()-1].size()-1][0][1] = sphere_points_3D[i][1];
                    triangle_points_3D_sphere[i][triangle_points_3D_sphere[i].size()-1][triangle_points_3D_sphere[i][triangle_points_3D_sphere[i].size()-1].size()-1][0][2] = sphere_points_3D[i][2];

                    triangle_points_3D_sphere[i][triangle_points_3D_sphere[i].size()-1][triangle_points_3D_sphere[i][triangle_points_3D_sphere[i].size()-1].size()-1].emplace_back(std::vector<double>(3, 0));
                    triangle_points_3D_sphere[i][triangle_points_3D_sphere[i].size()-1][triangle_points_3D_sphere[i][triangle_points_3D_sphere[i].size()-1].size()-1][1][0] = sphere_points_3D[adj_points[a]][0];
                    triangle_points_3D_sphere[i][triangle_points_3D_sphere[i].size()-1][triangle_points_3D_sphere[i][triangle_points_3D_sphere[i].size()-1].size()-1][1][1] = sphere_points_3D[adj_points[a]][1];
                    triangle_points_3D_sphere[i][triangle_points_3D_sphere[i].size()-1][triangle_points_3D_sphere[i][triangle_points_3D_sphere[i].size()-1].size()-1][1][2] = sphere_points_3D[adj_points[a]][2];

                    triangle_points_3D_sphere[i][triangle_points_3D_sphere[i].size()-1][triangle_points_3D_sphere[i][triangle_points_3D_sphere[i].size()-1].size()-1].emplace_back(std::vector<double>(3, 0));
                    triangle_points_3D_sphere[i][triangle_points_3D_sphere[i].size()-1][triangle_points_3D_sphere[i][triangle_points_3D_sphere[i].size()-1].size()-1][2][0] = sphere_points_3D[k][0];
                    triangle_points_3D_sphere[i][triangle_points_3D_sphere[i].size()-1][triangle_points_3D_sphere[i][triangle_points_3D_sphere[i].size()-1].size()-1][2][1] = sphere_points_3D[k][1];
                    triangle_points_3D_sphere[i][triangle_points_3D_sphere[i].size()-1][triangle_points_3D_sphere[i][triangle_points_3D_sphere[i].size()-1].size()-1][2][2] = sphere_points_3D[k][2];
                }
            }

        }
        
    }

    return triangle_points_3D_sphere;
}


std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>>> Graphics::clip_triangle_points_sphere(std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> triangle_points_3D_sphere){

    std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>>> clipped_polygon_points_3D_sphere;

    for (int i = 0; i < triangle_points_3D_sphere.size(); i++){
        clipped_polygon_points_3D_sphere.emplace_back();

        for (int j = 0; j < triangle_points_3D_sphere[i].size(); j++){
            clipped_polygon_points_3D_sphere[i].emplace_back();

            for (int k = 0; k < triangle_points_3D_sphere[i][j].size(); k++){
                clipped_polygon_points_3D_sphere[i][j].emplace_back();

                std::vector<std::vector<double>> line1;
                line1.emplace_back();
                line1[0].emplace_back(triangle_points_3D_sphere[i][j][k][0][0]);
                line1[0].emplace_back(triangle_points_3D_sphere[i][j][k][0][1]);
                line1[0].emplace_back(triangle_points_3D_sphere[i][j][k][0][2]);

                line1.emplace_back();
                line1[1].emplace_back(triangle_points_3D_sphere[i][j][k][1][0]);
                line1[1].emplace_back(triangle_points_3D_sphere[i][j][k][1][1]);
                line1[1].emplace_back(triangle_points_3D_sphere[i][j][k][1][2]);

                std::vector<double> clipped_coor_diffs_line1 = clip_3D_line(line1);



                std::vector<std::vector<double>> line2;
                line2.emplace_back();
                line2[0].emplace_back(triangle_points_3D_sphere[i][j][k][1][0]);
                line2[0].emplace_back(triangle_points_3D_sphere[i][j][k][1][1]);
                line2[0].emplace_back(triangle_points_3D_sphere[i][j][k][1][2]);

                line2.emplace_back();
                line2[1].emplace_back(triangle_points_3D_sphere[i][j][k][2][0]);
                line2[1].emplace_back(triangle_points_3D_sphere[i][j][k][2][1]);
                line2[1].emplace_back(triangle_points_3D_sphere[i][j][k][2][2]);

                std::vector<double> clipped_coor_diffs_line2 = clip_3D_line(line2);



                std::vector<std::vector<double>> line3;

                line3.emplace_back();
                line3[0].emplace_back(triangle_points_3D_sphere[i][j][k][2][0]);
                line3[0].emplace_back(triangle_points_3D_sphere[i][j][k][2][1]);
                line3[0].emplace_back(triangle_points_3D_sphere[i][j][k][2][2]);

                line3.emplace_back();
                line3[1].emplace_back(triangle_points_3D_sphere[i][j][k][0][0]);
                line3[1].emplace_back(triangle_points_3D_sphere[i][j][k][0][1]);
                line3[1].emplace_back(triangle_points_3D_sphere[i][j][k][0][2]);

                std::vector<double> clipped_coor_diffs_line3 = clip_3D_line(line3);

                


                std::vector<std::vector<double>> clipped_coor_line1;


                if (line1[0][0] != -100000 && line1[0][1] != -100000 && line1[0][2] != -100000 && 
                        line1[1][0] != -100000 && line1[1][1] != -100000 && line1[1][2] != -100000){

                    clipped_coor_line1.emplace_back();
                    clipped_coor_line1[0].emplace_back(playerx - clipped_coor_diffs_line1[0]); //Not sure why this is "playerx - clipped_coor_diffs_line1[0]" and not the reverse "clipped_coor_diffs_line1[0] + playerx" that is done in function clip_3D_line() but idk.
                    clipped_coor_line1[0].emplace_back(playery + clipped_coor_diffs_line1[1]);
                    clipped_coor_line1[0].emplace_back(playerz + clipped_coor_diffs_line1[2]);


                    clipped_coor_line1.emplace_back();
                    clipped_coor_line1[1].emplace_back(playerx - clipped_coor_diffs_line1[3]);
                    clipped_coor_line1[1].emplace_back(playery + clipped_coor_diffs_line1[4]);
                    clipped_coor_line1[1].emplace_back(playerz + clipped_coor_diffs_line1[5]);

                }else{

                    clipped_coor_line1.emplace_back();
                    clipped_coor_line1[0].emplace_back(-100000);
                    clipped_coor_line1[0].emplace_back(-100000);
                    clipped_coor_line1[0].emplace_back(-100000);


                    clipped_coor_line1.emplace_back();
                    clipped_coor_line1[1].emplace_back(-100000);
                    clipped_coor_line1[1].emplace_back(-100000);
                    clipped_coor_line1[1].emplace_back(-100000);
                }


                


                std::vector<std::vector<double>> clipped_coor_line2;

                if (line2[0][0] != -100000 && line2[0][1] != -100000 && line2[0][2] != -100000 && 
                        line2[1][0] != -100000 && line2[1][1] != -100000 && line2[1][2] != -100000){

                    clipped_coor_line2.emplace_back();
                    clipped_coor_line2[0].emplace_back(playerx - clipped_coor_diffs_line2[0]); //Not sure why this is "playerx - clipped_coor_diffs_line2[0]" and not the reverse "clipped_coor_diffs_line2[0] + playerx" that is done in function clip_3D_line() but idk.
                    clipped_coor_line2[0].emplace_back(playery + clipped_coor_diffs_line2[1]);
                    clipped_coor_line2[0].emplace_back(playerz + clipped_coor_diffs_line2[2]);


                    clipped_coor_line2.emplace_back();
                    clipped_coor_line2[1].emplace_back(playerx - clipped_coor_diffs_line2[3]);
                    clipped_coor_line2[1].emplace_back(playery + clipped_coor_diffs_line2[4]);
                    clipped_coor_line2[1].emplace_back(playerz + clipped_coor_diffs_line2[5]);

                }else{

                    clipped_coor_line2.emplace_back();
                    clipped_coor_line2[0].emplace_back(-100000);
                    clipped_coor_line2[0].emplace_back(-100000);
                    clipped_coor_line2[0].emplace_back(-100000);


                    clipped_coor_line2.emplace_back();
                    clipped_coor_line2[1].emplace_back(-100000);
                    clipped_coor_line2[1].emplace_back(-100000);
                    clipped_coor_line2[1].emplace_back(-100000);
                }


                std::vector<std::vector<double>> clipped_coor_line3;

                if (line3[0][0] != -100000 && line3[0][1] != -100000 && line3[0][2] != -100000 && 
                        line3[1][0] != -100000 && line3[1][1] != -100000 && line3[1][2] != -100000){

                    clipped_coor_line3.emplace_back();
                    clipped_coor_line3[0].emplace_back(playerx - clipped_coor_diffs_line3[0]); //Not sure why this is "playerx - clipped_coor_diffs_line3[0]" and not the reverse "clipped_coor_diffs_line3[0] + playerx" that is done in function clip_3D_line() but idk.
                    clipped_coor_line3[0].emplace_back(playery + clipped_coor_diffs_line3[1]);
                    clipped_coor_line3[0].emplace_back(playerz + clipped_coor_diffs_line3[2]);


                    clipped_coor_line3.emplace_back();
                    clipped_coor_line3[1].emplace_back(playerx - clipped_coor_diffs_line3[3]);
                    clipped_coor_line3[1].emplace_back(playery + clipped_coor_diffs_line3[4]);
                    clipped_coor_line3[1].emplace_back(playerz + clipped_coor_diffs_line3[5]);

                }else{

                    clipped_coor_line3.emplace_back();
                    clipped_coor_line3[0].emplace_back(-100000);
                    clipped_coor_line3[0].emplace_back(-100000);
                    clipped_coor_line3[0].emplace_back(-100000);


                    clipped_coor_line3.emplace_back();
                    clipped_coor_line3[1].emplace_back(-100000);
                    clipped_coor_line3[1].emplace_back(-100000);
                    clipped_coor_line3[1].emplace_back(-100000);
                }


                clipped_polygon_points_3D_sphere[i][j][k].emplace_back();
                clipped_polygon_points_3D_sphere[i][j][k][0].emplace_back();
                clipped_polygon_points_3D_sphere[i][j][k][0][0].emplace_back(clipped_coor_line1[0][0]);
                clipped_polygon_points_3D_sphere[i][j][k][0][0].emplace_back(clipped_coor_line1[0][1]);
                clipped_polygon_points_3D_sphere[i][j][k][0][0].emplace_back(clipped_coor_line1[0][2]);

                clipped_polygon_points_3D_sphere[i][j][k][0].emplace_back();
                clipped_polygon_points_3D_sphere[i][j][k][0][1].emplace_back(clipped_coor_line1[1][0]);
                clipped_polygon_points_3D_sphere[i][j][k][0][1].emplace_back(clipped_coor_line1[1][1]);
                clipped_polygon_points_3D_sphere[i][j][k][0][1].emplace_back(clipped_coor_line1[1][2]);



                clipped_polygon_points_3D_sphere[i][j][k].emplace_back();
                clipped_polygon_points_3D_sphere[i][j][k][1].emplace_back();
                clipped_polygon_points_3D_sphere[i][j][k][1][0].emplace_back(clipped_coor_line2[0][0]);
                clipped_polygon_points_3D_sphere[i][j][k][1][0].emplace_back(clipped_coor_line2[0][1]);
                clipped_polygon_points_3D_sphere[i][j][k][1][0].emplace_back(clipped_coor_line2[0][2]);

                clipped_polygon_points_3D_sphere[i][j][k][1].emplace_back();
                clipped_polygon_points_3D_sphere[i][j][k][1][1].emplace_back(clipped_coor_line2[1][0]);
                clipped_polygon_points_3D_sphere[i][j][k][1][1].emplace_back(clipped_coor_line2[1][1]);
                clipped_polygon_points_3D_sphere[i][j][k][1][1].emplace_back(clipped_coor_line2[1][2]);



                clipped_polygon_points_3D_sphere[i][j][k].emplace_back();
                clipped_polygon_points_3D_sphere[i][j][k][2].emplace_back();
                clipped_polygon_points_3D_sphere[i][j][k][2][0].emplace_back(clipped_coor_line3[0][0]);
                clipped_polygon_points_3D_sphere[i][j][k][2][0].emplace_back(clipped_coor_line3[0][1]);
                clipped_polygon_points_3D_sphere[i][j][k][2][0].emplace_back(clipped_coor_line3[0][2]);

                clipped_polygon_points_3D_sphere[i][j][k][2].emplace_back();
                clipped_polygon_points_3D_sphere[i][j][k][2][1].emplace_back(clipped_coor_line3[1][0]);
                clipped_polygon_points_3D_sphere[i][j][k][2][1].emplace_back(clipped_coor_line3[1][1]);
                clipped_polygon_points_3D_sphere[i][j][k][2][1].emplace_back(clipped_coor_line3[1][2]);
                
            }
        }
    }

    //return triangle_points_3D_sphere;
    return clipped_polygon_points_3D_sphere;
}


std::vector<std::vector<std::vector<std::vector<double>>>> Graphics::find_floor_lines_on_globe(std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> triangle_points_3D_sphere){
    std::vector<std::vector<std::vector<std::vector<double>>>> floor_points_3D;
    

    // Going through each triangle plane on the icosahedron globe and finding floor line start and end points based on scaled difference between points.
    floor_points_3D.emplace_back();
    floor_points_3D.emplace_back();
    // for (int i = 0; i < triangle_points_3D_sphere.size(); i++){
    //     for (int j = 0; j < triangle_points_3D_sphere[i].size(); j++){
    //         for (int l = 0; l < triangle_points_3D_sphere[i][j].size(); l++){

    std::vector<std::vector<std::vector<double>>> triangle_planes_already_lined;

    for (int i = 0; i < triangle_points_3D_sphere.size(); i++){
        for (int j = 0; j < triangle_points_3D_sphere[i].size(); j++){
            for (int l = 0; l < triangle_points_3D_sphere[i][j].size(); l++){
                

                // Checking to see if triangle plane has already been given floor lines. If so, it is skipped.
                int skip_count;
                bool skip = false;
                for (int t = 0; t < triangle_planes_already_lined.size(); t++){
                    skip_count = 0;

                    for (int p = 0; p < triangle_planes_already_lined[t].size(); p++){
                        for (int pp = 0; pp < triangle_points_3D_sphere[i][j][l].size(); pp++){

                            if (triangle_planes_already_lined[t][p][0] == triangle_points_3D_sphere[i][j][l][pp][0] &&
                                    triangle_planes_already_lined[t][p][1] == triangle_points_3D_sphere[i][j][l][pp][1] &&
                                    triangle_planes_already_lined[t][p][2] == triangle_points_3D_sphere[i][j][l][pp][2]){
                                skip_count++;
                            }

                        }

                    }

                    if (skip_count == 3){
                        skip = true;
                    }
                }


                if (!skip){
                    double xline_base1_start = triangle_points_3D_sphere[i][j][l][0][0];
                    double yline_base1_start = triangle_points_3D_sphere[i][j][l][0][1];
                    double zline_base1_start = triangle_points_3D_sphere[i][j][l][0][2];

                    double xline_base1_end = triangle_points_3D_sphere[i][j][l][1][0];
                    double yline_base1_end = triangle_points_3D_sphere[i][j][l][1][1];
                    double zline_base1_end = triangle_points_3D_sphere[i][j][l][1][2];
                    
                    double xline_base2_start = triangle_points_3D_sphere[i][j][l][2][0];
                    double yline_base2_start = triangle_points_3D_sphere[i][j][l][2][1];
                    double zline_base2_start = triangle_points_3D_sphere[i][j][l][2][2];

                    double xline_base2_end = triangle_points_3D_sphere[i][j][l][1][0];
                    double yline_base2_end = triangle_points_3D_sphere[i][j][l][1][1];
                    double zline_base2_end = triangle_points_3D_sphere[i][j][l][1][2];

                    double xline_base3_start = triangle_points_3D_sphere[i][j][l][0][0];
                    double yline_base3_start = triangle_points_3D_sphere[i][j][l][0][1];
                    double zline_base3_start = triangle_points_3D_sphere[i][j][l][0][2];

                    double xline_base3_end = triangle_points_3D_sphere[i][j][l][2][0];
                    double yline_base3_end = triangle_points_3D_sphere[i][j][l][2][1];
                    double zline_base3_end = triangle_points_3D_sphere[i][j][l][2][2];


                    // Scale determines the number of lines on icosaphere.
                    // Starting value and increment value should match and be evenly multiplied into 1.0.
                    for (double scale = 0.0; scale < 1.0; scale += 0.1){
                        int xline_start = (int) (xline_base1_start + scale * (xline_base1_end - xline_base1_start));
                        int yline_start = (int) (yline_base1_start + scale * (yline_base1_end - yline_base1_start));
                        int zline_start = (int) (zline_base1_start + scale * (zline_base1_end - zline_base1_start));

                        int xline_end = (int) (xline_base2_start + scale * (xline_base2_end - xline_base2_start));
                        int yline_end = (int) (yline_base2_start + scale * (yline_base2_end - yline_base2_start));
                        int zline_end = (int) (zline_base2_start + scale * (zline_base2_end - zline_base2_start));

                        floor_points_3D[0].emplace_back();
                        floor_points_3D[0][floor_points_3D[0].size() - 1].emplace_back();
                        floor_points_3D[0][floor_points_3D[0].size() - 1].emplace_back();

                        floor_points_3D[0][floor_points_3D[0].size() - 1][0].emplace_back(xline_start);
                        floor_points_3D[0][floor_points_3D[0].size() - 1][0].emplace_back(yline_start);
                        floor_points_3D[0][floor_points_3D[0].size() - 1][0].emplace_back(zline_start);

                        floor_points_3D[0][floor_points_3D[0].size() - 1][1].emplace_back(xline_end);
                        floor_points_3D[0][floor_points_3D[0].size() - 1][1].emplace_back(yline_end);
                        floor_points_3D[0][floor_points_3D[0].size() - 1][1].emplace_back(zline_end);



                        xline_start = (int) (xline_base1_start + scale * (xline_base1_end - xline_base1_start));
                        yline_start = (int) (yline_base1_start + scale * (yline_base1_end - yline_base1_start));
                        zline_start = (int) (zline_base1_start + scale * (zline_base1_end - zline_base1_start));

                        xline_end = (int) (xline_base3_start + scale * (xline_base3_end - xline_base3_start));
                        yline_end = (int) (yline_base3_start + scale * (yline_base3_end - yline_base3_start));
                        zline_end = (int) (zline_base3_start + scale * (zline_base3_end - zline_base3_start));

                        floor_points_3D[1].emplace_back();
                        floor_points_3D[1][floor_points_3D[0].size() - 1].emplace_back();
                        floor_points_3D[1][floor_points_3D[0].size() - 1].emplace_back();

                        floor_points_3D[1][floor_points_3D[0].size() - 1][0].emplace_back(xline_start);
                        floor_points_3D[1][floor_points_3D[0].size() - 1][0].emplace_back(yline_start);
                        floor_points_3D[1][floor_points_3D[0].size() - 1][0].emplace_back(zline_start);

                        floor_points_3D[1][floor_points_3D[0].size() - 1][1].emplace_back(xline_end);
                        floor_points_3D[1][floor_points_3D[0].size() - 1][1].emplace_back(yline_end);
                        floor_points_3D[1][floor_points_3D[0].size() - 1][1].emplace_back(zline_end);

                    }

                    triangle_planes_already_lined.emplace_back();
                    triangle_planes_already_lined[triangle_planes_already_lined.size()-1].emplace_back();
                    triangle_planes_already_lined[triangle_planes_already_lined.size()-1][triangle_planes_already_lined[triangle_planes_already_lined.size()-1].size()-1].emplace_back(triangle_points_3D_sphere[i][j][l][0][0]);
                    triangle_planes_already_lined[triangle_planes_already_lined.size()-1][triangle_planes_already_lined[triangle_planes_already_lined.size()-1].size()-1].emplace_back(triangle_points_3D_sphere[i][j][l][0][1]);
                    triangle_planes_already_lined[triangle_planes_already_lined.size()-1][triangle_planes_already_lined[triangle_planes_already_lined.size()-1].size()-1].emplace_back(triangle_points_3D_sphere[i][j][l][0][2]);

                    triangle_planes_already_lined[triangle_planes_already_lined.size()-1].emplace_back();
                    triangle_planes_already_lined[triangle_planes_already_lined.size()-1][triangle_planes_already_lined[triangle_planes_already_lined.size()-1].size()-1].emplace_back(triangle_points_3D_sphere[i][j][l][1][0]);
                    triangle_planes_already_lined[triangle_planes_already_lined.size()-1][triangle_planes_already_lined[triangle_planes_already_lined.size()-1].size()-1].emplace_back(triangle_points_3D_sphere[i][j][l][1][1]);
                    triangle_planes_already_lined[triangle_planes_already_lined.size()-1][triangle_planes_already_lined[triangle_planes_already_lined.size()-1].size()-1].emplace_back(triangle_points_3D_sphere[i][j][l][1][2]);

                    triangle_planes_already_lined[triangle_planes_already_lined.size()-1].emplace_back();
                    triangle_planes_already_lined[triangle_planes_already_lined.size()-1][triangle_planes_already_lined[triangle_planes_already_lined.size()-1].size()-1].emplace_back(triangle_points_3D_sphere[i][j][l][2][0]);
                    triangle_planes_already_lined[triangle_planes_already_lined.size()-1][triangle_planes_already_lined[triangle_planes_already_lined.size()-1].size()-1].emplace_back(triangle_points_3D_sphere[i][j][l][2][1]);
                    triangle_planes_already_lined[triangle_planes_already_lined.size()-1][triangle_planes_already_lined[triangle_planes_already_lined.size()-1].size()-1].emplace_back(triangle_points_3D_sphere[i][j][l][2][2]);
                    
                }

            }


        }   

    }

    return floor_points_3D;
}


std::vector<std::vector<std::vector<std::vector<int>>>> Graphics::clip_and_compute_2D_sphere_lines(std::vector<std::vector<std::vector<std::vector<double>>>> world_lines_points_3D){

    std::vector<std::vector<std::vector<std::vector<int>>>> world_lines_points_2D;

    // Iterating through all points on an object to compute the 2D window view point counterparts for a 3D object as observed by an eye behind the window.
    for (int i = 0; i < world_lines_points_3D.size(); i++){
        world_lines_points_2D.emplace_back();

        for (int j = 0; j < world_lines_points_3D[i].size(); j++){
            world_lines_points_2D[i].emplace_back();


            world_lines_points_2D[i][j].emplace_back();
            world_lines_points_2D[i][j][0].emplace_back(0);
            world_lines_points_2D[i][j][0].emplace_back(0);


            world_lines_points_2D[i][j].emplace_back();
            world_lines_points_2D[i][j][1].emplace_back(0);
            world_lines_points_2D[i][j][1].emplace_back(0);


            std::vector<double> clipped_coor_diffs = clip_3D_line(world_lines_points_3D[i][j]);
            
            double x1_clip_diff = clipped_coor_diffs[0];
            double y1_clip_diff = clipped_coor_diffs[1];
            double z1_clip_diff = clipped_coor_diffs[2];

            double x2_clip_diff = clipped_coor_diffs[3];
            double y2_clip_diff = clipped_coor_diffs[4];
            double z2_clip_diff = clipped_coor_diffs[5];

            



            if (x1_clip_diff == -100000 && y1_clip_diff == -100000 && z1_clip_diff == -100000 &&
                    x2_clip_diff == -100000 && y2_clip_diff == -100000 && z2_clip_diff == -100000){

                            
                world_lines_points_2D[i][j][0][0] = -100000;
                world_lines_points_2D[i][j][0][1] = -100000;

                world_lines_points_2D[i][j][1][0] = -100000;
                world_lines_points_2D[i][j][1][1] = -100000;

            }else{

                // Returning diff to objective point so that it can be plugged into compute_2D_point.
                double x_3D = (x1_clip_diff - playerx) * -1;
                double y_3D = y1_clip_diff + playery;
                double z_3D = z1_clip_diff + playerz;

                std::vector<double> point_3D = {x_3D, y_3D, z_3D};
                std::vector<int> point_2D = compute_2D_point(point_3D);

                world_lines_points_2D[i][j][0][0] = point_2D[0];
                world_lines_points_2D[i][j][0][1] = point_2D[1];



                x_3D = (x2_clip_diff - playerx) * -1;
                y_3D = y2_clip_diff + playery;
                z_3D = z2_clip_diff + playerz;

                point_3D = {x_3D, y_3D, z_3D};
                point_2D = compute_2D_point(point_3D);

                world_lines_points_2D[i][j][1][0] = point_2D[0];
                world_lines_points_2D[i][j][1][1] = point_2D[1];

            }

        }
    }


    return world_lines_points_2D;

}



std::vector<double> Graphics::clip_3D_line(std::vector<std::vector<double>> line_points_3D){

    double x_diff1 = playerx - line_points_3D[0][0];
    double y_diff1 = line_points_3D[0][1] - playery;
    double z_diff1 = line_points_3D[0][2] - playerz;

    double x_diff2 = playerx - line_points_3D[1][0];
    double y_diff2 = line_points_3D[1][1] - playery;
    double z_diff2 = line_points_3D[1][2] - playerz;


    double x1_clip_diff;
    double y1_clip_diff;
    double z1_clip_diff;

    double x2_clip_diff;
    double y2_clip_diff;
    double z2_clip_diff;

    
    // Determining if clipping is necessary (when z value reaches behind player).
    if (z_diff1 <= near_plane && z_diff2 <= near_plane){

        x1_clip_diff = -100000;
        y1_clip_diff = -100000;
        z1_clip_diff = -100000;

        x2_clip_diff = -100000;
        y2_clip_diff = -100000;
        z2_clip_diff = -100000;


    }else if (z_diff1 <= near_plane){

        double ratio_along = (near_plane - z_diff1) / (line_points_3D[1][2] - line_points_3D[0][2]);
        double x1_clip = line_points_3D[0][0] + ratio_along * (line_points_3D[1][0] - line_points_3D[0][0]);
        double y1_clip = line_points_3D[0][1] - ratio_along * (line_points_3D[0][1] - line_points_3D[1][1]);


        x1_clip_diff = playerx - x1_clip;
        y1_clip_diff = y1_clip - playery;
        z1_clip_diff = near_plane;

        x2_clip_diff = x_diff2;
        y2_clip_diff = y_diff2;
        z2_clip_diff = z_diff2;



    }else if (z_diff2 <= near_plane){

        x1_clip_diff = x_diff1;
        y1_clip_diff = y_diff1;
        z1_clip_diff = z_diff1;

        double ratio_along = (near_plane - z_diff2) / (z_diff1 - z_diff2);
        double x2_clip = line_points_3D[1][0] + ratio_along * (line_points_3D[0][0] - line_points_3D[1][0]);
        double y2_clip = line_points_3D[1][1] - ratio_along * (line_points_3D[1][1] - line_points_3D[0][1]);
        double z2_clip = near_plane;


        x2_clip_diff = playerx - x2_clip;
        y2_clip_diff = y2_clip - playery;
        z2_clip_diff = near_plane;

    }else{

        x1_clip_diff = x_diff1;
        y1_clip_diff = y_diff1;
        z1_clip_diff = z_diff1;

        x2_clip_diff = x_diff2;
        y2_clip_diff = y_diff2;
        z2_clip_diff = z_diff2;
    }

    std::vector<double> clipped_coor_diffs;
    clipped_coor_diffs.emplace_back(x1_clip_diff);
    clipped_coor_diffs.emplace_back(y1_clip_diff);
    clipped_coor_diffs.emplace_back(z1_clip_diff);
    clipped_coor_diffs.emplace_back(x2_clip_diff);
    clipped_coor_diffs.emplace_back(y2_clip_diff);
    clipped_coor_diffs.emplace_back(z2_clip_diff);

    return clipped_coor_diffs;
}

// std::vector<std::vector<std::vector<std::vector<int>>>> Graphics::compute_2D_lines(std::vector<std::vector<std::vector<std::vector<double>>>> floor_points_3D){

//     std::vector<std::vector<std::vector<std::vector<int>>>> floor_points_2D;

//     // Iterating through all points on an object to compute the 2D window view point counterparts for a 3D object as observed by an eye behind the window.
//     for (int i = 0; i < floor_points_3D.size(); i++){
//         floor_points_2D.emplace_back();

//         for (int j = 0; j < floor_points_3D[i].size(); j++){
//             floor_points_2D[i].emplace_back();

//             for (int k = 0; k < floor_points_3D[i][j].size(); k++){
//                 floor_points_2D[i][j].emplace_back();

//                 floor_points_2D[i][j][k].emplace_back(0);
//                 floor_points_2D[i][j][k].emplace_back(0);


//                 // gpt
//                 double x_diff = floor_points_3D[i][j][k][0] - playerx;
//                 double y_diff = floor_points_3D[i][j][k][1] - playery;
//                 double z_diff = floor_points_3D[i][j][k][2] - playerz;

//                 double sin_ax = sin(angley_diff);
//                 double cos_ax = cos(angley_diff);
//                 double sin_ay = sin(anglex_diff);
//                 double cos_ay = cos(anglex_diff);


//                 // --- Rotate around Y-axis --- //gpt
//                 double x1 = -x_diff * cos_ay + z_diff * sin_ay;
//                 double z1 = x_diff * sin_ay + z_diff * cos_ay;
//                 double y1 = y_diff;

//                 // --- Rotate around X-axis --- //gpt
//                 double y_final = y1 * cos_ax - z1 * sin_ax;
//                 double z_final = y1 * sin_ax + z1 * cos_ax;
//                 double x_final = x1;

//                 if (z_final < near_plane) {
//                     floor_points_2D[i][j][k][0] = -100000;
//                     floor_points_2D[i][j][k][1] = -100000;
//                 } else {
//                     int x = (int)((x_final / z_final) * zscreendiff);
//                     int y = (int)((y_final / z_final) * zscreendiff);

//                     floor_points_2D[i][j][k][0] = 960 - x;
//                     floor_points_2D[i][j][k][1] = 540 + y;
//                 }
//             }
//         }

//     }


//     return floor_points_2D;

// }


std::vector<std::vector<int>> Graphics::compute_2D_box(std::vector<std::vector<double>> rect_points_3D){

    std::vector<std::vector<int>> rect_points_2D;

    // Iterating through all points on an object to compute the 2D window view point counterparts for a 3D object as observed by an eye behind the window.
    for (int i = 0; i < rect_points_3D.size(); i++){
        rect_points_2D.emplace_back();

        rect_points_2D[i].emplace_back(0);
        rect_points_2D[i].emplace_back(0);



        // double anglex = atan2(rect_points_3D[i][0] - playerx, rect_points_3D[i][2] - playerz);
        // //int x = (int) (tan(anglex) * zscreendiff);

        // double angley = atan2(rect_points_3D[i][1] - playery, rect_points_3D[i][2] - playerz);
        // int y = (int) (tan(angley) * zscreendiff);


        // double anglex_turn = anglex + anglex_diff;
        // double hyp = (rect_points_3D[i][0] - playerx) / sin(anglex);
        // double z_turn_diff = cos(anglex_turn) * hyp;

        // if (z_turn_diff < near_plane){
        //     rect_points_2D[i][0] = -100000;
        //     rect_points_2D[i][1] = -100000;    

        // } else{

        //     int x = (int) (tan(anglex_turn) * zscreendiff);

        //     rect_points_2D[i][0] = (int) (960 + x);
        //     rect_points_2D[i][1] = (int) (540 + y);
        // }





        // gpt
        double x_diff = rect_points_3D[i][0] - playerx;
        double y_diff = rect_points_3D[i][1] - playery;
        double z_diff = rect_points_3D[i][2] - playerz;

        double sin_ax = sin(angley_diff);
        double cos_ax = cos(angley_diff);
        double sin_ay = sin(anglex_diff);
        double cos_ay = cos(anglex_diff);


        // --- Rotate around Y-axis --- //gpt
        double x1 = -x_diff * cos_ay + z_diff * sin_ay;
        double z1 = x_diff * sin_ay + z_diff * cos_ay;
        double y1 = y_diff;

        // --- Rotate around X-axis --- //gpt
        double y_final = y1 * cos_ax - z1 * sin_ax;
        double z_final = y1 * sin_ax + z1 * cos_ax;
        double x_final = x1;

        if (z_final < near_plane) {
            rect_points_2D[i][0] = -100000;
            rect_points_2D[i][1] = -100000;
        } else {
            int x = (int)((x_final / z_final) * zscreendiff);
            int y = (int)((y_final / z_final) * zscreendiff);

            rect_points_2D[i][0] = 960 - x;
            rect_points_2D[i][1] = 540 + y;
        }

    }

    return rect_points_2D;

}


std::vector<std::vector<std::vector<std::vector<std::vector<int>>>>> Graphics::compute_2D_sphere_triangles(std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> triangle_points_3D_sphere){
    std::vector<std::vector<std::vector<std::vector<std::vector<int>>>>> object_2D(
        triangle_points_3D_sphere.size(), std::vector<std::vector<std::vector<std::vector<int>>>>(
                triangle_points_3D_sphere[0].size(), std::vector<std::vector<std::vector<int>>>(
                    triangle_points_3D_sphere[0][0].size(), std::vector<std::vector<int>>(
                            3, std::vector<int>(2, 0)))));

    // Iterating through all points on an object to compute the 2D window view point counterparts for a 3D object as observed by an eye behind the window.
    for (int i = 0; i < triangle_points_3D_sphere.size(); i++){
        for (int j = 0; j < triangle_points_3D_sphere[i].size(); j++){
            for (int l = 0; l < triangle_points_3D_sphere[i][j].size(); l++){ 

                for (int k = 0; k < 3; k++){

                    object_2D[i][j][l][k] = compute_2D_point(triangle_points_3D_sphere[i][j][l][k]);



                    // // gpt
                    // double x_diff = triangle_points_3D_sphere[i][j][l][k][0] - playerx;
                    // double y_diff = triangle_points_3D_sphere[i][j][l][k][1] - playery;
                    // double z_diff = triangle_points_3D_sphere[i][j][l][k][2] - playerz;

                    // double sin_ax = sin(angley_diff);
                    // double cos_ax = cos(angley_diff);
                    // double sin_ay = sin(anglex_diff);
                    // double cos_ay = cos(anglex_diff);


                    // // --- Rotate around Y-axis --- //gpt
                    // double x1 = -x_diff * cos_ay + z_diff * sin_ay;
                    // double z1 = x_diff * sin_ay + z_diff * cos_ay;
                    // double y1 = y_diff;

                    // // --- Rotate around X-axis --- //gpt
                    // double y_final = y1 * cos_ax - z1 * sin_ax;
                    // double z_final = y1 * sin_ax + z1 * cos_ax;
                    // double x_final = x1;

                    // if (z_final < near_plane) {
                    //     object_2D[i][j][l][k][0] = -100000;
                    //     object_2D[i][j][l][k][1] = -100000;
                    // } else {
                    //     int x = (int)((x_final / z_final) * zscreendiff);
                    //     int y = (int)((y_final / z_final) * zscreendiff);

                    //     object_2D[i][j][l][k][0] = 960 - x;
                    //     object_2D[i][j][l][k][1] = 540 + y;
                    // }
                }
            }
        }
    }

    return object_2D;

}


std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<int>>>>>> Graphics::compute_2D_sphere_triangles_as_lines(std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>>> triangle_points_3D_sphere_as_lines){
    std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<int>>>>>> object_2D;

    // Iterating through all points on an object to compute the 2D window view point counterparts for a 3D object as observed by an eye behind the window.
    for (int i = 0; i < triangle_points_3D_sphere_as_lines.size(); i++){
        object_2D.emplace_back();
        for (int j = 0; j < triangle_points_3D_sphere_as_lines[i].size(); j++){
            object_2D[i].emplace_back();
            for (int k = 0; k < triangle_points_3D_sphere_as_lines[i][j].size(); k++){ 

                object_2D[i][j].emplace_back();

                object_2D[i][j][k].emplace_back();
                object_2D[i][j][k][0].emplace_back(compute_2D_point(triangle_points_3D_sphere_as_lines[i][j][k][0][0]));
                object_2D[i][j][k][0].emplace_back(compute_2D_point(triangle_points_3D_sphere_as_lines[i][j][k][0][1]));


                object_2D[i][j][k].emplace_back();
                object_2D[i][j][k][1].emplace_back(compute_2D_point(triangle_points_3D_sphere_as_lines[i][j][k][1][0]));
                object_2D[i][j][k][1].emplace_back(compute_2D_point(triangle_points_3D_sphere_as_lines[i][j][k][1][1]));


                object_2D[i][j][k].emplace_back();
                object_2D[i][j][k][2].emplace_back(compute_2D_point(triangle_points_3D_sphere_as_lines[i][j][k][2][0]));
                object_2D[i][j][k][2].emplace_back(compute_2D_point(triangle_points_3D_sphere_as_lines[i][j][k][2][1]));
            }
        }
    }

    return object_2D;

}


std::vector<int> Graphics::compute_2D_point(std::vector<double> point_3D){
    std::vector<int> point_2D(2, 0);

    // Computing the 2D window view point counterparts for a 3D object as observed by an eye behind the window.
    double x_3D_diff = playerx - point_3D[0];
    double y_3D_diff = point_3D[1] - playery;
    double z_3D_diff = point_3D[2] - playerz;

    double anglex = atan2(x_3D_diff, z_3D_diff);
    double anglex_turn = anglex + anglex_diff;

    double angley = atan2(y_3D_diff, z_3D_diff);
    //double angley_turn = angley + angley_diff;


    int x_2D_diff = (int) (tan(anglex_turn) * zscreendiff);
    int y_2D_diff = (int) (tan(angley) * zscreendiff);



    point_2D[0] = (int) (960 - x_2D_diff);
    point_2D[1] = (int) (540 + y_2D_diff);

    return point_2D;

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
            if (floor_points_2D[i][j][0][0] != -100000 && floor_points_2D[i][j][1][0] != -100000 &&
                    floor_points_2D[i][j][0][1] != -100000 && floor_points_2D[i][j][1][1] != -100000){
                
                glBegin(GL_LINES);
                    glVertex2i(floor_points_2D[i][j][0][0], floor_points_2D[i][j][0][1]);
                    glVertex2i(floor_points_2D[i][j][1][0], floor_points_2D[i][j][1][1]);
                glEnd();

            }
        }
    }

}


void Graphics::draw_full_triangles_sphere(std::vector<std::vector<std::vector<std::vector<std::vector<int>>>>> triangle_points_2D){

    for (int i = 0; i < triangle_points_2D.size(); i++){

        bool skip = false;
        for (int j = 0; j < triangle_points_2D[i].size(); j++){
            for (int l = 0; l < triangle_points_2D[i][j].size(); l++){
                for (int k = 0; k < triangle_points_2D[i][j][l].size(); k++){
                    if (triangle_points_2D[i][j][l][k][0] == -100000 && triangle_points_2D[i][j][l][k][1] == -100000) skip = true;
                }
            }
        }

        if (!skip){
            for (int j = 0; j < triangle_points_2D[i].size(); j++){
                for (int l = 0; l < triangle_points_2D[i][j].size(); l++){

                    glBegin(GL_POLYGON);
                        glVertex2i(triangle_points_2D[i][j][l][0][0], triangle_points_2D[i][j][l][0][1]);
                        glVertex2i(triangle_points_2D[i][j][l][1][0], triangle_points_2D[i][j][l][1][1]);
                        glVertex2i(triangle_points_2D[i][j][l][2][0], triangle_points_2D[i][j][l][2][1]);
                    glEnd();
                }
            }
        }
    }

}


void Graphics::draw_hollow_triangles_sphere(std::vector<std::vector<std::vector<std::vector<std::vector<int>>>>> triangle_points_2D){

    for (int i = 0; i < triangle_points_2D.size(); i++){

        bool skip = false;
        for (int j = 0; j < triangle_points_2D[0].size(); j++){
            for (int l = 0; l < triangle_points_2D[i][j].size(); l++){
                for (int k = 0; k < triangle_points_2D[0][0].size(); k++){
                    if (triangle_points_2D[i][j][l][k][0] == -100000 && triangle_points_2D[i][j][l][k][1] == -100000 ) skip = true;
                }
            }
        }

        if (!skip){

            for (int j = 0; j < triangle_points_2D[0].size(); j++){
                for (int l = 0; l < triangle_points_2D[i][j].size(); l++){
                    glBegin(GL_LINES);
                        glVertex2i(triangle_points_2D[i][j][l][0][0], triangle_points_2D[i][j][l][0][1]);
                        glVertex2i(triangle_points_2D[i][j][l][1][0], triangle_points_2D[i][j][l][1][1]);
                    glEnd();

                    glBegin(GL_LINES);
                        glVertex2i(triangle_points_2D[i][j][l][1][0], triangle_points_2D[i][j][l][1][1]);
                        glVertex2i(triangle_points_2D[i][j][l][2][0], triangle_points_2D[i][j][l][2][1]);
                    glEnd();

                    glBegin(GL_LINES);
                        glVertex2i(triangle_points_2D[i][j][l][2][0], triangle_points_2D[i][j][l][2][1]);
                        glVertex2i(triangle_points_2D[i][j][l][0][0], triangle_points_2D[i][j][l][0][1]);
                    glEnd();
                }
            }
        }
    }
}



void Graphics::draw_hollow_triangles_sphere_as_lines(std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<int>>>>>> triangle_points_2D){

    for (int i = 0; i < triangle_points_2D.size(); i++){

        bool skip = false;
        for (int j = 0; j < triangle_points_2D[i].size(); j++){
            for (int k = 0; k < triangle_points_2D[i][j].size(); k++){
                for (int l = 0; l < triangle_points_2D[i][j].size(); l++){
                    if (triangle_points_2D[i][j][k][l][0][0] == -100000 && triangle_points_2D[i][j][k][l][0][1] == -100000 &&
                            triangle_points_2D[i][j][k][l][1][0] == -100000 && triangle_points_2D[i][j][k][l][1][1] == -100000 ) skip = true;
                }
            }
        }

        if (!skip){

            for (int j = 0; j < triangle_points_2D[i].size(); j++){
                for (int k = 0; k < triangle_points_2D[i][j].size(); k++){
                    for (int l = 0; l < triangle_points_2D[i][j][k].size(); l++){
                        glBegin(GL_LINES);
                            glVertex2i(triangle_points_2D[i][j][k][l][0][0], triangle_points_2D[i][j][k][l][0][1]);
                            glVertex2i(triangle_points_2D[i][j][k][l][1][0], triangle_points_2D[i][j][k][l][1][1]);
                        glEnd();
                    }
                }
            }
        }
    }
}



void Graphics::draw_full_box(std::vector<std::vector<int>> rect_points_2D){

    bool skip = false;

    for (int i = 0; i < rect_points_2D.size(); i++){
        if (rect_points_2D[i][0] == -100000 && rect_points_2D[i][1] == -100000) skip = true;
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

void Graphics::draw_full_polygon(std::vector<std::vector<int>> polygon_points_2D){

    bool skip = false;

    for (int i = 0; i < polygon_points_2D.size(); i++){
        if (polygon_points_2D[i][0] == -100000 && polygon_points_2D[i][1] == -100000) skip = true;
    }

    if (!skip){

        if (polygon_points_2D.size() == 3){

            glBegin(GL_POLYGON);
                glVertex2i(polygon_points_2D[0][0], polygon_points_2D[0][1]);
                glVertex2i(polygon_points_2D[1][0], polygon_points_2D[1][1]);
                glVertex2i(polygon_points_2D[2][0], polygon_points_2D[2][1]);
            glEnd();

        }else if (polygon_points_2D.size() == 4){

            glBegin(GL_POLYGON);
                glVertex2i(polygon_points_2D[0][0], polygon_points_2D[0][1]);
                glVertex2i(polygon_points_2D[1][0], polygon_points_2D[1][1]);
                glVertex2i(polygon_points_2D[2][0], polygon_points_2D[2][1]);
                glVertex2i(polygon_points_2D[3][0], polygon_points_2D[3][1]);
            glEnd();

        }else if (polygon_points_2D.size() == 5){

            glBegin(GL_POLYGON);
                glVertex2i(polygon_points_2D[0][0], polygon_points_2D[0][1]);
                glVertex2i(polygon_points_2D[1][0], polygon_points_2D[1][1]);
                glVertex2i(polygon_points_2D[2][0], polygon_points_2D[2][1]);
                glVertex2i(polygon_points_2D[3][0], polygon_points_2D[3][1]);
                glVertex2i(polygon_points_2D[4][0], polygon_points_2D[4][1]);
            glEnd();

        }else if (polygon_points_2D.size() == 6){

            glBegin(GL_POLYGON);
                glVertex2i(polygon_points_2D[0][0], polygon_points_2D[0][1]);
                glVertex2i(polygon_points_2D[1][0], polygon_points_2D[1][1]);
                glVertex2i(polygon_points_2D[2][0], polygon_points_2D[2][1]);
                glVertex2i(polygon_points_2D[3][0], polygon_points_2D[3][1]);
                glVertex2i(polygon_points_2D[4][0], polygon_points_2D[4][1]);
                glVertex2i(polygon_points_2D[5][0], polygon_points_2D[5][1]);
            glEnd();

        // Drawing full box.
        }else if (polygon_points_2D.size() == 8){
            glBegin(GL_POLYGON);
                glVertex2i(polygon_points_2D[0][0], polygon_points_2D[0][1]);
                glVertex2i(polygon_points_2D[1][0], polygon_points_2D[1][1]);
                glVertex2i(polygon_points_2D[3][0], polygon_points_2D[3][1]);
                glVertex2i(polygon_points_2D[2][0], polygon_points_2D[2][1]);
            glEnd();

            glBegin(GL_POLYGON);
                glVertex2i(polygon_points_2D[2][0], polygon_points_2D[2][1]);
                glVertex2i(polygon_points_2D[0][0], polygon_points_2D[0][1]);
                glVertex2i(polygon_points_2D[4][0], polygon_points_2D[4][1]);
                glVertex2i(polygon_points_2D[6][0], polygon_points_2D[6][1]);
            glEnd();

            glBegin(GL_POLYGON);
                glVertex2i(polygon_points_2D[0][0], polygon_points_2D[0][1]);
                glVertex2i(polygon_points_2D[1][0], polygon_points_2D[1][1]);
                glVertex2i(polygon_points_2D[5][0], polygon_points_2D[5][1]);
                glVertex2i(polygon_points_2D[4][0], polygon_points_2D[4][1]);
            glEnd();

            glBegin(GL_POLYGON);
                glVertex2i(polygon_points_2D[5][0], polygon_points_2D[5][1]);
                glVertex2i(polygon_points_2D[1][0], polygon_points_2D[1][1]);
                glVertex2i(polygon_points_2D[3][0], polygon_points_2D[3][1]);
                glVertex2i(polygon_points_2D[7][0], polygon_points_2D[7][1]);
            glEnd();

            glBegin(GL_POLYGON);
                glVertex2i(polygon_points_2D[2][0], polygon_points_2D[2][1]);
                glVertex2i(polygon_points_2D[3][0], polygon_points_2D[3][1]);
                glVertex2i(polygon_points_2D[7][0], polygon_points_2D[7][1]);
                glVertex2i(polygon_points_2D[6][0], polygon_points_2D[6][1]);
            glEnd();

            glBegin(GL_POLYGON);
                glVertex2i(polygon_points_2D[4][0], polygon_points_2D[4][1]);
                glVertex2i(polygon_points_2D[5][0], polygon_points_2D[5][1]);
                glVertex2i(polygon_points_2D[7][0], polygon_points_2D[7][1]);
                glVertex2i(polygon_points_2D[6][0], polygon_points_2D[6][1]);
            glEnd();
        }
    }

}

void Graphics::draw_hollow_polygon(std::vector<std::vector<int>> polygon_points_2D){

    bool skip = false;

    for (int i = 0; i < polygon_points_2D.size(); i++){
        if (polygon_points_2D[i][0] == -100000 && polygon_points_2D[i][1] == -100000) skip = true;
    }

    if (!skip){

        if (polygon_points_2D.size() == 3){

            glBegin(GL_LINE_LOOP);
                glVertex2i(polygon_points_2D[0][0], polygon_points_2D[0][1]);
                glVertex2i(polygon_points_2D[1][0], polygon_points_2D[1][1]);
                glVertex2i(polygon_points_2D[2][0], polygon_points_2D[2][1]);
            glEnd();

        }else if (polygon_points_2D.size() == 4){

            glBegin(GL_LINE_LOOP);
                glVertex2i(polygon_points_2D[0][0], polygon_points_2D[0][1]);
                glVertex2i(polygon_points_2D[1][0], polygon_points_2D[1][1]);
                glVertex2i(polygon_points_2D[2][0], polygon_points_2D[2][1]);
                glVertex2i(polygon_points_2D[3][0], polygon_points_2D[3][1]);
            glEnd();

        }else if (polygon_points_2D.size() == 5){

            glBegin(GL_LINE_LOOP);
                glVertex2i(polygon_points_2D[0][0], polygon_points_2D[0][1]);
                glVertex2i(polygon_points_2D[1][0], polygon_points_2D[1][1]);
                glVertex2i(polygon_points_2D[2][0], polygon_points_2D[2][1]);
                glVertex2i(polygon_points_2D[3][0], polygon_points_2D[3][1]);
                glVertex2i(polygon_points_2D[4][0], polygon_points_2D[4][1]);
            glEnd();

        }else if (polygon_points_2D.size() == 6){

            glBegin(GL_LINE_LOOP);
                glVertex2i(polygon_points_2D[0][0], polygon_points_2D[0][1]);
                glVertex2i(polygon_points_2D[1][0], polygon_points_2D[1][1]);
                glVertex2i(polygon_points_2D[2][0], polygon_points_2D[2][1]);
                glVertex2i(polygon_points_2D[3][0], polygon_points_2D[3][1]);
                glVertex2i(polygon_points_2D[4][0], polygon_points_2D[4][1]);
                glVertex2i(polygon_points_2D[5][0], polygon_points_2D[5][1]);
            glEnd();

        }else if (polygon_points_2D.size() == 8){
            glBegin(GL_LINE_LOOP);
                glVertex2i(polygon_points_2D[0][0], polygon_points_2D[0][1]);
                glVertex2i(polygon_points_2D[1][0], polygon_points_2D[1][1]);
                glVertex2i(polygon_points_2D[3][0], polygon_points_2D[3][1]);
                glVertex2i(polygon_points_2D[2][0], polygon_points_2D[2][1]);
            glEnd();

            glBegin(GL_LINE_LOOP);
                glVertex2i(polygon_points_2D[2][0], polygon_points_2D[2][1]);
                glVertex2i(polygon_points_2D[0][0], polygon_points_2D[0][1]);
                glVertex2i(polygon_points_2D[4][0], polygon_points_2D[4][1]);
                glVertex2i(polygon_points_2D[6][0], polygon_points_2D[6][1]);
            glEnd();

            glBegin(GL_LINE_LOOP);
                glVertex2i(polygon_points_2D[0][0], polygon_points_2D[0][1]);
                glVertex2i(polygon_points_2D[1][0], polygon_points_2D[1][1]);
                glVertex2i(polygon_points_2D[5][0], polygon_points_2D[5][1]);
                glVertex2i(polygon_points_2D[4][0], polygon_points_2D[4][1]);
            glEnd();

            glBegin(GL_LINE_LOOP);
                glVertex2i(polygon_points_2D[5][0], polygon_points_2D[5][1]);
                glVertex2i(polygon_points_2D[1][0], polygon_points_2D[1][1]);
                glVertex2i(polygon_points_2D[3][0], polygon_points_2D[3][1]);
                glVertex2i(polygon_points_2D[7][0], polygon_points_2D[7][1]);
            glEnd();

            glBegin(GL_LINE_LOOP);
                glVertex2i(polygon_points_2D[2][0], polygon_points_2D[2][1]);
                glVertex2i(polygon_points_2D[3][0], polygon_points_2D[3][1]);
                glVertex2i(polygon_points_2D[7][0], polygon_points_2D[7][1]);
                glVertex2i(polygon_points_2D[6][0], polygon_points_2D[6][1]);
            glEnd();

            glBegin(GL_LINE_LOOP);
                glVertex2i(polygon_points_2D[4][0], polygon_points_2D[4][1]);
                glVertex2i(polygon_points_2D[5][0], polygon_points_2D[5][1]);
                glVertex2i(polygon_points_2D[7][0], polygon_points_2D[7][1]);
                glVertex2i(polygon_points_2D[6][0], polygon_points_2D[6][1]);
            glEnd();
        }
    }

}


void Graphics::draw_hollow_box(std::vector<std::vector<int>> rect_points_2D){

    bool skip = false;

    for (int i = 0; i < rect_points_2D.size(); i++){
        if (rect_points_2D[i][0] == -100000 && rect_points_2D[i][1] == -100000) skip = true;
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