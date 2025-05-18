#include <GL/glut.h>
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

#include <random>

#include "main.h"
#include "Zombie.h"
#include "Arrow.h"
#include "Graphics.h"
#include "Star.h"

Graphics graphics;
int num_zombies;
std::vector<Zombie> zombie_vector;
std::vector<Arrow> arrow_vector;
std::vector<Star> star_vector;

int window_width = 1920;
int window_height = 1080;

const float aspect_ratio = 16.0f / 9.0f; // Desired aspect ratio

// Keyboard input callback
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            graphics.playerz += 5;
            // if (graphics.playerz < 1000){
            //     graphics.playerz += 5;
            // }
            break;
        case 's':
            graphics.playerz -= 5;
            // if (graphics.playerz > 0){
            //     graphics.playerz -= 5;
            // }
            break;
        case 'd':
            graphics.playerx += 5;
            // if (graphics.playerx < 1920){
            //     graphics.playerx += 5;
            // }
            break;
        case 'a':
            graphics.playerx -= 5;
            // if (graphics.playerx > 0){
            //     graphics.playerx -= 5;
            // }
            break;
        case 'r':
            if (graphics.playery > 0){
                graphics.playery -= 5;
            }
            break;
        case 'f':
            if (graphics.playery < 1080){
                graphics.playery += 5;
            }
            break;
        case 'e':
            for (int i = 0; i < num_zombies; i++){
                zombie_vector[i].move(1);
                zombie_vector[i].render(&graphics);
            }
            break;
        case 'q':
            for (int j = 0; j < num_zombies; j++){
                zombie_vector[j].move(-1);
                zombie_vector[j].render(&graphics);
            }
            break;
        case 'z':
            graphics.anglex_adj -= 0.01745329 * 2;
            break;
        case 'c':
            graphics.anglex_adj += 0.01745329 * 2;
            break;
        case 'x':
            arrow_vector[0].move(&graphics);
            break;

        case '/':
            
            std::cout << "-----------------\n";

            for (int i = 0; i < zombie_vector[0].rect_points_3D_leg1.size(); i++){

                for (int j = 0; j < zombie_vector[0].rect_points_3D_leg1[0].size(); j++){
                    std::cout << i << " " << zombie_vector[0].rect_points_3D_leg1[i][j];
                    std::cout << "\n";
                }
                std::cout << "---\n";
            }
            break;

        case 27: //ESC key
            exit(0);
    }
}


void mouse_click(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        //std::cout << "Mouse clicked at: (" << x << ", " << y << ")\n";

        // Check which button was pressed
        switch (button) {
            case GLUT_LEFT_BUTTON:
                arrow_vector.emplace_back(Arrow(&graphics, x, y));
                break;
            case GLUT_RIGHT_BUTTON:
                break;
            case GLUT_MIDDLE_BUTTON:
                break;
        }
    }
}


void reshapen_window_recal(int before_width, int before_height){
    window_width = glutGet(GLUT_WINDOW_WIDTH);
    window_height = glutGet(GLUT_WINDOW_HEIGHT);




    glViewport(0, 0, window_width, window_height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, window_width, window_height, 0); // Map OpenGL coordinates to screen pixels

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();




    // window_width = before_width;
    // window_height = before_height;



    // const float logical_width = 1920.0f;
    // const float logical_height = 1080.0f;
    // const float aspect_ratio = logical_width / logical_height;
    // float window_aspect = (float)window_width / (float)window_height;

    // // vp is for viewport
    // int vp_width, vp_height;
    // int vp_x = 0, vp_y = 0;

    // if (window_aspect > aspect_ratio) {
    //     // Window is wider than logical aspect — pillarbox /gpt
    //     vp_height = window_height;
    //     vp_width = (int)(window_height * aspect_ratio);
    //     vp_x = (window_width - vp_width) / 2;
    // } else {
    //     // Window is taller than logical aspect — letterbox /gpt
    //     vp_width = window_width;
    //     vp_height = (int)(window_width / aspect_ratio);
    //     vp_y = (window_height - vp_height) / 2;
    // }

    // // Centered viewport with fixed aspect ratio
    // glViewport(vp_x, vp_y, vp_width, vp_height);

    // // Fixed logical projection
    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // gluOrtho2D(0.0, logical_width, logical_height, 0.0);

    // glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();



}


