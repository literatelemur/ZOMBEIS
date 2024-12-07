#include <SDL2/SDL.h>
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

#include <random>

#include "Zombie.h"
#include "Graphics.h"


int main(int argc, char* argv[]) {
    
    Graphics graphics;

    // Main loop flag
    bool isRunning = true;

    // Event handler
    SDL_Event event;


    std::vector<Zombie> zombie_vector;


    // Create a random device (seed source)
    std::random_device rd;

    // Initialize a random number generator (Mersenne Twister)
    std::mt19937 gen(rd());

    // Define a distribution range (e.g., between 1 and 100)
    std::uniform_int_distribution<> distrib(1, 1920);


    int random_num = distrib(gen);

    for (double i = 0; i < 50; i++){
        random_num = distrib(gen);
        zombie_vector.emplace_back(Zombie(&graphics, random_num, 1064, 150));
        zombie_vector[i].render_zombie(&graphics);
    }

    // Change distribution range
    distrib = std::uniform_int_distribution<int>(1, 10);
    
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
                        if (graphics.playerz < 1000){
                            graphics.playerz += 5;
                        }
                    case SDLK_s:
                        if (graphics.playerz > 0){
                            graphics.playerz -= 5;
                        }
                        break;
                    case SDLK_d:
                        if (graphics.playerx < 1920){
                            graphics.playerx += 5;
                        }
                    case SDLK_a:
                        if (graphics.playerx > 0){
                            graphics.playerx -= 5;
                        }
                        break;
                    case SDLK_r:
                        if (graphics.playery > 0){
                            graphics.playery -= 5;
                        }
                        break;
                    case SDLK_f:
                        if (graphics.playery < 1080){
                            graphics.playery += 5;
                        }
                        break;
                    case SDLK_e:
                        for (int i = 0; i < 50; i++){
                            random_num = distrib(gen);
                            zombie_vector[i].move(random_num);
                        }
                        break;
                    case SDLK_q:
                        for (int j = 0; j < 50; j++){
                            random_num = distrib(gen);
                            zombie_vector[j].move(random_num * -1);
                        }
                        break;
                    case SDLK_ESCAPE:
                        isRunning = false; // Exit the loop
                        break;
                }
            }
        }

        graphics.clear_draw_screen();
        graphics.draw_horizon();

        for (double i = 0; i < 50; i++){
            zombie_vector[i].render_zombie(&graphics);
        }

        graphics.present_frame();

        
        // std::vector<std::vector<double>> sphere_points_3D_1 = make_sphere({960, 530, z1}, 5, 12);
        // std::vector<std::vector<std::vector<std::vector<double>>>> sphere_triangle_points_3D_1 = find_triangle_points_sphere(sphere_points_3D_1);
        // std::vector<std::vector<std::vector<std::vector<int>>>> sphere_triangle_points_2D_1 = compute_2D(sphere_triangle_points_3D_1);
        // draw_triangles_sphere(renderer, sphere_triangle_points_2D_1);

        // std::vector<std::vector<double>> rect_points_3D_11 = make_rectangle({960, 550, z1}, 10, 20, 5);
        // std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_11 = find_triangle_points_rectangle(rect_points_3D_11);
        // std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_11 = compute_2D(rect_triangle_points_3D_11);
        // draw_triangles_rectangle(renderer, rect_triangle_points_2D_11);


        // std::vector<std::vector<double>> rect_points_3D_12 = make_rectangle({960 - 7, 550 - 5, z1}, 2, 2, 25);
        // std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_12 = find_triangle_points_rectangle(rect_points_3D_12);
        // std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_12 = compute_2D(rect_triangle_points_3D_12);
        // draw_triangles_rectangle(renderer, rect_triangle_points_2D_12);

        // std::vector<std::vector<double>> rect_points_3D_13 = make_rectangle({960 + 7, 550 - 5, z1}, 2, 2, 25);
        // std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_13 = find_triangle_points_rectangle(rect_points_3D_13);
        // std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_13 = compute_2D(rect_triangle_points_3D_13);
        // draw_triangles_rectangle(renderer, rect_triangle_points_2D_13);

        // std::vector<std::vector<double>> rect_points_3D_14 = make_rectangle({960 - 2, 550 + 12, z1}, 2, 5, 5);
        // std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_14 = find_triangle_points_rectangle(rect_points_3D_14);
        // std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_14 = compute_2D(rect_triangle_points_3D_14);
        // draw_triangles_rectangle(renderer, rect_triangle_points_2D_14);

        // std::vector<std::vector<double>> rect_points_3D_15 = make_rectangle({960 + 2, 550 + 12, z1}, 2, 5, 5);
        // std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_15 = find_triangle_points_rectangle(rect_points_3D_15);
        // std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_15 = compute_2D(rect_triangle_points_3D_15);
        // draw_triangles_rectangle(renderer, rect_triangle_points_2D_15);





        // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

        // std::vector<std::vector<double>> sphere_points_3D_2 = make_sphere({960 - 25, 530, z2}, 5, 12);
        // std::vector<std::vector<std::vector<std::vector<double>>>> sphere_triangle_points_3D_2 = find_triangle_points_sphere(sphere_points_3D_2);
        // std::vector<std::vector<std::vector<std::vector<int>>>> sphere_triangle_points_2D_2 = compute_2D(sphere_triangle_points_3D_2);
        // draw_triangles_sphere(renderer, sphere_triangle_points_2D_2);

        // std::vector<std::vector<double>> rect_points_3D_21 = make_rectangle({960 - 25, 550, z2}, 10, 20, 5);
        // std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_21 = find_triangle_points_rectangle(rect_points_3D_21);
        // std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_21 = compute_2D(rect_triangle_points_3D_21);
        // draw_triangles_rectangle(renderer, rect_triangle_points_2D_21);


        // std::vector<std::vector<double>> rect_points_3D_22 = make_rectangle({960 - 25 - 7, 550 - 5, z2}, 2, 10, 5);
        // std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_22 = find_triangle_points_rectangle(rect_points_3D_22);
        // std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_22 = compute_2D(rect_triangle_points_3D_22);
        // draw_triangles_rectangle(renderer, rect_triangle_points_2D_22);

        // std::vector<std::vector<double>> rect_points_3D_23 = make_rectangle({960 - 25 + 7, 550 - 5, z2}, 2, 10, 5);
        // std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_23 = find_triangle_points_rectangle(rect_points_3D_23);
        // std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_23 = compute_2D(rect_triangle_points_3D_23);
        // draw_triangles_rectangle(renderer, rect_triangle_points_2D_23);

        // std::vector<std::vector<double>> rect_points_3D_24 = make_rectangle({960 - 25 - 2, 550 + 12, z2}, 2, 5, 5);
        // std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_24 = find_triangle_points_rectangle(rect_points_3D_24);
        // std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_24 = compute_2D(rect_triangle_points_3D_24);
        // draw_triangles_rectangle(renderer, rect_triangle_points_2D_24);

        // std::vector<std::vector<double>> rect_points_3D_25 = make_rectangle({960 - 25 + 2, 550 + 12, z2}, 2, 5, 5);
        // std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_25 = find_triangle_points_rectangle(rect_points_3D_25);
        // std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_25 = compute_2D(rect_triangle_points_3D_25);
        // draw_triangles_rectangle(renderer, rect_triangle_points_2D_25);




        // SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        
        // std::vector<std::vector<double>> sphere_points_3D_3 = make_sphere({960 + 25, 530, z3}, 5, 12);
        // std::vector<std::vector<std::vector<std::vector<double>>>> sphere_triangle_points_3D_3 = find_triangle_points_sphere(sphere_points_3D_3);
        // std::vector<std::vector<std::vector<std::vector<int>>>> sphere_triangle_points_2D_3 = compute_2D(sphere_triangle_points_3D_3);
        // draw_triangles_sphere(renderer, sphere_triangle_points_2D_3);

        // std::vector<std::vector<double>> rect_points_3D_31 = make_rectangle({960 + 25, 550, z3}, 10, 20, 5);
        // std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_31 = find_triangle_points_rectangle(rect_points_3D_31);
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




        // SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

        // std::vector<std::vector<double>> rect_points_3D_box_1 = make_rectangle({910, 567, 100}, 15, 15, 15);
        // std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_box_1 = find_triangle_points_rectangle(rect_points_3D_box_1);
        // std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_box_1 = compute_2D(rect_triangle_points_3D_box_1);
        // draw_triangles_rectangle(renderer, rect_triangle_points_2D_box_1);


        // std::vector<std::vector<double>> rect_points_3D_box_2 = make_rectangle({1000, 567, 150}, 25, 25, 25);
        // std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_box_2 = find_triangle_points_rectangle(rect_points_3D_box_2);
        // std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_box_2 = compute_2D(rect_triangle_points_3D_box_2);
        // draw_triangles_rectangle(renderer, rect_triangle_points_2D_box_2);





        // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);


        // std::vector<std::vector<double>> rect_points_3D_box_3_1 = make_rectangle({800, 567, 100}, 25, 25, 25);
        // std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_box_3_1 = find_triangle_points_rectangle(rect_points_3D_box_3_1);
        // std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_box_3_1 = compute_2D(rect_triangle_points_3D_box_3_1);
        // draw_triangles_rectangle(renderer, rect_triangle_points_2D_box_3_1);

        // SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);


        // std::vector<std::vector<double>> rect_points_3D_box_3_2 = make_rectangle({800 + 1, 567, 100}, 25, 25, 25);
        // std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_box_3_2 = find_triangle_points_rectangle(rect_points_3D_box_3_2);
        // std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_box_3_2 = compute_2D(rect_triangle_points_3D_box_3_2);
        // draw_triangles_rectangle(renderer, rect_triangle_points_2D_box_3_2);

        // std::vector<std::vector<double>> rect_points_3D_box_3_3 = make_rectangle({800 - 1, 567, 100}, 25, 25, 25);
        // std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_box_3_3 = find_triangle_points_rectangle(rect_points_3D_box_3_3);
        // std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_box_3_3 = compute_2D(rect_triangle_points_3D_box_3_3);
        // draw_triangles_rectangle(renderer, rect_triangle_points_2D_box_3_3);


        // std::vector<std::vector<double>> rect_points_3D_box_3_4 = make_rectangle({800, 567 + 1, 100}, 25, 25, 25);
        // std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_box_3_4 = find_triangle_points_rectangle(rect_points_3D_box_3_4);
        // std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_box_3_4 = compute_2D(rect_triangle_points_3D_box_3_4);
        // draw_triangles_rectangle(renderer, rect_triangle_points_2D_box_3_4);

        // std::vector<std::vector<double>> rect_points_3D_box_3_5 = make_rectangle({800, 567 - 1, 100}, 25, 25, 25);
        // std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D_box_3_5 = find_triangle_points_rectangle(rect_points_3D_box_3_5);
        // std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D_box_3_5 = compute_2D(rect_triangle_points_3D_box_3_5);
        // draw_triangles_rectangle(renderer, rect_triangle_points_2D_box_3_5);


        // SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

        // for (int i = 0; i < zombie_vector.size(); i++){
        //     for (int j = 0; j < 6; j++){
        //         if (j == 0){
        //             std::vector<std::vector<std::vector<std::vector<double>>>> sphere_triangle_points_3D = find_triangle_points_sphere(zombie_vector[i][j]);
        //             std::vector<std::vector<std::vector<std::vector<int>>>> sphere_triangle_points_2D = compute_2D(sphere_triangle_points_3D);
        //             draw_triangles_sphere(renderer, sphere_triangle_points_2D);

        //         } else{
        //             std::vector<std::vector<std::vector<std::vector<double>>>> rect_triangle_points_3D = find_triangle_points_rectangle(zombie_vector[i][j]);
        //             std::vector<std::vector<std::vector<std::vector<int>>>> rect_triangle_points_2D = compute_2D(rect_triangle_points_3D);
        //             draw_triangles_rectangle(renderer, rect_triangle_points_2D);
        //         }
        //     }
        // }
    }

    // Clean up resources
    SDL_DestroyRenderer(graphics.renderer);
    SDL_DestroyWindow(graphics.window);
    SDL_Quit();

    return 0;
}

//std::cout << "QQQQQQQQQ " + std::to_string(adj_points.size()) << std::endl;
