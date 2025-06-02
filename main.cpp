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

bool key_states[256] = { false };



void keyDown(unsigned char key, int idk1, int idk2) {
    key_states[key] = true;
}


void keyUp(unsigned char key, int idk1, int idk2){
    key_states[key] = false;
}


// Keyboard press check
void key_press_check() {
    if(key_states['w']){
        graphics.playerz += 5;
        // if (graphics.playerz < 1000){
        //     graphics.playerz += 5;
        // }
    }if(key_states['s']){
        graphics.playerz -= 5;
        // if (graphics.playerz > 0){
        //     graphics.playerz -= 5;
        // }
    }if(key_states['d']){
        graphics.playerx += 5;
        // if (graphics.playerx < 1920){
        //     graphics.playerx += 5;
        // }
    }if(key_states['a']){
        graphics.playerx -= 5;
        // if (graphics.playerx > 0){
        //     graphics.playerx -= 5;
        // }
    }if(key_states['r']){
        // if (graphics.playery > 0){
            graphics.playery -= 5;
        // }
    }if(key_states['f']){
        //if (graphics.playery < 1070){
            graphics.playery += 5;
        //}
    }if(key_states['e']){
        for (int i = 0; i < num_zombies; i++){
            zombie_vector[i].move(1);
            zombie_vector[i].render(&graphics);
        }
    }if(key_states['q']){
        for (int j = 0; j < num_zombies; j++){
            zombie_vector[j].move(-1);
            zombie_vector[j].render(&graphics);
        }
    }if(key_states['z']){
        graphics.anglex_adj -= 0.01745329 * 2;

    }if(key_states['c']){
        graphics.anglex_adj += 0.01745329 * 2;

    }if(key_states['x']){
        
    }if(key_states['/']){

    //27 - ESC key
    }if(key_states[27]){ 
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


void render_all(){
        graphics.clear_draw_screen();

        for (int i = 0; i < star_vector.size(); i++){
            star_vector[i].move(&graphics);
            star_vector[i].render(&graphics);
        }


        std::vector<std::vector<std::vector<std::vector<double>>>> floor_sphere_points_3D = graphics.find_triangle_points_sphere(graphics.floor_sphere_points_3D);
        std::vector<std::vector<std::vector<std::vector<int>>>> floor_sphere_points_2D = graphics.compute_2D_triangles(floor_sphere_points_3D);


        //std::vector<std::vector<std::vector<std::vector<int>>>> floor_points_2D = graphics.compute_2D_lines(graphics.floor_points_3D);


        graphics.set_color(1.0f, 1.0f, 1.0f);

        graphics.draw_full_triangles_sphere(floor_sphere_points_2D);

        graphics.set_color(1.0f, 0.0f, 0.0f);

        graphics.draw_hollow_triangles_sphere(floor_sphere_points_2D);


        //graphics.draw_floor_lines(floor_points_2D);




        // std::vector<std::vector<std::vector<std::vector<double>>>> test_points_3D = graphics.find_triangle_points_sphere(graphics.test_points_3D[0][0]);
        // std::vector<std::vector<std::vector<std::vector<int>>>> test_points_2D = graphics.compute_2D_triangles(test_points_3D);


        //std::vector<std::vector<std::vector<std::vector<int>>>> floor_points_2D = graphics.compute_2D_lines(graphics.floor_points_3D);




        // graphics.set_color(1.0f, 1.0f, 1.0f);

        // graphics.draw_full_triangles_sphere(test_points_2D);

        // graphics.set_color(1.0f, 0.0f, 0.0f);

        // graphics.draw_hollow_triangles_sphere(test_points_2D);





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

        // for (double i = 0; i < num_zombies; i++){
        //     zombie_vector[i].render(&graphics);
        // }

        graphics.set_color(1.0f, 1.0f, 1.0f);

        for (int i = 0; i < arrow_vector.size(); i++){
            arrow_vector[i].move(&graphics);
            arrow_vector[i].render(&graphics);
            if (arrow_vector[i].y >= 1070){
                arrow_vector.erase(arrow_vector.begin() + i);
            }
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

    // Set up orthographic projection //gpt
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, window_width, window_height, 0); // Map OpenGL coordinates to screen pixels

    // Main loop flag
    bool isRunning = true;

    // Event handler
    //SDL_Event event;

    // Create a random device (seed source) //gpt
    std::random_device rd;

    // Initialize a random number generator (Mersenne Twister) //gpt
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distribx(460, 1460);
    std::uniform_int_distribution<> distribz(500, 5000);
    std::uniform_int_distribution<> distribs(1, 15);

    int random_numx = distribx(gen);
    int random_numz = distribz(gen);
    int random_nums = distribs(gen);

    //num_zombies = 100;
     num_zombies = 50;
    //num_zombies = 25;

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
    std::uniform_int_distribution<> distrib_starx(-25000, 25000);
    int random_star_numx = distrib_starx(gen);

    std::uniform_int_distribution<> distrib_stary(-1800, -1100);
    int random_star_numy = distrib_stary(gen);

    std::uniform_int_distribution<> distrib_starz(1000, 50000);
    int random_star_numz = distrib_starz(gen);

    int count = 1;
    while (count < 5000){
        random_star_numx = distrib_starx(gen);
        random_star_numy = distrib_stary(gen);
        random_star_numz = distrib_starz(gen);
        star_vector.emplace_back(Star(&graphics, (double)random_star_numx, (double)random_star_numy, (double)random_star_numz, -2000, -1000));
        count++;
    }

    
    // Register the keyboard input callback
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    //glutKeyboardFunc(keyboard);
    //glutIdleFunc(keyboard);

    // Register the mouse callback function
    glutMouseFunc(mouse_click);

    // Check keyboard input constantly
    glutIdleFunc(key_press_check);

    // Register the display function.
    glutDisplayFunc(render_all);

    glutMainLoop();

    return 0;
}



//FIXX:
// -distance-based render of objects so far away objects not in front of close ones
// -make horizon physical line at end of grid
// -make bow
// -make arrows more detailed visually
// -make world spherical
// -make arm movement better
// -review floor angle code vs zombei angle code (zombei angle code being gpt)

// -refine zombei leg movement animation
// -fix hollow portions of zombei heads