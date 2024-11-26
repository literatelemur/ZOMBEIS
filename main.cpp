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
int playerz = 0;

std::array<std::array<int, 3>, 6> make_sphere(SDL_Renderer* renderer, int complexity){

    //(x - 960)^2 + (y - 540)^2 + (z - 10)^2 = radius^2

    //std::array<std::array<int, 3>, 6> sphere = {};

    
    // std::array<std::array<int, 3>, 6> sphere1 = {};

    // int rad = 10;
    // int dist_down = rad;
    // int dist_up = 0;
    // int count = 1;

    // sphere1[0][0] = 960 - rad;
    // sphere1[0][1] = 540;
    // sphere1[0][2] = 25;

    // sphere1[1][0] = 960 + rad;
    // sphere1[1][1] = 540;
    // sphere1[1][2] = 25;

    // sphere1[2][0] = 960;
    // sphere1[2][1] = 540 - rad;
    // sphere1[2][2] = 25;

    // sphere1[3][0] = 960;
    // sphere1[3][1] = 540 + rad;
    // sphere1[3][2] = 25;

    // sphere1[4][0] = 960;
    // sphere1[4][1] = 540;
    // sphere1[4][2] = 25 + rad;

    // sphere1[5][0] = 960;
    // sphere1[5][1] = 540;
    // sphere1[5][2] = 25 - rad;



//     std::vector<int> center = {960, 540, 25};

//     double radius = 10;
//     double angle_diff = 90;
//     double offset = 0;

//     for (int j = 0; j < 1; j++){
//         double angle = 0;

//         angle = angle + offset;

//         for (int i = 0; i < 4; i++){

//             double angle_rad = angle * M_PI / 180.0;

//             int x = sin(angle_rad) * radius;
//             int y = cos(angle_rad) * radius;
//             int z = center[2];

//             sphere[i][0] = center[0] + x;
//             sphere[i][1] = center[1] - y;
//             sphere[i][2] = center[2];

//             angle = angle + angle_diff;
// std::cout << "shpere " + std::to_string(j) + " " + std::to_string(i) + " " + std::to_string(sphere[i][0]) << std::endl;
//         std::cout << "shpere " + std::to_string(j) + " " + std::to_string(i) + " " + std::to_string(sphere[i][1]) << std::endl;
//         std::cout << "shpere " + std::to_string(j) + " " + std::to_string(i) + " " + std::to_string(sphere[i][2]) << std::endl;

//         SDL_RenderDrawLine(renderer, sphere[i][0], sphere[i][1], sphere[i][0] + 5, sphere[i][1] + 5);
//         }

//         angle = 0;
//         angle = angle + offset;
//         for (int i = 4; i < 6; i++){

//             double angle_rad = angle * M_PI / 180.0;

//             int x = sin(angle_rad) * radius;
//             int y = center[1];
//             int z = cos(angle_rad) * radius;

//             sphere[i][0] = center[0] + x;
//             sphere[i][1] = center[1];
//             sphere[i][2] = center[2] + z;

//             angle = angle + angle_diff * 2;
//             std::cout << "shpere " + std::to_string(j) + " " + std::to_string(i) + " " + std::to_string(sphere[i][0]) << std::endl;
//         std::cout << "shpere " + std::to_string(j) + " " + std::to_string(i) + " " + std::to_string(sphere[i][1]) << std::endl;
//         std::cout << "shpere " + std::to_string(j) + " " + std::to_string(i) + " " + std::to_string(sphere[i][2]) << std::endl;

//         SDL_RenderDrawLine(renderer, sphere[i][0], sphere[i][1], sphere[i][0] + 5, sphere[i][1] + 5);
//         }
//         offset = 45;
//     }




    std::vector<int> center = {960, 540, 25};

    double radius = 10;
    double angle_diff = 90;
    double offset = 0;

    int vertices = 10 * (complexity * complexity) + 2;
    double angle_change = 360 / (vertices / 3);

    int i = 0;
    for (int anglex = 0; anglex < 360; anglex + angle_change){
        for (int angley = 0; angley < 360; angley + angle_change){
            for (int anglez = 0; anglez < 360; anglez + angle_change){
                
                double anglex_rad = anglex * M_PI / 180.0;
                double angley_rad = angley * M_PI / 180.0;
                double anglez_rad = anglez * M_PI / 180.0;

                int x = sin(anglex) * radius;
                int y = cos(angley) * radius;
                int z = cos(angley) * radius;

                sphere[i][0] = center[0] + x;
                sphere[i][1] = center[1] - y;
                sphere[i][2] = center[2] + z;

                std::cout << "shpere " + std::to_string(i) + " " + std::to_string(sphere[i][0]) << std::endl;
                std::cout << "shpere " + std::to_string(i) + " " + std::to_string(sphere[i][1]) << std::endl;
                std::cout << "shpere " + std::to_string(i) + " " + std::to_string(sphere[i][2]) << std::endl;
                i++;
            }
        }
    }

    return sphere;
}


