#include <SDL2/SDL.h>
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

#include "Graphics.h"

// class Graphics {

//     public:

        
        Graphics::Graphics(){

            zscreendiff = 1000;
            playerx = 960;
            playery = 1060;
            playerz = 0;

            anglex_adj = 0;
            
            // Initialize SDL
            if (SDL_Init(SDL_INIT_VIDEO) != 0) {
                std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
                //return 1;
            }

            // Create an SDL window
            window = SDL_CreateWindow("SDL2 Window with GPU",
                                                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                                1920, 1080,
                                                SDL_WINDOW_SHOWN);
            if (window == nullptr) {
                std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
                SDL_Quit();
                //return 1;
            }

            // Create a renderer for the window
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

            if (renderer == nullptr) {
                std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
                SDL_DestroyWindow(window);
                SDL_Quit();
                //return 1;
            }

            SDL_RendererInfo info;
            SDL_GetRendererInfo(renderer, &info);
            std::cout << "Renderer Name: " << info.name << std::endl;
            if (info.flags & SDL_RENDERER_ACCELERATED) {
                std::cout << "Using hardware acceleration!" << std::endl;
            }



            double x_stop = 19200;
            double z_stop = 20000;

            floor_points_3D.emplace_back();

            int i = 0;
            for (double x = -10000; x < x_stop; x += 100){
                floor_points_3D[0].emplace_back();
                floor_points_3D[0][i].emplace_back();
                floor_points_3D[0][i][0].emplace_back(0);
                floor_points_3D[0][i][0].emplace_back(0);
                floor_points_3D[0][i][0].emplace_back(0);
                floor_points_3D[0][i][0][0] = x;
                floor_points_3D[0][i][0][1] = 1080;
                floor_points_3D[0][i][0][2] = 100;

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
            for (double z = 100; z < z_stop; z += 100){
                floor_points_3D[1].emplace_back();
                floor_points_3D[1][i].emplace_back();
                floor_points_3D[1][i][0].emplace_back(0);
                floor_points_3D[1][i][0].emplace_back(0);
                floor_points_3D[1][i][0].emplace_back(0);
                floor_points_3D[1][i][0][0] = -10000;
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

            //floor_points_3D = {{{{500, 1080, 100}, {500, 1080, 1000}}, {{700, 1080, 100}, {700, 1080, 1000}}}};


            // floor_points_3D = {
            //     {
            //         {
            //             {500, 1080, 100}, 
            //             {500, 1080, 1000}
            //         },
            //         {
            //             {700, 1080, 100}, 
            //             {700, 1080, 1000}
            //         }
            //     }
            // };


        }


        std::vector<std::vector<double>> Graphics::make_sphere(std::vector<double> center, int radius, int num_points){

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


        std::vector<std::vector<double>> Graphics::make_rectangle(std::vector<double> center, double top_length, double side_length, double depth){
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


        std::vector<std::vector<std::vector<std::vector<double>>>> Graphics::find_triangle_points_rectangle(std::vector<std::vector<double>> rect_points_3D){

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


        std::vector<std::vector<std::vector<std::vector<int>>>> Graphics::compute_2D_lines(std::vector<std::vector<std::vector<std::vector<double>>>> floor_points_3D){

            std::vector<std::vector<std::vector<std::vector<int>>>> floor_points_2D;

            // Iterating through all points on an object to compute the 2D window view point counterparts for a 3D object as observed by an eye behind the window.
            for (int i = 0; i < floor_points_3D.size(); i++){
                floor_points_2D.emplace_back();

                for (int j = 0; j < floor_points_3D[i].size(); j++){
                    floor_points_2D[i].emplace_back();

                    for (int k = 0; k < 2; k++){
                        floor_points_2D[i][j].emplace_back();
                        floor_points_2D[i][j][k].emplace_back(0);
                        floor_points_2D[i][j][k].emplace_back(0);

                        double anglex = atan2(floor_points_3D[i][j][k][0] - playerx, floor_points_3D[i][j][k][2] - playerz) + anglex_adj;
                        int x = (int) (tan(anglex) * zscreendiff);

                        double angley = atan2(floor_points_3D[i][j][k][1] - playery, floor_points_3D[i][j][k][2] - playerz);
                        int y = (int) (tan(angley) * zscreendiff);

                        floor_points_2D[i][j][k][0] = (int) (x + 960);
                        floor_points_2D[i][j][k][1] = (int) (y + 540);
                    }
                }
            }

            return floor_points_2D;

        }


        std::vector<std::vector<std::vector<std::vector<int>>>> Graphics::compute_2D_triangles(std::vector<std::vector<std::vector<std::vector<double>>>> triangle_points){
            std::vector<std::vector<std::vector<std::vector<int>>>> object_2D(
                triangle_points.size(), std::vector<std::vector<std::vector<int>>>(
                        triangle_points[0].size(), std::vector<std::vector<int>>(
                                    3, std::vector<int>(2, 0))));

            // Iterating through all points on an object to compute the 2D window view point counterparts for a 3D object as observed by an eye behind the window.
            for (int i = 0; i < triangle_points.size(); i++){
                for (int j = 0; j < triangle_points[0].size(); j++){
                    for (int k = 0; k < 3; k++){

                        double anglex = atan2(triangle_points[i][j][k][0] - playerx, triangle_points[i][j][k][2] - playerz) + anglex_adj;
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


        void Graphics::clear_draw_screen(){
            // Clear the screen with a color
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
        }


        void Graphics::draw_horizon(){

            //std::vector<std::vector<double>> rect_points_horizon_1 = make_rectangle({0, 1080, 2000}, 3000, 2, 1);
            // std::vector<std::vector<double>> rect_points_horizon_1 = make_rectangle({0, 1080, 20000}, 300000, 2, 1);
            // std::vector<std::vector<std::vector<std::vector<double>>>> rect_horizon_triangle_points_1 = find_triangle_points_rectangle(rect_points_horizon_1);
            // std::vector<std::vector<std::vector<std::vector<int>>>> rect_horizon_points_1 = compute_2D_triangles(rect_horizon_triangle_points_1);
            // draw_triangles_rectangle(rect_horizon_points_1);

            // std::vector<std::vector<double>> rect_points_horizon_2 = make_rectangle({2000, 1080, 20000}, 300000, 2, 1);
            // std::vector<std::vector<std::vector<std::vector<double>>>> rect_horizon_triangle_points_2 = find_triangle_points_rectangle(rect_points_horizon_2);
            // std::vector<std::vector<std::vector<std::vector<int>>>> rect_horizon_points_2 = compute_2D_triangles(rect_horizon_triangle_points_2);
            // draw_triangles_rectangle(rect_horizon_points_2);




            // std::vector<std::vector<std::vector<std::vector<double>>>> horizon_points_3D = {{{{0, 1080, 20000}, {19200, 1080, 20000}}}};
            // std::vector<std::vector<std::vector<std::vector<int>>>> horizon_points_2D = compute_2D_lines(horizon_points_3D);
            // draw_floor_lines(horizon_points_2D);


            SDL_RenderDrawLine(renderer, 0, 540, 1920, 540);

            // for (double i = 0; i < 1980; i++){
            //     for (double j = 0; j < 1000; j++){




            // std::vector<std::vector<double>> rect_points_floor;
            // std::vector<std::vector<std::vector<std::vector<double>>>> rect_floor_triangle_points;
            // std::vector<std::vector<std::vector<std::vector<int>>>> rect_floor_points;

            // for (double x = 0; x < 1920; x += 100){
            //     for (double z = 100; z < 2000; z += 100){
            //         rect_points_floor = make_rectangle({x, 1079, z}, 100, 0, 100);
            //         rect_floor_triangle_points = find_triangle_points_rectangle(rect_points_floor);
            //         rect_floor_points = compute_2D(rect_floor_triangle_points);
            //         draw_triangles_rectangle(rect_floor_points);
            //     }
            // }

        }


        void Graphics::draw_floor_lines(std::vector<std::vector<std::vector<std::vector<int>>>> floor_points_2D){

            for (int i = 0; i < floor_points_2D.size(); i++){
                for (int j = 0; j < floor_points_2D[i].size(); j++){
                    SDL_RenderDrawLine(renderer, floor_points_2D[i][j][0][0], floor_points_2D[i][j][0][1], floor_points_2D[i][j][1][0], floor_points_2D[i][j][1][1]);
                }
            }

        }


        void Graphics::draw_triangles_sphere(std::vector<std::vector<std::vector<std::vector<int>>>> triangle_points){

            for (int i = 0; i < triangle_points.size(); i++){
                //if (triangle_points[i][0][0][2] > 5){
                    for (int j = 0; j < triangle_points[0].size(); j++){
                        SDL_RenderDrawLine(renderer, triangle_points[i][j][0][0], triangle_points[i][j][0][1], triangle_points[i][j][1][0], triangle_points[i][j][1][1]);
                        SDL_RenderDrawLine(renderer, triangle_points[i][j][1][0], triangle_points[i][j][1][1], triangle_points[i][j][2][0], triangle_points[i][j][2][1]);
                        SDL_RenderDrawLine(renderer, triangle_points[i][j][2][0], triangle_points[i][j][2][1], triangle_points[i][j][0][0], triangle_points[i][j][0][1]);
                    }
                //}
            }
        }


        void Graphics::draw_triangles_rectangle(std::vector<std::vector<std::vector<std::vector<int>>>> triangle_points){

            // Create a surface with a single line
            SDL_Surface* lineSurface = SDL_CreateRGBSurface(0, 2, 1, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
            SDL_FillRect(lineSurface, nullptr, SDL_MapRGB(lineSurface->format, 0, 255, 0));  // White line

            // Convert the surface to a texture
            SDL_Texture* lineTexture = SDL_CreateTextureFromSurface(renderer, lineSurface);
            SDL_FreeSurface(lineSurface);

            // Now you can render this line texture multiple times at different positions
            // SDL_Rect destRect = {100, 100, 200, 1};  // 200px long line
            // SDL_RenderCopy(renderer, lineTexture, nullptr, &destRect);



            for (int i = 0; i < triangle_points.size(); i++){
                //if (triangle_points[i][0][0][2] > 5){
                    for (int j = 0; j < triangle_points[0].size(); j++){
                        SDL_RenderDrawLine(renderer, triangle_points[i][j][0][0], triangle_points[i][j][0][1], triangle_points[i][j][1][0], triangle_points[i][j][1][1]);
                        //SDL_RenderDrawLine(renderer, triangle_points[i][j][1][0], triangle_points[i][j][1][1], triangle_points[i][j][2][0], triangle_points[i][j][2][1]);
                        SDL_RenderDrawLine(renderer, triangle_points[i][j][2][0], triangle_points[i][j][2][1], triangle_points[i][j][0][0], triangle_points[i][j][0][1]);
                    }
                //}
            }

            // for (int i = 0; i < triangle_points.size(); i++){
            //     //if (triangle_points[i][0][0][2] > 5){
            //         for (int j = 0; j < triangle_points[0].size(); j++){
            //             for (int k = 0; k < 3; k++){

            //                 SDL_Rect destRect = {triangle_points[i][j][0][0], triangle_points[i][j][0][1], triangle_points[i][j][1][0] - triangle_points[i][j][0][0], triangle_points[i][j][1][1] - triangle_points[i][j][0][1]};
            //                 SDL_RenderCopy(renderer, lineTexture, nullptr, &destRect);

            //             }
            //         }
            //     //}
            // }

            // // Don't forget to clean up
            // SDL_DestroyTexture(lineTexture);
        }


        void Graphics::set_color(int r, int g, int b){
            // Set the draw color.
            SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        }

        void Graphics::present_frame(){
            // Present the rendered frame
            SDL_RenderPresent(renderer);
        }
//};