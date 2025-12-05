#include <GL/glut.h>
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

#include <random>

#include "main.h"
#include "Zombei.h"
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

int mousex;
int mousey;


bool key_states[256] = { false };

int num_zombeis;
std::vector<Zombei> zombei_vector;
std::vector<Bullet> bullet_vector;
std::vector<Star> star_vector;
std::vector<World> world_vector;

std::vector<std::vector<double>> starscape_base_points_3D;
std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> starscape_base_triangle_points_3D;

std::vector<std::vector<double>> test_box;


int player_speed = 1;


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
        for (int i = 0; i < num_zombeis; i++){
            zombei_vector[i].move(1);
            zombei_vector[i].render(&graphics);
        }

    }if(key_states['q']){
        for (int j = 0; j < num_zombeis; j++){
            zombei_vector[j].move(-1);
            zombei_vector[j].render(&graphics);
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

void track_mouse_move(int x, int y){

    mousex = x;
    mousey = y;
    
}


void mouse_move_check(){

    if (!first_mouse_move){

        glutWarpPointer(window_width / 2, window_height / 2);

        int mouse_diffx = mousex - window_width / 2;
        int mouse_diffy = window_height / 2 - mousey;

        double sensitivity = 1.0;

        graphics.anglex_diff = graphics.anglex_diff + mouse_diffx * sensitivity * 0.001;
        graphics.angley_diff = graphics.angley_diff + mouse_diffy * sensitivity * 0.001;

    }else{
        first_mouse_move = false;
    }

}


void check_keys_and_mouse(){

    key_press_check();
    mouse_move_check();

}


void render_all(){

        graphics.clear_draw_screen();

        for (int i = 0; i < star_vector.size(); i++){
            star_vector[i].move(&graphics);
            star_vector[i].render(&graphics);
        }   

        for (int i = 0; i < world_vector.size(); i++){
            world_vector[i].render(&graphics);
        }


        int zombei_to_remove = -1;
        int bullet_to_remove = -1;
    

        // Check for collision for all bullets hitting all zombeis
        for (int i = 0; i < bullet_vector.size(); i++){

            for (double j = 0; j < num_zombeis; j++){
                if (zombei_vector[j].box_points_3D_body[0][0] <= bullet_vector[i].x &&
                        zombei_vector[j].box_points_3D_body[1][0] >= bullet_vector[i].x &&
                        zombei_vector[j].box_points_3D_body[0][1] <= bullet_vector[i].y &&
                        zombei_vector[j].box_points_3D_body[2][1] >= bullet_vector[i].y &&
                        zombei_vector[j].box_points_3D_body[0][2] >= bullet_vector[i].z &&
                        zombei_vector[j].box_points_3D_body[4][2] <= bullet_vector[i].z){

                    zombei_to_remove = j;
                    bullet_to_remove = i;
                    break;
                }
            }

            if (zombei_to_remove != -1){
                
                zombei_vector.erase(zombei_vector.begin() + zombei_to_remove);
                bullet_vector.erase(bullet_vector.begin() + bullet_to_remove);
                num_zombeis--;
                zombei_to_remove = -1;
                bullet_to_remove = -1;
            }   

        }

        for (int i = 0; i < num_zombeis; i++){
            zombei_vector[i].gravitate(world_vector[0]);
            zombei_vector[i].render(&graphics);
        }


        for (int i = 0; i < bullet_vector.size(); i++){
            bullet_vector[i].move(&graphics);
            bullet_vector[i].render(&graphics);
            // Bullet hits floor
            // if (bullet_vector[i].y >= 1070){
            //     bullet_vector.erase(bullet_vector.begin() + i);
            // }
        }


        std::vector<std::vector<std::vector<double>>> clipped_box_points_3D = graphics.clip_box(test_box);
        std::vector<std::vector<std::vector<int>>> clipped_box_points_2D = graphics.compute_2D_box_as_lines(clipped_box_points_3D);
        graphics.set_color(0, 0, 0);
        graphics.draw_full_box_as_lines(clipped_box_points_2D);

        graphics.set_color(1, 1, 1);
        graphics.draw_hollow_box_as_lines(clipped_box_points_2D);


        glutPostRedisplay();
        graphics.present_frame();

}


int main(int argc, char* argv[]) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("ZOMBEIS");

    glutSetCursor(GLUT_CURSOR_NONE);
    glutWarpPointer(window_width / 2, window_height / 2);
    //glutEntryFunc(mouse_enter_leave_window);

    glLoadIdentity();
    gluOrtho2D(0, window_width, window_height, 0); // Map OpenGL coordinates to screen pixels


    // Register the keyboard input callback
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    //glutKeyboardFunc(keyboard);
    //glutIdleFunc(keyboard);

    // Register the mouse callback function
    glutMouseFunc(mouse_click);

    glutPassiveMotionFunc(track_mouse_move);
    glutMotionFunc(track_mouse_move);

    // Check keyboard input constantly
    glutIdleFunc(check_keys_and_mouse);

    // Register the display function.
    glutDisplayFunc(render_all);

    

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

    //num_zombeis = 100;
    //num_zombeis = 50;
    //num_zombeis = 25;
    num_zombeis = 0;

    for (int i = 0; i < num_zombeis; i++){
        random_numx = distribx(gen);
        random_numz = distribz(gen);
        zombei_vector.emplace_back(Zombei(&graphics, random_numx, 1064, random_numz));
        zombei_vector[i].render(&graphics);
    }

    // Randomly setting speed for zombeis.
    for (int i = 0; i < num_zombeis; i++){
        random_nums = distribs(gen);
        zombei_vector[i].speed = random_nums;
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




    // Making icosahedron starscape

    starscape_base_points_3D = graphics.make_sphere({(double)graphics.playerx, (double)graphics.playery, (double)graphics.playerz}, 10000, 12);
    starscape_base_triangle_points_3D = graphics.find_triangle_points_sphere(starscape_base_points_3D);

    for (int i = 0; i < starscape_base_triangle_points_3D.size(); i++){
        for (int j = 0; j < starscape_base_triangle_points_3D[i].size(); j++){
            for (int k = 0; k < starscape_base_triangle_points_3D[i][j].size(); k++){

                int minx = starscape_base_triangle_points_3D[i][j][k][0][0];
                int maxx = starscape_base_triangle_points_3D[i][j][k][1][0];

                if (minx > maxx) std::swap(minx, maxx);


                int miny = starscape_base_triangle_points_3D[i][j][k][0][1];
                int maxy = starscape_base_triangle_points_3D[i][j][k][2][1];

                if (miny > maxy) std::swap(miny, maxy);


                int minz = starscape_base_triangle_points_3D[i][j][k][0][2];
                int maxz = starscape_base_triangle_points_3D[i][j][k][2][2];

                if (minz > maxz) std::swap(minz, maxz);


                std::uniform_int_distribution<> distrib_starx(minx, maxx);
                std::uniform_int_distribution<> distrib_stary(miny, maxy);
                std::uniform_int_distribution<> distrib_starz(minz, maxz);

                int num_stars = 1;
                //while (num_stars < 5000){
                while (num_stars < 2){
                    int random_star_numx = distrib_starx(gen);
                    int random_star_numy = distrib_stary(gen);
                    int random_star_numz = distrib_starz(gen);
                    star_vector.emplace_back(Star(&graphics, (double)random_star_numx, (double)random_star_numy, (double)random_star_numz, random_star_numy + 100, random_star_numy - 100));
                    num_stars++;
                }
                
            }
        }
    }


    test_box = graphics.make_box(std::vector<double>{960, 1060, 0 + 25}, 100, 100, 100);    

    glutMainLoop();

    return 0;
}



//FIXX:
// -distance-based render of objects so far away objects not in front of close ones
// -make bow
// -make bullets more detailed visually?
// -make arm movement better
// -refine zombei leg movement animation
// -comment graphics.find_floor_lines_on_globe
// -clean up compute_2D_point assuming second quadrant and having positive x values for negative x
// -consider switching drawing to floats instead of ints
// -investigate large numbers drawing coordinates when clipping
// -fix clipping of triangle points sphere taking away everything too soon