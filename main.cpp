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
#include "Bullet.h"
#include "Graphics.h"
#include "Star.h"
#include "World.h"

Graphics graphics;

int window_width = 1920;
int window_height = 1080;

bool first_mouse_move = true;
int last_mouse_movex = int(window_width / 2);
int last_mouse_movey = int(window_height / 2);

bool key_states[256] = { false };

int num_zombies;
std::vector<Zombie> zombie_vector;
std::vector<Bullet> bullet_vector;
std::vector<Star> star_vector;
std::vector<World> world_vector;

std::vector<std::vector<double>> starscape_base_points_3D;
std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> starscape_base_triangle_points_3D;


//int player_speed = 10;
int player_speed = 10;


void keyDown(unsigned char key, int idk1, int idk2) {
    key_states[key] = true;
}


void keyUp(unsigned char key, int idk1, int idk2){
    key_states[key] = false;
}


// Keyboard press check
void key_press_check() {
    if(key_states['w']){
        graphics.playerz += player_speed;

    }if(key_states['s']){
        graphics.playerz -= player_speed;

    }if(key_states['d']){
        graphics.playerx += player_speed;

    }if(key_states['a']){
        graphics.playerx -= player_speed;

    }if(key_states['r']){
        graphics.playery -= player_speed;

    }if(key_states['f']){
        graphics.playery += player_speed;

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
        graphics.anglex_diff -= 0.01745329 * 2;

    }if(key_states['c']){
        graphics.anglex_diff += 0.01745329 * 2;

    }if(key_states['t']){
        graphics.angley_diff += 0.01745329 * 2;

    }if(key_states['g']){
        graphics.angley_diff -= 0.01745329 * 2;
        
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
                bullet_vector.emplace_back(Bullet(&graphics, x, y));
                break;
            case GLUT_RIGHT_BUTTON:
                break;
            case GLUT_MIDDLE_BUTTON:
                break;
        }
    }
}

void mouse_move(int x, int y){

    if (first_mouse_move){
        last_mouse_movex = x;
        last_mouse_movey = y;
        first_mouse_move = false;
    }
    
    int mouse_diffx = x - last_mouse_movex;
    int mouse_diffy = last_mouse_movey - y;

    last_mouse_movex = x;
    last_mouse_movey = y;

    double sensitivity = 1.0;

    graphics.anglex_diff = graphics.anglex_diff + mouse_diffx * sensitivity * 0.001;
    graphics.angley_diff = graphics.angley_diff + mouse_diffy * sensitivity * 0.001;

    if (x > window_width || x < 100 || y > window_height || y < 100){
        glutWarpPointer(window_width / 2, window_height / 2);
        first_mouse_move = true;
    }
    
}

void mouse_enter_leave_window(int state){

    if (state == GLUT_LEFT){
        glutWarpPointer(window_width / 2, window_height / 2);
        first_mouse_move = true;
    }
}

void render_all(){

        graphics.clear_draw_screen();

        for (int i = 0; i < world_vector.size(); i++){
            world_vector[i].render(&graphics);
        }

        for (int i = 0; i < star_vector.size(); i++){
            star_vector[i].move(&graphics);
            star_vector[i].render(&graphics);
        }        


        int zombie_to_remove = -1;
        int bullet_to_remove = -1;
    

        // Check for collision for all bullets hitting all zombeis
        for (int i = 0; i < bullet_vector.size(); i++){

            for (double j = 0; j < num_zombies; j++){
                if (zombie_vector[j].box_points_3D_body[0][0] <= bullet_vector[i].x &&
                        zombie_vector[j].box_points_3D_body[1][0] >= bullet_vector[i].x &&
                        zombie_vector[j].box_points_3D_body[0][1] <= bullet_vector[i].y &&
                        zombie_vector[j].box_points_3D_body[2][1] >= bullet_vector[i].y &&
                        zombie_vector[j].box_points_3D_body[0][2] >= bullet_vector[i].z &&
                        zombie_vector[j].box_points_3D_body[4][2] <= bullet_vector[i].z){

                    zombie_to_remove = j;
                    bullet_to_remove = i;
                    break;
                }
            }

            if (zombie_to_remove != -1){
                
                zombie_vector.erase(zombie_vector.begin() + zombie_to_remove);
                bullet_vector.erase(bullet_vector.begin() + bullet_to_remove);
                num_zombies--;
                zombie_to_remove = -1;
                bullet_to_remove = -1;
            }   

        }

        for (double i = 0; i < num_zombies; i++){
            zombie_vector[i].gravitate(world_vector[0]);
            zombie_vector[i].render(&graphics);
        }


        for (int i = 0; i < bullet_vector.size(); i++){
            bullet_vector[i].move(&graphics);
            bullet_vector[i].render(&graphics);
            // Bullet hits floor
            // if (bullet_vector[i].y >= 1070){
            //     bullet_vector.erase(bullet_vector.begin() + i);
            // }
        }


        glutPostRedisplay();
        graphics.present_frame();

}


