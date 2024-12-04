#include <SDL2/SDL.h>
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

int zscreendiff = 1000;
int playerx = 960;
int playery = 540;
//int playery = 640;
int playerz = 0;
double z1 = 175;
double z2 = 175;
double z3 = 175;

std::vector<std::vector<double>> make_sphere(SDL_Renderer* renderer, std::vector<double> center, int radius, int num_points){

    //(x - 960)^2 + (y - 540)^2 + (z - 10)^2 = radius^2

    //int radius = 10;

    //std::vector<double> center = {960, 540, 75};


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

        // 12-sided geodesic dome

        //std::vector<std::vector<int>> sphere(12, std::vector<int>(3, 0));

        // sphere[0][0] = center[0];
        // sphere[0][1] = center[1] - radius;
        // sphere[0][2] = center[2] + radius;

        // double angle = 72;
        // double angle_rad = angle * M_PI / 180.0;

        // double anglex = atan2(triangle_points[i][j][k][0] - playerx, triangle_points[i][j][k][2] - playerz);
        // int x = (int) (tan(anglex) * zscreendiff);

        // double angley = atan2(triangle_points[i][j][k][1] - playery, triangle_points[i][j][k][2] - playerz);
        // int y = (int) (tan(angley) * zscreendiff);

        // double z_step = radius / 3;


        // copied attempt at 12-sided geodesic sphere (based on golden ratio):

        double phi = 1.61803;
        sphere_points_3D = { {center[0] + -1 * radius,  center[1] + phi * radius,  center[2] + 0 * radius}, {center[0] + 1 * radius,  center[1] + phi * radius,  center[2] + 0 * radius}, {center[0] + -1 * radius, center[1] + -phi * radius,  center[2] + 0 * radius}, {center[0] + 1 * radius, center[1] + -phi * radius,  center[2] + 0 * radius},
            {center[0] + 0 * radius, center[1] + -1 * radius,  center[2] + phi * radius}, {center[0] + 0 * radius,  center[1] + 1 * radius,  center[2] + phi * radius}, {center[0] + 0 * radius, center[1] + -1 * radius, center[2] + -phi * radius}, {center[0] + 0 * radius,  center[1] + 1 * radius, center[2] + -phi * radius},
            {center[0] + phi * radius,  center[1] + 0 * radius, center[2] + -1 * radius}, {center[0] + phi * radius,  center[1] + 0 * radius,  center[2] + 1 * radius}, {center[0] + -phi * radius,  center[1] + 0 * radius, center[2] + -1 * radius}, {center[0] + -phi * radius,  center[1] + 0 * radius,  center[2] + 1 * radius} };
    }


    // working-ish angular attempt.

    // std::vector<std::vector<double>> sphere;

    // int i = 0;
    // for (int anglez = 0; anglez < 360; anglez+= 10){
    //     double anglez_rad = anglez * M_PI / 180.0;
    //     double z = cos(anglez) * radius;

    //     for (int anglex = 0; anglex < 360; anglex+= 10){
    //         for (int angley = 0; angley < 360; angley+= 10){

    //             double anglex_rad = anglex * M_PI / 180.0;
    //             double angley_rad = angley * M_PI / 180.0;

    //             double x = sin(anglex) * radius;
    //             double y = cos(angley) * radius;

    //             //std::cout << "PPPPPPPP " + std::to_string(i) + " " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z) << std::endl;
    //             double result = x * x + y * y + z * z;

    //             //std::cout << "OOOOOOOO " + std::to_string(result) << std::endl;
    //             if (result > radius * radius - 10 && result < radius * radius + 10){

    //                 //sphere.emplace_back(std::vector<int>{x, y, z});
    //                 i++;

    //                 std::cout << "LLLLLLLLLL " + std::to_string(i) + " " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z) << std::endl;

    //                 double x_total = center[0] + x;
    //                 double y_total = center[1] - y;
    //                 double z_total = center[2] + z;

    //                 sphere.emplace_back(std::vector<double>{});
    //                 sphere[sphere.size()-1].emplace_back(x_total);
    //                 sphere[sphere.size()-1].emplace_back(y_total);
    //                 sphere[sphere.size()-1].emplace_back(z_total);



    //                 double anglex1 = atan2(x_total - playerx, z_total - playerz);
    //                 double x1 = (int) (tan(anglex1) * zscreendiff);

    //                 double angley1 = atan2(y_total - playery, z_total - playerz);
    //                 double y1 = (int) (tan(angley1) * zscreendiff);

    //                 int x2 = (int) x1 + 960;
    //                 int y2 = (int) y1 + 540;

    //                 //std::cout << "KKKKKKKKKKKK " + std::to_string(x2) + " " + std::to_string(y2) << std::endl;
    //                 SDL_RenderDrawLine(renderer, x2, y2, x2 + 10, y2 + 10);
    //             }
    //         }
    //     }
    //  }


    return sphere_points_3D;
}