std::vector<std::vector<std::vector<std::vector<int>>>> find_triangle_points(std::array<std::array<int, 3>, 6> sphere_3D){
    std::vector<std::vector<std::vector<std::vector<int>>>> triangle_points(
        6, std::vector<std::vector<std::vector<int>>>(
                  4, std::vector<std::vector<int>>(
                            3, std::vector<int>(3, 0))));

    for (int i = 0; i < 6; i++){

        // Determining shortest line between each point and all other points.
        double shortest = 99999;
        double dist1;

        for (int j = 0; j < 6; j++){
            if (i == j){continue;}
            double xdist = std::abs(sphere_3D[j][0] - sphere_3D[i][0]);
            double ydist = std::abs(sphere_3D[j][1] - sphere_3D[i][1]);
            double zdist = std::abs(sphere_3D[j][2] - sphere_3D[i][2]);

            // int largest = std::max(xdist, std::max(ydist, zdist));
            // int second_largest = std::max(xdist == largest ? -1 : xdist, std::max(ydist == largest ? -1 : ydist, zdist == largest ? -1 : zdist));

            int larger1 = 0;
            int larger2 = 0;
            if (xdist <= ydist and xdist <= zdist){
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
        std::vector<int> adj_points;
        for (int j = 0; j < 6; j++){
            if (i == j){continue;}
            double xdist = std::abs(sphere_3D[j][0] - sphere_3D[i][0]);
            double ydist = std::abs(sphere_3D[j][1] - sphere_3D[i][1]);
            double zdist = std::abs(sphere_3D[j][2] - sphere_3D[i][2]);

            int larger1 = 0;
            int larger2 = 0;
            if (xdist <= ydist and xdist <= zdist){
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
            if (dist1 == shortest){
                adj_points.emplace_back(j);
            }
        }

        // Determining if adjacent points have same shortest line between adjacent point's adjcent points so that a full equilateral triangle is found.
        double dist2;
        double dist3;
        for (int a = 0; a < adj_points.size(); a++){
            for (int k = 0; k < 6; k++){
                if (k == i || k == adj_points[a] || i == adj_points[a]){continue;}
                double xdist = std::abs(sphere_3D[k][0] - sphere_3D[adj_points[a]][0]);
                double ydist = std::abs(sphere_3D[k][1] - sphere_3D[adj_points[a]][1]);
                double zdist = std::abs(sphere_3D[k][2] - sphere_3D[adj_points[a]][2]);

                int larger1 = 0;
                int larger2 = 0;
                if (xdist <= ydist and xdist <= zdist){
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

                xdist = std::abs(sphere_3D[k][0] - sphere_3D[i][0]);
                ydist = std::abs(sphere_3D[k][1] - sphere_3D[i][1]);
                zdist = std::abs(sphere_3D[k][2] - sphere_3D[i][2]);

                larger1 = 0;
                larger2 = 0;
                if (xdist <= ydist and xdist <= zdist){
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

                if (dist2 == shortest && dist3 == shortest){

                    triangle_points[i][a][0][0] = (sphere_3D[i][0]);
                    triangle_points[i][a][0][1] = (sphere_3D[i][1]);
                    triangle_points[i][a][0][2] = (sphere_3D[i][2]);
                    triangle_points[i][a][1][0] = (sphere_3D[adj_points[a]][0]);
                    triangle_points[i][a][1][1] = (sphere_3D[adj_points[a]][1]);
                    triangle_points[i][a][1][2] = (sphere_3D[adj_points[a]][2]);
                    triangle_points[i][a][2][0] = (sphere_3D[k][0]);
                    triangle_points[i][a][2][1] = (sphere_3D[k][1]);
                    triangle_points[i][a][2][2] = (sphere_3D[k][2]);
                }
            }
        }
    }

    return triangle_points;
}

std::vector<std::vector<std::vector<std::vector<int>>>> compute_2D(std::vector<std::vector<std::vector<std::vector<int>>>> triangle_points){
    std::vector<std::vector<std::vector<std::vector<int>>>> object_2D(
        6, std::vector<std::vector<std::vector<int>>>(
                  4, std::vector<std::vector<int>>(
                            3, std::vector<int>(2, 0))));

    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 4; j++){
            for (int k = 0; k < 3; k++){
                double anglex = atan2(triangle_points[i][j][k][0] - playerx, triangle_points[i][j][k][2] - playerz);
                int x = (int) (tan(anglex) * zscreendiff);

                double angley = atan2(triangle_points[i][j][k][1] - playery, triangle_points[i][j][k][2] - playerz);
                int y = (int) (tan(angley) * zscreendiff);

                object_2D[i][j][k][0] = x + 960;
                object_2D[i][j][k][1] = y + 540;
            }
        }
    }

    return object_2D;

}

void draw(SDL_Renderer* renderer, std::vector<std::vector<std::vector<std::vector<int>>>> triangle_points){

    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 4; j++){
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

        // // Define the triangle vertices
        // int x1 = 400, y1 = 100;  // Top vertex
        // int x2 = 300, y2 = 400;  // Bottom-left vertex
        // int x3 = 500, y3 = 400;  // Bottom-right vertex

        // // Draw the triangle
        // SDL_RenderDrawLine(renderer, x1, y1, x2, y2);  // Line from top to bottom-left
        // SDL_RenderDrawLine(renderer, x2, y2, x3, y3);  // Line from bottom-left to bottom-right
        // SDL_RenderDrawLine(renderer, x3, y3, x1, y1);  // Line from bottom-right to top



        std::array<std::array<int, 3>, 6> sphere_3D = make_sphere(renderer, 1);
        std::vector<std::vector<std::vector<std::vector<int>>>> triangle_points_3D = find_triangle_points(sphere_3D);
        std::vector<std::vector<std::vector<std::vector<int>>>> triangle_points_2D = compute_2D(triangle_points_3D);
        draw(renderer, triangle_points_2D);


        // Present the rendered frame
        SDL_RenderPresent(renderer);
    }

    // Clean up resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


// #include <iostream>
// int main(int argc, char* argv[]) {
//     std::cout << "Hello, World!" << std::endl;
// }std::vector<std::vector<int>>
//std::cout << "QQQQQQQQQ " + std::to_string(adj_points.size()) << std::endl;