void render_all(){
        graphics.clear_draw_screen();

        for (int i = 0; i < star_vector.size(); i++){
            star_vector[i].move(&graphics);
            star_vector[i].render(&graphics);
        }

        graphics.set_color(1.0f, 0.0f, 0.0f);
        graphics.draw_horizon();

        std::vector<std::vector<std::vector<std::vector<int>>>> floor_points_2D = graphics.compute_2D_lines(graphics.floor_points_3D);
        graphics.draw_floor_lines(floor_points_2D);

        graphics.set_color(0.0f, 0.0f, 1.0f);

        int zombie_to_remove = -1;
        int arrow_to_remove = -1;
    

        // Check for collision for all arrows hitting all zombeis
        for (int i = 0; i < arrow_vector.size(); i++){

            for (double j = 0; j < num_zombies; j++){
                if (zombie_vector[j].rect_points_3D_body[0][0] <= arrow_vector[i].x &&
                        zombie_vector[j].rect_points_3D_body[1][0] >= arrow_vector[i].x &&
                        zombie_vector[j].rect_points_3D_body[0][1] <= arrow_vector[i].y &&
                        zombie_vector[j].rect_points_3D_body[2][1] >= arrow_vector[i].y &&
                        zombie_vector[j].rect_points_3D_body[0][2] >= arrow_vector[i].z &&
                        zombie_vector[j].rect_points_3D_body[4][2] <= arrow_vector[i].z){

                    zombie_to_remove = j;
                    arrow_to_remove = i;
                    break;
                }
            }

            if (zombie_to_remove != -1){
                
                zombie_vector.erase(zombie_vector.begin() + zombie_to_remove);
                arrow_vector.erase(arrow_vector.begin() + arrow_to_remove);
                num_zombies--;
                zombie_to_remove = -1;
                arrow_to_remove = -1;
            }   

        }

        for (double i = 0; i < num_zombies; i++){
            zombie_vector[i].render(&graphics);
        }

        graphics.set_color(1.0f, 1.0f, 1.0f);

        for (int i = 0; i < arrow_vector.size(); i++){
            arrow_vector[i].move(&graphics);
            arrow_vector[i].render(&graphics);
        }


        glutPostRedisplay();
        graphics.present_frame();

}


int main(int argc, char* argv[]) {
    
    Graphics graphics;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("ZOMBEIS");

    //glutReshapeFunc(reshapen_window_recal);

    // Set up orthographic projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, window_width, window_height, 0); // Map OpenGL coordinates to screen pixels

    // Main loop flag
    bool isRunning = true;

    // Event handler
    //SDL_Event event;

    // Create a random device (seed source)
    std::random_device rd;

    // Initialize a random number generator (Mersenne Twister)
    std::mt19937 gen(rd());

    // Define a distribution range (e.g., between 1 and 100)
    // std::uniform_int_distribution<> distribx(-19040, 20960);
    // std::uniform_int_distribution<> distribz(500, 10000);

    // std::uniform_int_distribution<> distribx(-1040, 1960);
    // std::uniform_int_distribution<> distribz(500, 10000);
    // std::uniform_int_distribution<> distribs(1, 15);

    std::uniform_int_distribution<> distribx(460, 1460);
    //std::uniform_int_distribution<> distribz(500, 10000);
    std::uniform_int_distribution<> distribz(500, 5000);
    std::uniform_int_distribution<> distribs(1, 15);

    int random_numx = distribx(gen);
    int random_numz = distribz(gen);
    int random_nums = distribs(gen);

    //num_zombies = 100;
    num_zombies = 50;

    for (double i = 0; i < num_zombies; i++){
        random_numx = distribx(gen);
        random_numz = distribz(gen);
        zombie_vector.emplace_back(Zombie(&graphics, random_numx, 1064, random_numz));
        zombie_vector[i].render(&graphics);
    }

    // Randomly setting speed for zombies.
    for (double i = 0; i < num_zombies; i++){
        random_nums = distribs(gen);
        zombie_vector[i].speed = random_nums;
    }



    // Making stars
    std::uniform_int_distribution<> distriby(-1800, -1100);
    int random_numy = distriby(gen);

    for (int i = -10040; i < 10460; i += 500){
        for (int k = 1000; k < 50000; k += 500){
            random_numy = distriby(gen);
            star_vector.emplace_back(Star(&graphics, (double)i, (double)random_numy, (double)k, -2000, -1000));
        }
    }

    //star_vector.emplace_back(Star(&graphics, 960, 1060, 1010)); 


    //arrow_vector.emplace_back(Arrow(&graphics));
    
    // Register the keyboard input callback
    glutKeyboardFunc(keyboard);

    // Register the mouse callback function
    glutMouseFunc(mouse_click);

    // Register the display function.
    glutDisplayFunc(render_all);

    glutMainLoop();

    return 0;
}



//FIXX:
// -distance-based render of objects so far away objects not in front of close ones
// -fix turning
// -make horizon physical line at end of grid
// -make arrows tilt?
// -make bow
// -make arrows more detailed visually
// -make world spherical

// -refine zombei leg movement animation
// -fix hollow portions of zombei heads