std::vector<std::vector<double>> make_rectangle(std::vector<double> center, double top_length, double side_length, double depth){
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
    rect_points_3D[3][2] = center[2] + depth;

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


std::vector<std::vector<std::vector<std::vector<double>>>> find_triangle_points_sphere(std::vector<std::vector<double>> sphere_points_3D){

    std::vector<std::vector<std::vector<std::vector<double>>>> triangle_points;


    for (int i = 0; i < sphere_points_3D.size(); i++){

        triangle_points.emplace_back();

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
            triangle_points[i].emplace_back();

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
                    
                    triangle_points[i][triangle_points[i].size()-1].emplace_back(std::vector<double>(3, 0));
                    triangle_points[i][triangle_points[i].size()-1][0][0] = sphere_points_3D[i][0];
                    triangle_points[i][triangle_points[i].size()-1][0][1] = sphere_points_3D[i][1];
                    triangle_points[i][triangle_points[i].size()-1][0][2] = sphere_points_3D[i][2];

                    triangle_points[i][triangle_points[i].size()-1].emplace_back(std::vector<double>(3, 0));
                    triangle_points[i][triangle_points[i].size()-1][1][0] = sphere_points_3D[adj_points[a]][0];
                    triangle_points[i][triangle_points[i].size()-1][1][1] = sphere_points_3D[adj_points[a]][1];
                    triangle_points[i][triangle_points[i].size()-1][1][2] = sphere_points_3D[adj_points[a]][2];

                    triangle_points[i][triangle_points[i].size()-1].emplace_back(std::vector<double>(3, 0));
                    triangle_points[i][triangle_points[i].size()-1][2][0] = sphere_points_3D[k][0];
                    triangle_points[i][triangle_points[i].size()-1][2][1] = sphere_points_3D[k][1];
                    triangle_points[i][triangle_points[i].size()-1][2][2] = sphere_points_3D[k][2];
                    break;
                }
            }
        }
    }
    
    return triangle_points;
}


