#include <GL/glut.h>
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

#include <random>

#include "Zombie.h"
#include "Arrow.h"
#include "Graphics.h"

Graphics graphics;
int num_zombies;
std::vector<Zombie> zombie_vector;
std::vector<Arrow> arrow_vector;


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
            }
            break;
        case 'q':
            for (int j = 0; j < num_zombies; j++){
                zombie_vector[j].move(-1);
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
        case 27: //ESC key
            exit(0);
    }
}


void mouse_click(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        std::cout << "Mouse clicked at: (" << x << ", " << y << ")\n";

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
        graphics.set_color(1.0f, 0.0f, 0.0f);
        graphics.draw_horizon();

        std::vector<std::vector<std::vector<std::vector<int>>>> floor_points_2D = graphics.compute_2D_lines(graphics.floor_points_3D);
        graphics.draw_floor_lines(floor_points_2D);

        graphics.set_color(0.0f, 0.0f, 1.0f);

        for (double i = 0; i < num_zombies; i++){
            zombie_vector[i].render_zombie(&graphics);
        }

        graphics.set_color(1.0f, 1.0f, 1.0f);

        for (int i = 0; i < arrow_vector.size(); i++){
            arrow_vector[i].render_arrow(&graphics);
        }

        glutPostRedisplay();
        graphics.present_frame();

}


int main(int argc, char* argv[]) {
    
    Graphics graphics;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    // int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    // int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    int windowWidth = 1920;
    int windowHeight = 1080;
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("ZOMBEIS");

    // Set up orthographic projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, windowHeight, 0); // Map OpenGL coordinates to screen pixels

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
    std::uniform_int_distribution<> distribx(-1040, 1960);
    std::uniform_int_distribution<> distribz(500, 10000);
    std::uniform_int_distribution<> distribs(1, 15);

    int random_numx = distribx(gen);
    int random_numz = distribz(gen);
    int random_nums = distribs(gen);

    num_zombies = 100;

    for (double i = 0; i < num_zombies; i++){
        random_numx = distribx(gen);
        random_numz = distribz(gen);
        zombie_vector.emplace_back(Zombie(&graphics, random_numx, 1064, random_numz));
        zombie_vector[i].render_zombie(&graphics);
    }

    // Randomly setting speed for zombies.
    for (double i = 0; i < num_zombies; i++){
        random_nums = distribs(gen);
        zombie_vector[i].speed = random_nums;
    }



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