int main(int argc, char* argv[]) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("ZOMBEIS");

    glutSetCursor(GLUT_CURSOR_NONE);
    glutPassiveMotionFunc(mouse_move);
    glutWarpPointer(window_width / 2, window_height / 2);
    glutEntryFunc(mouse_enter_leave_window);

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


    // Making worlds
    world_vector.emplace_back(World(&graphics, 960, 1060 + 1100, 1000 + 500, {1, 0, 0}));
    // world_vector.emplace_back(World(&graphics, 960, 1060 + 1100, 1000 + 500));
    // world_vector.emplace_back(World(&graphics, 960 - 5000, 1060 + 1100 - 3000, 1000 + 500 + 10000));
    // world_vector.emplace_back(World(&graphics, 960 + 7000, 1060 + 1100 + 1000, 1000 + 500 + 20000));
    // world_vector.emplace_back(World(&graphics, 960 + 9000, 1060 + 1100 - 2000, 1000 + 500 + 30000));
    // world_vector.emplace_back(World(&graphics, 960 + 6000, 1060 + 1100 + 8000, 1000 + 500 + 40000));


    // Making worlds
    // std::uniform_int_distribution<> distrib_worldx(-10000, 10000);
    // int random_world_numx = distrib_worldx(gen);

    // std::uniform_int_distribution<> distrib_worldy(-2500, 2500);
    // int random_world_numy = distrib_worldy(gen);

    // std::uniform_int_distribution<> distrib_worldz(1000, 50000);
    // int random_world_numz = distrib_worldz(gen);


    // std::uniform_int_distribution<> distrib_world_colorr(0, 10);
    // float random_world_colorr = distrib_world_colorr(gen);

    // std::uniform_int_distribution<> distrib_world_colorg(0, 10);
    // float random_world_colorg = distrib_world_colorg(gen);

    // std::uniform_int_distribution<> distrib_world_colorb(0, 10);
    // float random_world_colorb = distrib_world_colorb(gen);

    // std::uniform_int_distribution<> distrib_world_color(0, 10);
    // float random_world_color = distrib_world_color(gen);


    // int num_worlds = 0;
    // while (num_worlds < 25){
    //     random_world_numx = distrib_worldx(gen);
    //     random_world_numy = distrib_worldy(gen);
    //     random_world_numz = distrib_worldz(gen);

    //     random_world_colorr = distrib_world_colorr(gen);
    //     random_world_colorg = distrib_world_colorg(gen);
    //     random_world_colorb = distrib_world_colorb(gen);
    //     random_world_color = distrib_world_color(gen);

    //     std::vector<float> surface_color = {(float)random_world_colorr, (float)random_world_colorg, (float)random_world_colorb};

    //     // std::vector<float> surface_color;
    //     // if (random_world_color > 3){
    //     //     surface_color = {1, 1, 1};
    //     // } else{
    //     //     surface_color = {0, 0, 1};
    //     // }

    //     world_vector.emplace_back(World(&graphics, 960 + random_world_numx, 1060 + 1100 + random_world_numy, 1000 + 500 + random_world_numz, surface_color));
    //     num_worlds++;
    // }




    // Making zombeis
    std::uniform_int_distribution<> distribx(460, 1460);
    std::uniform_int_distribution<> distribz(500, 5000);
    std::uniform_int_distribution<> distribs(1, 15);

    int random_numx = distribx(gen);
    int random_numz = distribz(gen);
    int random_nums = distribs(gen);

    //num_zombies = 100;
    //num_zombies = 50;
    //num_zombies = 25;
    num_zombies = 0;

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
    // std::uniform_int_distribution<> distrib_starx(-25000, 25000);
    // int random_star_numx = distrib_starx(gen);

    // std::uniform_int_distribution<> distrib_stary(-1800, -1100);
    // int random_star_numy = distrib_stary(gen);

    // std::uniform_int_distribution<> distrib_starz(1000, 50000);
    // int random_star_numz = distrib_starz(gen);

    // int num_stars = 1;
    // //while (num_stars < 5000){
    // while (num_stars < 1000){
    //     random_star_numx = distrib_starx(gen);
    //     random_star_numy = distrib_stary(gen);
    //     random_star_numz = distrib_starz(gen);
    //     star_vector.emplace_back(Star(&graphics, (double)random_star_numx, (double)random_star_numy, (double)random_star_numz, -2000, -1000));
    //     num_stars++;
    // }




    // Making starscape

    starscape_base_points_3D = graphics.make_sphere({(double)graphics.playerx, (double)graphics.playery, (double)graphics.playerz}, 10000, 12);
    starscape_base_triangle_points_3D = graphics.find_triangle_points_sphere(starscape_base_points_3D);

    for (int i = 0; i < starscape_base_triangle_points_3D.size(); i++){
        for (int j = 0; j < starscape_base_triangle_points_3D[i].size(); j++){
            for (int k = 0; k < starscape_base_triangle_points_3D[i][j].size(); k++){

                std::uniform_int_distribution<> distrib_starx(starscape_base_triangle_points_3D[i][j][k][0][0], starscape_base_triangle_points_3D[i][j][k][1][0]);
                std::uniform_int_distribution<> distrib_stary(starscape_base_triangle_points_3D[i][j][k][0][1], starscape_base_triangle_points_3D[i][j][k][2][1]);
                std::uniform_int_distribution<> distrib_starz(starscape_base_triangle_points_3D[i][j][k][0][2], starscape_base_triangle_points_3D[i][j][k][2][2]);

                int num_stars = 1;
                //while (num_stars < 5000){
                while (num_stars < 5){
                    int random_star_numx = distrib_starx(gen);
                    int random_star_numy = distrib_stary(gen);
                    int random_star_numz = distrib_starz(gen);
                    star_vector.emplace_back(Star(&graphics, (double)random_star_numx, (double)random_star_numy, (double)random_star_numz, random_star_numy + 100, random_star_numy - 100));
                    num_stars++;
                }
                
            }
        }
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
// -make bow
// -make bullets more detailed visually?
// -make arm movement better
// -review floor angle code vs zombei angle code (zombei angle code being gpt)
// -refine zombei leg movement animation
// -comment graphics.find_floor_lines_on_globe
// -clean up compute_2D_point assuming second quadrant and having positive x values for negative x