std::vector<std::vector<std::vector<std::vector<double>>>> find_triangle_points_rectangle(std::vector<std::vector<double>> rect_points_3D){

    std::vector<std::vector<std::vector<std::vector<double>>>> triangle_points(
        8, std::vector<std::vector<std::vector<double>>>(
            3, std::vector<std::vector<double>>(
                3, std::vector<double>(3, 0))));

    triangle_points[0][0][0][0] = rect_points_3D[0][0];
    triangle_points[0][0][0][1] = rect_points_3D[0][1];
    triangle_points[0][0][0][2] = rect_points_3D[0][2];

    triangle_points[0][0][1][0] = rect_points_3D[1][0];
    triangle_points[0][0][1][1] = rect_points_3D[1][1];
    triangle_points[0][0][1][2] = rect_points_3D[1][2];

    triangle_points[0][0][2][0] = rect_points_3D[2][0];
    triangle_points[0][0][2][1] = rect_points_3D[2][1];
    triangle_points[0][0][2][2] = rect_points_3D[2][2];


    triangle_points[0][1][0][0] = rect_points_3D[0][0];
    triangle_points[0][1][0][1] = rect_points_3D[0][1];
    triangle_points[0][1][0][2] = rect_points_3D[0][2];

    triangle_points[0][1][1][0] = rect_points_3D[1][0];
    triangle_points[0][1][1][1] = rect_points_3D[1][1];
    triangle_points[0][1][1][2] = rect_points_3D[1][2];

    triangle_points[0][1][2][0] = rect_points_3D[4][0];
    triangle_points[0][1][2][1] = rect_points_3D[4][1];
    triangle_points[0][1][2][2] = rect_points_3D[4][2];


    triangle_points[0][2][0][0] = rect_points_3D[0][0];
    triangle_points[0][2][0][1] = rect_points_3D[0][1];
    triangle_points[0][2][0][2] = rect_points_3D[0][2];

    triangle_points[0][2][1][0] = rect_points_3D[2][0];
    triangle_points[0][2][1][1] = rect_points_3D[2][1];
    triangle_points[0][2][1][2] = rect_points_3D[2][2];

    triangle_points[0][2][2][0] = rect_points_3D[4][0];
    triangle_points[0][2][2][1] = rect_points_3D[4][1];
    triangle_points[0][2][2][2] = rect_points_3D[4][2];


    
    triangle_points[1][0][0][0] = rect_points_3D[1][0];
    triangle_points[1][0][0][1] = rect_points_3D[1][1];
    triangle_points[1][0][0][2] = rect_points_3D[1][2];

    triangle_points[1][0][1][0] = rect_points_3D[3][0];
    triangle_points[1][0][1][1] = rect_points_3D[3][1];
    triangle_points[1][0][1][2] = rect_points_3D[3][2];

    triangle_points[1][0][2][0] = rect_points_3D[0][0];
    triangle_points[1][0][2][1] = rect_points_3D[0][1];
    triangle_points[1][0][2][2] = rect_points_3D[0][2];


    triangle_points[1][1][0][0] = rect_points_3D[1][0];
    triangle_points[1][1][0][1] = rect_points_3D[1][1];
    triangle_points[1][1][0][2] = rect_points_3D[1][2];

    triangle_points[1][1][1][0] = rect_points_3D[0][0];
    triangle_points[1][1][1][1] = rect_points_3D[0][1];
    triangle_points[1][1][1][2] = rect_points_3D[0][2];

    triangle_points[1][1][2][0] = rect_points_3D[5][0];
    triangle_points[1][1][2][1] = rect_points_3D[5][1];
    triangle_points[1][1][2][2] = rect_points_3D[5][2];


    triangle_points[1][2][0][0] = rect_points_3D[1][0];
    triangle_points[1][2][0][1] = rect_points_3D[1][1];
    triangle_points[1][2][0][2] = rect_points_3D[1][2];

    triangle_points[1][2][1][0] = rect_points_3D[3][0];
    triangle_points[1][2][1][1] = rect_points_3D[3][1];
    triangle_points[1][2][1][2] = rect_points_3D[3][2];

    triangle_points[1][2][2][0] = rect_points_3D[5][0];
    triangle_points[1][2][2][1] = rect_points_3D[5][1];
    triangle_points[1][2][2][2] = rect_points_3D[5][2];



    triangle_points[2][0][0][0] = rect_points_3D[2][0];
    triangle_points[2][0][0][1] = rect_points_3D[2][1];
    triangle_points[2][0][0][2] = rect_points_3D[2][2];

    triangle_points[2][0][1][0] = rect_points_3D[0][0];
    triangle_points[2][0][1][1] = rect_points_3D[0][1];
    triangle_points[2][0][1][2] = rect_points_3D[0][2];

    triangle_points[2][0][2][0] = rect_points_3D[3][0];
    triangle_points[2][0][2][1] = rect_points_3D[3][1];
    triangle_points[2][0][2][2] = rect_points_3D[3][2];


    triangle_points[2][1][0][0] = rect_points_3D[2][0];
    triangle_points[2][1][0][1] = rect_points_3D[2][1];
    triangle_points[2][1][0][2] = rect_points_3D[2][2];

    triangle_points[2][1][1][0] = rect_points_3D[3][0];
    triangle_points[2][1][1][1] = rect_points_3D[3][1];
    triangle_points[2][1][1][2] = rect_points_3D[3][2];

    triangle_points[2][1][2][0] = rect_points_3D[6][0];
    triangle_points[2][1][2][1] = rect_points_3D[6][1];
    triangle_points[2][1][2][2] = rect_points_3D[6][2];


    triangle_points[2][2][0][0] = rect_points_3D[2][0];
    triangle_points[2][2][0][1] = rect_points_3D[2][1];
    triangle_points[2][2][0][2] = rect_points_3D[2][2];

    triangle_points[2][2][1][0] = rect_points_3D[0][0];
    triangle_points[2][2][1][1] = rect_points_3D[0][1];
    triangle_points[2][2][1][2] = rect_points_3D[0][2];

    triangle_points[2][2][2][0] = rect_points_3D[6][0];
    triangle_points[2][2][2][1] = rect_points_3D[6][1];
    triangle_points[2][2][2][2] = rect_points_3D[6][2];



    triangle_points[3][0][0][0] = rect_points_3D[3][0];
    triangle_points[3][0][0][1] = rect_points_3D[3][1];
    triangle_points[3][0][0][2] = rect_points_3D[3][2];

    triangle_points[3][0][1][0] = rect_points_3D[1][0];
    triangle_points[3][0][1][1] = rect_points_3D[1][1];
    triangle_points[3][0][1][2] = rect_points_3D[1][2];

    triangle_points[3][0][2][0] = rect_points_3D[2][0];
    triangle_points[3][0][2][1] = rect_points_3D[2][1];
    triangle_points[3][0][2][2] = rect_points_3D[2][2];


    triangle_points[3][1][0][0] = rect_points_3D[3][0];
    triangle_points[3][1][0][1] = rect_points_3D[3][1];
    triangle_points[3][1][0][2] = rect_points_3D[3][2];

    triangle_points[3][1][1][0] = rect_points_3D[1][0];
    triangle_points[3][1][1][1] = rect_points_3D[1][1];
    triangle_points[3][1][1][2] = rect_points_3D[1][2];

    triangle_points[3][1][2][0] = rect_points_3D[7][0];
    triangle_points[3][1][2][1] = rect_points_3D[7][1];
    triangle_points[3][1][2][2] = rect_points_3D[7][2];


    triangle_points[3][2][0][0] = rect_points_3D[3][0];
    triangle_points[3][2][0][1] = rect_points_3D[3][1];
    triangle_points[3][2][0][2] = rect_points_3D[3][2];

    triangle_points[3][2][1][0] = rect_points_3D[2][0];
    triangle_points[3][2][1][1] = rect_points_3D[2][1];
    triangle_points[3][2][1][2] = rect_points_3D[2][2];

    triangle_points[3][2][2][0] = rect_points_3D[7][0];
    triangle_points[3][2][2][1] = rect_points_3D[7][1];
    triangle_points[3][2][2][2] = rect_points_3D[7][2];


    triangle_points[4][0][0][0] = rect_points_3D[4][0];
    triangle_points[4][0][0][1] = rect_points_3D[4][1];
    triangle_points[4][0][0][2] = rect_points_3D[4][2];

    triangle_points[4][0][1][0] = rect_points_3D[5][0];
    triangle_points[4][0][1][1] = rect_points_3D[5][1];
    triangle_points[4][0][1][2] = rect_points_3D[5][2];

    triangle_points[4][0][2][0] = rect_points_3D[6][0];
    triangle_points[4][0][2][1] = rect_points_3D[6][1];
    triangle_points[4][0][2][2] = rect_points_3D[6][2];


    triangle_points[4][1][0][0] = rect_points_3D[4][0];
    triangle_points[4][1][0][1] = rect_points_3D[4][1];
    triangle_points[4][1][0][2] = rect_points_3D[4][2];

    triangle_points[4][1][1][0] = rect_points_3D[5][0];
    triangle_points[4][1][1][1] = rect_points_3D[5][1];
    triangle_points[4][1][1][2] = rect_points_3D[5][2];

    triangle_points[4][1][2][0] = rect_points_3D[0][0];
    triangle_points[4][1][2][1] = rect_points_3D[0][1];
    triangle_points[4][1][2][2] = rect_points_3D[0][2];


    triangle_points[4][2][0][0] = rect_points_3D[4][0];
    triangle_points[4][2][0][1] = rect_points_3D[4][1];
    triangle_points[4][2][0][2] = rect_points_3D[4][2];

    triangle_points[4][2][1][0] = rect_points_3D[0][0];
    triangle_points[4][2][1][1] = rect_points_3D[0][1];
    triangle_points[4][2][1][2] = rect_points_3D[0][2];

    triangle_points[4][2][2][0] = rect_points_3D[6][0];
    triangle_points[4][2][2][1] = rect_points_3D[6][1];
    triangle_points[4][2][2][2] = rect_points_3D[6][2];


    triangle_points[5][0][0][0] = rect_points_3D[5][0];
    triangle_points[5][0][0][1] = rect_points_3D[5][1];
    triangle_points[5][0][0][2] = rect_points_3D[5][2];

    triangle_points[5][0][1][0] = rect_points_3D[4][0];
    triangle_points[5][0][1][1] = rect_points_3D[4][1];
    triangle_points[5][0][1][2] = rect_points_3D[4][2];

    triangle_points[5][0][2][0] = rect_points_3D[7][0];
    triangle_points[5][0][2][1] = rect_points_3D[7][1];
    triangle_points[5][0][2][2] = rect_points_3D[7][2];


    triangle_points[5][1][0][0] = rect_points_3D[5][0];
    triangle_points[5][1][0][1] = rect_points_3D[5][1];
    triangle_points[5][1][0][2] = rect_points_3D[5][2];

    triangle_points[5][1][1][0] = rect_points_3D[4][0];
    triangle_points[5][1][1][1] = rect_points_3D[4][1];
    triangle_points[5][1][1][2] = rect_points_3D[4][2];

    triangle_points[5][1][2][0] = rect_points_3D[1][0];
    triangle_points[5][1][2][1] = rect_points_3D[1][1];
    triangle_points[5][1][2][2] = rect_points_3D[1][2];


    triangle_points[5][2][0][0] = rect_points_3D[5][0];
    triangle_points[5][2][0][1] = rect_points_3D[5][1];
    triangle_points[5][2][0][2] = rect_points_3D[5][2];

    triangle_points[5][2][1][0] = rect_points_3D[1][0];
    triangle_points[5][2][1][1] = rect_points_3D[1][1];
    triangle_points[5][2][1][2] = rect_points_3D[1][2];

    triangle_points[5][2][2][0] = rect_points_3D[7][0];
    triangle_points[5][2][2][1] = rect_points_3D[7][1];
    triangle_points[5][2][2][2] = rect_points_3D[7][2];


    triangle_points[6][0][0][0] = rect_points_3D[6][0];
    triangle_points[6][0][0][1] = rect_points_3D[6][1];
    triangle_points[6][0][0][2] = rect_points_3D[6][2];

    triangle_points[6][0][1][0] = rect_points_3D[4][0];
    triangle_points[6][0][1][1] = rect_points_3D[4][1];
    triangle_points[6][0][1][2] = rect_points_3D[4][2];

    triangle_points[6][0][2][0] = rect_points_3D[7][0];
    triangle_points[6][0][2][1] = rect_points_3D[7][1];
    triangle_points[6][0][2][2] = rect_points_3D[7][2];


    triangle_points[6][1][0][0] = rect_points_3D[6][0];
    triangle_points[6][1][0][1] = rect_points_3D[6][1];
    triangle_points[6][1][0][2] = rect_points_3D[6][2];

    triangle_points[6][1][1][0] = rect_points_3D[4][0];
    triangle_points[6][1][1][1] = rect_points_3D[4][1];
    triangle_points[6][1][1][2] = rect_points_3D[4][2];

    triangle_points[6][1][2][0] = rect_points_3D[2][0];
    triangle_points[6][1][2][1] = rect_points_3D[2][1];
    triangle_points[6][1][2][2] = rect_points_3D[2][2];


    triangle_points[6][2][0][0] = rect_points_3D[6][0];
    triangle_points[6][2][0][1] = rect_points_3D[6][1];
    triangle_points[6][2][0][2] = rect_points_3D[6][2];

    triangle_points[6][2][1][0] = rect_points_3D[2][0];
    triangle_points[6][2][1][1] = rect_points_3D[2][1];
    triangle_points[6][2][1][2] = rect_points_3D[2][2];

    triangle_points[6][2][2][0] = rect_points_3D[7][0];
    triangle_points[6][2][2][1] = rect_points_3D[7][1];
    triangle_points[6][2][2][2] = rect_points_3D[7][2];



    triangle_points[7][0][0][0] = rect_points_3D[7][0];
    triangle_points[7][0][0][1] = rect_points_3D[7][1];
    triangle_points[7][0][0][2] = rect_points_3D[7][2];

    triangle_points[7][0][1][0] = rect_points_3D[6][0];
    triangle_points[7][0][1][1] = rect_points_3D[6][1];
    triangle_points[7][0][1][2] = rect_points_3D[6][2];

    triangle_points[7][0][2][0] = rect_points_3D[5][0];
    triangle_points[7][0][2][1] = rect_points_3D[5][1];
    triangle_points[7][0][2][2] = rect_points_3D[5][2];


    triangle_points[7][1][0][0] = rect_points_3D[7][0];
    triangle_points[7][1][0][1] = rect_points_3D[7][1];
    triangle_points[7][1][0][2] = rect_points_3D[7][2];

    triangle_points[7][1][1][0] = rect_points_3D[5][0];
    triangle_points[7][1][1][1] = rect_points_3D[5][1];
    triangle_points[7][1][1][2] = rect_points_3D[5][2];

    triangle_points[7][1][2][0] = rect_points_3D[3][0];
    triangle_points[7][1][2][1] = rect_points_3D[3][1];
    triangle_points[7][1][2][2] = rect_points_3D[3][2];


    triangle_points[7][2][0][0] = rect_points_3D[7][0];
    triangle_points[7][2][0][1] = rect_points_3D[7][1];
    triangle_points[7][2][0][2] = rect_points_3D[7][2];

    triangle_points[7][2][1][0] = rect_points_3D[6][0];
    triangle_points[7][2][1][1] = rect_points_3D[6][1];
    triangle_points[7][2][1][2] = rect_points_3D[6][2];

    triangle_points[7][2][2][0] = rect_points_3D[3][0];
    triangle_points[7][2][2][1] = rect_points_3D[3][1];
    triangle_points[7][2][2][2] = rect_points_3D[3][2];

    return triangle_points;
}



std::vector<std::vector<std::vector<std::vector<int>>>> compute_2D(std::vector<std::vector<std::vector<std::vector<double>>>> triangle_points){
    std::vector<std::vector<std::vector<std::vector<int>>>> object_2D(
        triangle_points.size(), std::vector<std::vector<std::vector<int>>>(
                  triangle_points[0].size(), std::vector<std::vector<int>>(
                            3, std::vector<int>(2, 0))));

    // Iterating through all points on an object to compute the 2D window view point counterparts for a 3D object as observed by an eye behind the window.
    for (int i = 0; i < triangle_points.size(); i++){
        for (int j = 0; j < triangle_points[0].size(); j++){
            for (int k = 0; k < 3; k++){

                double anglex = atan2(triangle_points[i][j][k][0] - playerx, triangle_points[i][j][k][2] - playerz);
                int x = (int) (tan(anglex) * zscreendiff);

                double angley = atan2(triangle_points[i][j][k][1] - playery, triangle_points[i][j][k][2] - playerz);
                int y = (int) (tan(angley) * zscreendiff);

                object_2D[i][j][k][0] = (int) (x + 960);
                object_2D[i][j][k][1] = (int) (y + 540);
            }
        }
    }

    return object_2D;

}


void draw_triangles_sphere(SDL_Renderer* renderer, std::vector<std::vector<std::vector<std::vector<int>>>> triangle_points){

    for (int i = 0; i < triangle_points.size(); i++){
        for (int j = 0; j < triangle_points[0].size(); j++){
            SDL_RenderDrawLine(renderer, triangle_points[i][j][0][0], triangle_points[i][j][0][1], triangle_points[i][j][1][0], triangle_points[i][j][1][1]);
            SDL_RenderDrawLine(renderer, triangle_points[i][j][1][0], triangle_points[i][j][1][1], triangle_points[i][j][2][0], triangle_points[i][j][2][1]);
            SDL_RenderDrawLine(renderer, triangle_points[i][j][2][0], triangle_points[i][j][2][1], triangle_points[i][j][0][0], triangle_points[i][j][0][1]);
        }
    }
}


void draw_triangles_rectangle(SDL_Renderer* renderer, std::vector<std::vector<std::vector<std::vector<int>>>> triangle_points){

    for (int i = 0; i < triangle_points.size(); i++){
        for (int j = 0; j < triangle_points[0].size(); j++){
            SDL_RenderDrawLine(renderer, triangle_points[i][j][0][0], triangle_points[i][j][0][1], triangle_points[i][j][1][0], triangle_points[i][j][1][1]);
            SDL_RenderDrawLine(renderer, triangle_points[i][j][1][0], triangle_points[i][j][1][1], triangle_points[i][j][2][0], triangle_points[i][j][2][1]);
            SDL_RenderDrawLine(renderer, triangle_points[i][j][2][0], triangle_points[i][j][2][1], triangle_points[i][j][0][0], triangle_points[i][j][0][1]);
        }
    }
}


int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create an SDL window
    SDL_Window* window = SDL_CreateWindow("SDL2 Window",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          1920, 1080,
                                          SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create a renderer for the window
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Main loop flag
    bool isRunning = true;

    // Event handler
    SDL_Event event;

    // Main application loop
    while (isRunning) {
        
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false; // Exit loop on close event
            } else if (event.type == SDL_KEYDOWN){
                // Handle key press
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                        playerz++;
                        break;
                    case SDLK_s:
                        playerz--;
                        break;
                    case SDLK_d:
                        playerx++;
                        break;
                    case SDLK_a:
                        playerx--;
                        break;
                    case SDLK_r:
                        playery--;
                        break;
                    case SDLK_f:
                        playery++;
                        break;
                    case SDLK_e:
                        z1 -= 1;
                        z2 -= 2;
                        z3 -= 3;
                        break;
                    case SDLK_q:
                        z1 += 1;
                        z2 += 2;
                        z3 += 3;
                        break;
                    case SDLK_ESCAPE:
                        isRunning = false; // Exit the loop
                        break;
                }
            }
        }

        // Clear the screen with a color
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Blue color
        SDL_RenderClear(renderer);

        // Set the draw color.
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);


        std::vector<std::vector<double>> rect_points_horizon_1 = make_rectangle({0, 600, 2000}, 3000, 2, 1);
        std::vector<std::vector<std::vector<std::vector<double>>>> rect_horizon_triangle_points_1 = find_triangle_points_rectangle(rect_points_horizon_1);
        std::vector<std::vector<std::vector<std::vector<int>>>> rect_horizon_points_1 = compute_2D(rect_horizon_triangle_points_1);
        draw_triangles_rectangle(renderer, rect_horizon_points_1);

        std::vector<std::vector<double>> rect_points_horizon_2 = make_rectangle({2000, 600, 2000}, 3000, 2, 1);
        std::vector<std::vector<std::vector<std::vector<double>>>> rect_horizon_triangle_points_2 = find_triangle_points_rectangle(rect_points_horizon_2);
        std::vector<std::vector<std::vector<std::vector<int>>>> rect_horizon_points_2 = compute_2D(rect_horizon_triangle_points_2);
        draw_triangles_rectangle(renderer, rect_horizon_points_2);



        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);


        std::vector<std::vector<double>> sphere_points_3D_1 = make_sphere(renderer, {960, 530, z1}, 5, 12);
        std::vector<std::vector<std::vector<std::vector<double>>>> sphere_triangle_points_3D_1 = find_triangle_points_sphere(sphere_points_3D_1);
        std::vector<std::vector<std::vector<std::vector<int>>>> sphere_triangle_points_2D_1 = compute_2D(sphere_triangle_points_3D_1);
        draw_triangles_sphere(renderer, sphere_triangle_points_2D_1);

        std::vector<std::vector<double>> rect_points_3D_11 = make_rectangle({960, 550, z1}, 10, 20, 5);
        std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_11 = find_triangle_points_rectangle(rect_points_3D_11);
        std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_11 = compute_2D(rect_triangle_points_3D_11);
        draw_triangles_rectangle(renderer, rect_triangle_points_2D_11);


        std::vector<std::vector<double>> rect_points_3D_12 = make_rectangle({960 - 7, 550 - 5, z1}, 2, 2, 25);
        std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_12 = find_triangle_points_rectangle(rect_points_3D_12);
        std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_12 = compute_2D(rect_triangle_points_3D_12);
        draw_triangles_rectangle(renderer, rect_triangle_points_2D_12);

        std::vector<std::vector<double>> rect_points_3D_13 = make_rectangle({960 + 7, 550 - 5, z1}, 2, 2, 25);
        std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_13 = find_triangle_points_rectangle(rect_points_3D_13);
        std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_13 = compute_2D(rect_triangle_points_3D_13);
        draw_triangles_rectangle(renderer, rect_triangle_points_2D_13);

        std::vector<std::vector<double>> rect_points_3D_14 = make_rectangle({960 - 2, 550 + 12, z1}, 2, 5, 5);
        std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_14 = find_triangle_points_rectangle(rect_points_3D_14);
        std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_14 = compute_2D(rect_triangle_points_3D_14);
        draw_triangles_rectangle(renderer, rect_triangle_points_2D_14);

        std::vector<std::vector<double>> rect_points_3D_15 = make_rectangle({960 + 2, 550 + 12, z1}, 2, 5, 5);
        std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_15 = find_triangle_points_rectangle(rect_points_3D_15);
        std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_15 = compute_2D(rect_triangle_points_3D_15);
        draw_triangles_rectangle(renderer, rect_triangle_points_2D_15);





        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

        std::vector<std::vector<double>> sphere_points_3D_2 = make_sphere(renderer, {960 - 25, 530, z2}, 5, 12);
        std::vector<std::vector<std::vector<std::vector<double>>>> sphere_triangle_points_3D_2 = find_triangle_points_sphere(sphere_points_3D_2);
        std::vector<std::vector<std::vector<std::vector<int>>>> sphere_triangle_points_2D_2 = compute_2D(sphere_triangle_points_3D_2);
        draw_triangles_sphere(renderer, sphere_triangle_points_2D_2);

        std::vector<std::vector<double>> rect_points_3D_21 = make_rectangle({960 - 25, 550, z2}, 10, 20, 5);
        std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_21 = find_triangle_points_rectangle(rect_points_3D_21);
        std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_21 = compute_2D(rect_triangle_points_3D_21);
        draw_triangles_rectangle(renderer, rect_triangle_points_2D_21);


        std::vector<std::vector<double>> rect_points_3D_22 = make_rectangle({960 - 25 - 7, 550 - 5, z2}, 2, 10, 5);
        std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_22 = find_triangle_points_rectangle(rect_points_3D_22);
        std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_22 = compute_2D(rect_triangle_points_3D_22);
        draw_triangles_rectangle(renderer, rect_triangle_points_2D_22);

        std::vector<std::vector<double>> rect_points_3D_23 = make_rectangle({960 - 25 + 7, 550 - 5, z2}, 2, 10, 5);
        std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_23 = find_triangle_points_rectangle(rect_points_3D_23);
        std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_23 = compute_2D(rect_triangle_points_3D_23);
        draw_triangles_rectangle(renderer, rect_triangle_points_2D_23);

        std::vector<std::vector<double>> rect_points_3D_24 = make_rectangle({960 - 25 - 2, 550 + 12, z2}, 2, 5, 5);
        std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_24 = find_triangle_points_rectangle(rect_points_3D_24);
        std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_24 = compute_2D(rect_triangle_points_3D_24);
        draw_triangles_rectangle(renderer, rect_triangle_points_2D_24);

        std::vector<std::vector<double>> rect_points_3D_25 = make_rectangle({960 - 25 + 2, 550 + 12, z2}, 2, 5, 5);
        std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_25 = find_triangle_points_rectangle(rect_points_3D_25);
        std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_25 = compute_2D(rect_triangle_points_3D_25);
        draw_triangles_rectangle(renderer, rect_triangle_points_2D_25);




        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        
        std::vector<std::vector<double>> sphere_points_3D_3 = make_sphere(renderer, {960 + 25, 530, z3}, 5, 12);
        std::vector<std::vector<std::vector<std::vector<double>>>> sphere_triangle_points_3D_3 = find_triangle_points_sphere(sphere_points_3D_3);
        std::vector<std::vector<std::vector<std::vector<int>>>> sphere_triangle_points_2D_3 = compute_2D(sphere_triangle_points_3D_3);
        draw_triangles_sphere(renderer, sphere_triangle_points_2D_3);

        std::vector<std::vector<double>> rect_points_3D_31 = make_rectangle({960 + 25, 550, z3}, 10, 20, 5);
        std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_31 = find_triangle_points_rectangle(rect_points_3D_31);
        std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_31 = compute_2D(rect_triangle_points_3D_31);
        draw_triangles_rectangle(renderer, rect_triangle_points_2D_31);


        std::vector<std::vector<double>> rect_points_3D_32 = make_rectangle({960 + 25 - 7, 550 - 5, z3}, 2, 10, 5);
        std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_32 = find_triangle_points_rectangle(rect_points_3D_32);
        std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_32 = compute_2D(rect_triangle_points_3D_32);
        draw_triangles_rectangle(renderer, rect_triangle_points_2D_32);

        std::vector<std::vector<double>> rect_points_3D_33 = make_rectangle({960 + 25 + 7, 550 - 5, z3}, 2, 10, 5);
        std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_33 = find_triangle_points_rectangle(rect_points_3D_33);
        std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_33 = compute_2D(rect_triangle_points_3D_33);
        draw_triangles_rectangle(renderer, rect_triangle_points_2D_33);

        std::vector<std::vector<double>> rect_points_3D_34 = make_rectangle({960 + 25 - 2, 550 + 12, z3}, 2, 5, 5);
        std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_34 = find_triangle_points_rectangle(rect_points_3D_34);
        std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_34 = compute_2D(rect_triangle_points_3D_34);
        draw_triangles_rectangle(renderer, rect_triangle_points_2D_34);

        std::vector<std::vector<double>> rect_points_3D_35 = make_rectangle({960 + 25 + 2, 550 + 12, z3}, 2, 5, 5);
        std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_35 = find_triangle_points_rectangle(rect_points_3D_35);
        std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_35 = compute_2D(rect_triangle_points_3D_35);
        draw_triangles_rectangle(renderer, rect_triangle_points_2D_35);




        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

        std::vector<std::vector<double>> rect_points_3D_box_1 = make_rectangle({910, 567, 100}, 15, 15, 15);
        std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_box_1 = find_triangle_points_rectangle(rect_points_3D_box_1);
        std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_box_1 = compute_2D(rect_triangle_points_3D_box_1);
        draw_triangles_rectangle(renderer, rect_triangle_points_2D_box_1);


        std::vector<std::vector<double>> rect_points_3D_box_2 = make_rectangle({1000, 567, 150}, 25, 25, 25);
        std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_box_2 = find_triangle_points_rectangle(rect_points_3D_box_2);
        std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_box_2 = compute_2D(rect_triangle_points_3D_box_2);
        draw_triangles_rectangle(renderer, rect_triangle_points_2D_box_2);





        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);


        std::vector<std::vector<double>> rect_points_3D_box_3_1 = make_rectangle({800, 567, 100}, 25, 25, 25);
        std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_box_3_1 = find_triangle_points_rectangle(rect_points_3D_box_3_1);
        std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_box_3_1 = compute_2D(rect_triangle_points_3D_box_3_1);
        draw_triangles_rectangle(renderer, rect_triangle_points_2D_box_3_1);

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);


        std::vector<std::vector<double>> rect_points_3D_box_3_2 = make_rectangle({800 + 1, 567, 100}, 25, 25, 25);
        std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_box_3_2 = find_triangle_points_rectangle(rect_points_3D_box_3_2);
        std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_box_3_2 = compute_2D(rect_triangle_points_3D_box_3_2);
        draw_triangles_rectangle(renderer, rect_triangle_points_2D_box_3_2);

        std::vector<std::vector<double>> rect_points_3D_box_3_3 = make_rectangle({800 - 1, 567, 100}, 25, 25, 25);
        std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_box_3_3 = find_triangle_points_rectangle(rect_points_3D_box_3_3);
        std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_box_3_3 = compute_2D(rect_triangle_points_3D_box_3_3);
        draw_triangles_rectangle(renderer, rect_triangle_points_2D_box_3_3);


        std::vector<std::vector<double>> rect_points_3D_box_3_4 = make_rectangle({800, 567 + 1, 100}, 25, 25, 25);
        std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_box_3_4 = find_triangle_points_rectangle(rect_points_3D_box_3_4);
        std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_box_3_4 = compute_2D(rect_triangle_points_3D_box_3_4);
        draw_triangles_rectangle(renderer, rect_triangle_points_2D_box_3_4);

        std::vector<std::vector<double>> rect_points_3D_box_3_5 = make_rectangle({800, 567 - 1, 100}, 25, 25, 25);
        std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_box_3_5 = find_triangle_points_rectangle(rect_points_3D_box_3_5);
        std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_box_3_5 = compute_2D(rect_triangle_points_3D_box_3_5);
        draw_triangles_rectangle(renderer, rect_triangle_points_2D_box_3_5);






        
        // draw_triangles_sphere(renderer, compute_2D(find_triangle_points_sphere(make_sphere(renderer, {960 + 25, 530, z3}, 5, 12))));

        // std::vector<std::vector<double>> rect_points_3D_31 = make_rectangle({960 + 25, 550, z3}, 10, 20, 5);
        // std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_3i = find_triangle_points_rectangle(rect_points_3D_31);
        // std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_31 = compute_2D(rect_triangle_points_3D_31);
        // draw_triangles_rectangle(renderer, rect_triangle_points_2D_31);


        // std::vector<std::vector<double>> rect_points_3D_32 = make_rectangle({960 + 25 - 7, 550 - 5, z3}, 2, 10, 5);
        // std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_32 = find_triangle_points_rectangle(rect_points_3D_32);
        // std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_32 = compute_2D(rect_triangle_points_3D_32);
        // draw_triangles_rectangle(renderer, rect_triangle_points_2D_32);

        // std::vector<std::vector<double>> rect_points_3D_33 = make_rectangle({960 + 25 + 7, 550 - 5, z3}, 2, 10, 5);
        // std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_33 = find_triangle_points_rectangle(rect_points_3D_33);
        // std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_33 = compute_2D(rect_triangle_points_3D_33);
        // draw_triangles_rectangle(renderer, rect_triangle_points_2D_33);

        // std::vector<std::vector<double>> rect_points_3D_34 = make_rectangle({960 + 25 - 2, 550 + 12, z3}, 2, 5, 5);
        // std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_34 = find_triangle_points_rectangle(rect_points_3D_34);
        // std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_34 = compute_2D(rect_triangle_points_3D_34);
        // draw_triangles_rectangle(renderer, rect_triangle_points_2D_34);

        // std::vector<std::vector<double>> rect_points_3D_35 = make_rectangle({960 + 25 + 2, 550 + 12, z3}, 2, 5, 5);
        // std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_35 = find_triangle_points_rectangle(rect_points_3D_35);
        // std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_35 = compute_2D(rect_triangle_points_3D_35);
        // draw_triangles_rectangle(renderer, rect_triangle_points_2D_35);


        // Present the rendered frame
        SDL_RenderPresent(renderer);
    }

    // Clean up resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

//std::cout << "QQQQQQQQQ " + std::to_string(adj_points.size()) << std::endl;
