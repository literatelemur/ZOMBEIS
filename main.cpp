#include <GL/glut.h>
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <random>

#include "Zombei.h"
#include "Bullet.h"
#include "Graphics.h"
#include "Star.h"
#include "World.h"
#include "Edit.h"
#include "Triangle.h"
#include "Camera.h"

Graphics graphics;
Camera camera;

int window_width = 1920;
int window_height = 1080;

bool first_mouse_move = true;
int last_mouse_movex = int(window_width / 2);
int last_mouse_movey = int(window_height / 2);

int mousex;
int mousey;

bool key_states[256] = { false };
bool prev_key_states[256] = { false };

int num_zombeis;
std::vector<Zombei> zombei_vector;
std::vector<Bullet> bullet_vector;
std::vector<Star> star_vector;
std::vector<World> world_vector;

std::vector<std::vector<double>> starscape_base_points_3D;
std::vector<Triangle> starscape_base_triangle_points_3D;

std::vector<std::vector<double>> floor_points_3D;
std::vector<Triangle> floor_triangles_3D;


double normal_player_speed = 10;
double edit_player_speed = 0.25;
double player_speed = normal_player_speed;


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
        }

    }if(key_states['q']){
        for (int j = 0; j < num_zombeis; j++){
            zombei_vector[j].move(-1);
        }

    }if(key_states['z']){
        graphics.anglex_diff -= 0.01745329 * 2;

    }if(key_states['c']){
        graphics.anglex_diff += 0.01745329 * 2;

    }if(key_states['t']){
        graphics.angley_diff += 0.01745329 * 2;

    }if(key_states['g']){
        graphics.angley_diff -= 0.01745329 * 2;
        
    }if(key_states['x'] && !prev_key_states['x']){
        Edit::toggle_edit_mode();
        if (Edit::edit_mode) player_speed = edit_player_speed;
        else player_speed = normal_player_speed;

    }if(Edit::edit_mode){        
    
        if(key_states['='] && !prev_key_states['=']){
            Edit::points_3D.emplace_back(std::vector<double>{graphics.playerx, graphics.playery, graphics.playerz + 10});
            Edit::points_3D_main_index = Edit::points_3D.size() - 1;
            Edit::points_points_3D.emplace_back(graphics.make_sphere({graphics.playerx, graphics.playery, graphics.playerz + 10}, 0.25, 12));

        }if(key_states['-'] && !prev_key_states['-']){
            Edit::points_3D.pop_back();
            Edit::points_3D_main_index--;
            Edit::points_3D_sub1_index--;
            Edit::points_3D_sub2_index--;
            Edit::points_points_3D.pop_back();


        }if(key_states['i']){
            Edit::move_point(1, -1);

        }if(key_states['k']){
            Edit::move_point(1, 1);

        }if(key_states['j']){
            Edit::move_point(0, -1);

        }if(key_states['l']){
            Edit::move_point(0, 1);

        }if(key_states['u']){
            Edit::move_point(2, -1);

        }if(key_states['o']){
            Edit::move_point(2, 1);

        }if (Edit::points_3D.size() > 0){
            if(key_states[','] && !prev_key_states[',']){
                Edit::points_3D_main_index--;
                for (int i = 0; i < 3; i++){
                    if (Edit::points_3D_main_index == Edit::points_3D_sub1_index || Edit::points_3D_main_index == Edit::points_3D_sub2_index) Edit::points_3D_main_index--;
                    if (Edit::points_3D_main_index == -1) Edit::points_3D_main_index = Edit::points_3D.size() - 1;
                }

            }if(key_states['.'] && !prev_key_states['.']){
                Edit::points_3D_main_index++;
                for (int i = 0; i < 3; i++){
                    if (Edit::points_3D_main_index == Edit::points_3D_sub1_index || Edit::points_3D_main_index == Edit::points_3D_sub2_index) Edit::points_3D_main_index++;
                    if (Edit::points_3D_main_index == Edit::points_3D.size()) Edit::points_3D_main_index = 0;
                }

            }if(key_states[';'] && !prev_key_states[';']){
                Edit::points_3D_sub1_index--;
                for (int i = 0; i < 3; i++){
                    if (Edit::points_3D_sub1_index == Edit::points_3D_main_index || Edit::points_3D_sub1_index == Edit::points_3D_sub2_index) Edit::points_3D_sub1_index--;
                    if (Edit::points_3D_sub1_index == -1) Edit::points_3D_sub1_index = Edit::points_3D.size() - 1;
                }

            }if(key_states['\''] && !prev_key_states['\'']){
                Edit::points_3D_sub1_index++;
                for (int i = 0; i < 3; i++){
                    if (Edit::points_3D_sub1_index == Edit::points_3D_main_index || Edit::points_3D_sub1_index == Edit::points_3D_sub2_index) Edit::points_3D_sub1_index++;
                    if (Edit::points_3D_sub1_index == Edit::points_3D.size()) Edit::points_3D_sub1_index = 0;
                }

            }if(key_states['['] && !prev_key_states['[']){
                Edit::points_3D_sub2_index--;
                for (int i = 0; i < 3; i++){
                    if (Edit::points_3D_sub2_index == Edit::points_3D_main_index || Edit::points_3D_sub2_index == Edit::points_3D_sub1_index) Edit::points_3D_sub2_index--;
                    if (Edit::points_3D_sub2_index == -1) Edit::points_3D_sub2_index = Edit::points_3D.size() - 1;
                }

            }if(key_states[']'] && !prev_key_states[']']){
                Edit::points_3D_sub2_index++;
                for (int i = 0; i < 3; i++){
                    if (Edit::points_3D_sub2_index == Edit::points_3D_main_index || Edit::points_3D_sub2_index == Edit::points_3D_sub1_index) Edit::points_3D_sub2_index++;
                    if (Edit::points_3D_sub2_index == Edit::points_3D.size()) Edit::points_3D_sub2_index = 0;
                }

            }if(key_states['m'] && !prev_key_states['m']){
                if (Edit::edit_draw_points) Edit::edit_draw_points = false;
                else Edit::edit_draw_points = true;
            }
        }if (Edit::points_3D.size() > 2 && Edit::points_3D_main_index > -1 && Edit::points_3D_sub1_index > -1 && Edit::points_3D_sub2_index > -1){
            if(key_states['/'] && !prev_key_states['/']) Edit::triangles_3D.emplace_back(Triangle(&graphics, Edit::points_3D[Edit::points_3D_main_index], Edit::points_3D[Edit::points_3D_sub1_index], Edit::points_3D[Edit::points_3D_sub2_index], "both", {0, 0, 0}, {1, 0, 0}, 0));

        }

    //27 - ESC key
    }if(key_states[27]){ 
        exit(0);
    }

    std::copy(std::begin(key_states), std::end(key_states), std::begin(prev_key_states));
}


void mouse_click(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        //std::cout << "Mouse clicked at: (" << x << ", " << y << ")\n";

        // Check which button was pressed
        switch (button) {
            case GLUT_LEFT_BUTTON:
                if (!Edit::edit_mode) bullet_vector.emplace_back(Bullet(&graphics, x, y));
                else {
                    Edit::edit_click_mouse_button = "left";
                    Edit::click_point(&graphics);
                }
                break;
            case GLUT_RIGHT_BUTTON:
                if (Edit::edit_mode) {
                    Edit::edit_click_mouse_button = "right";
                    Edit::click_point(&graphics);
                }
                break;
            case GLUT_MIDDLE_BUTTON:
                if (Edit::edit_mode) {
                    Edit::edit_click_mouse_button = "middle";
                    Edit::click_point(&graphics);
                }
                break;
        }

    } else if(state == GLUT_UP){

        if (Edit::edit_mode) Edit::edit_click_mouse_button = "none";
    }
}


void track_mouse_move(int x, int y){

    mousex = x;
    mousey = y;
    
}


void mouse_move_check(){

    if (!first_mouse_move){

        glutWarpPointer(window_width / 2, window_height / 2);

        int mouse_diffx = window_width / 2 - mousex;
        int mouse_diffy = window_height / 2 - mousey;

        double sensitivity = 1.0;

        graphics.anglex_diff = graphics.anglex_diff - mouse_diffx * sensitivity * 0.001;
        graphics.angley_diff = graphics.angley_diff - mouse_diffy * sensitivity * 0.001;


        // Moving edit mode points with mouse movement and mouse button clicked.
        if (Edit::edit_click_mouse_button != "none") {

            Edit::move_point_with_mouse(&graphics);
            Edit::first_click_move = false;
        }else Edit::first_click_move = true;

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

    std::vector<Triangle> all_triangles;

    for (int i = 0; i < floor_triangles_3D.size(); i++){
        all_triangles.emplace_back(floor_triangles_3D[i]);
    }

    for (int i = 0; i < star_vector.size(); i++){
        star_vector[i].find_movement_value(&graphics);
        star_vector[i].box_triangles_3D = graphics.find_triangles_box(star_vector[i].box_points_3D, "both", {0, 0, 0}, {1, 1, 1}, 0);

        for (int j = 0; j < star_vector[i].box_triangles_3D.size(); j++){
            all_triangles.emplace_back(star_vector[i].box_triangles_3D[j]);
        }
    }   

    for (int i = 0; i < world_vector.size(); i++){
        world_vector[i].sphere_triangles_3D = graphics.find_triangles_sphere(world_vector[i].sphere_points_3D, "both", {0, 0, 0}, world_vector[i].surface_color, 10);

        for (int j = 0; j < world_vector[i].sphere_triangles_3D.size(); j++){
            all_triangles.emplace_back(world_vector[i].sphere_triangles_3D[j]);
        }
    }

    


    for (int i = 0; i < zombei_vector.size(); i++){

        zombei_vector[i].sphere_triangles_3D_head = graphics.find_triangles_sphere(zombei_vector[i].sphere_points_3D_head, "both", {0, 0, 1}, {0, 0, 0}, 0);

        for (int j = 0; j < zombei_vector[i].sphere_triangles_3D_head.size(); j++){
            all_triangles.emplace_back(zombei_vector[i].sphere_triangles_3D_head[j]);
        }

        zombei_vector[i].box_triangles_3D_body = graphics.find_triangles_box(zombei_vector[i].box_points_3D_body, "both", {0, 0, 0}, {0, 0, 1}, 0);

        for (int j = 0; j < zombei_vector[i].box_triangles_3D_body.size(); j++){
            all_triangles.emplace_back(zombei_vector[i].box_triangles_3D_body[j]);
        }

        zombei_vector[i].box_triangles_3D_arm1 = graphics.find_triangles_box(zombei_vector[i].box_points_3D_arm1, "both", {0, 0, 0}, {0, 0, 1}, 0);

        for (int j = 0; j < zombei_vector[i].box_triangles_3D_arm1.size(); j++){
            all_triangles.emplace_back(zombei_vector[i].box_triangles_3D_arm1[j]);
        }

        zombei_vector[i].box_triangles_3D_arm2 = graphics.find_triangles_box(zombei_vector[i].box_points_3D_arm2, "both", {0, 0, 0}, {0, 0, 1}, 0);

        for (int j = 0; j < zombei_vector[i].box_triangles_3D_arm2.size(); j++){
            all_triangles.emplace_back(zombei_vector[i].box_triangles_3D_arm2[j]);
        }

        zombei_vector[i].box_triangles_3D_leg1 = graphics.find_triangles_box(zombei_vector[i].box_points_3D_leg1, "both", {0, 0, 0}, {0, 0, 1}, 0);

        for (int j = 0; j < zombei_vector[i].box_triangles_3D_leg1.size(); j++){
            all_triangles.emplace_back(zombei_vector[i].box_triangles_3D_leg1[j]);
        }

        zombei_vector[i].box_triangles_3D_leg2 = graphics.find_triangles_box(zombei_vector[i].box_points_3D_leg2, "both", {0, 0, 0}, {0, 0, 1}, 0);

        for (int j = 0; j < zombei_vector[i].box_triangles_3D_leg2.size(); j++){
            all_triangles.emplace_back(zombei_vector[i].box_triangles_3D_leg2[j]);
        }
    }


    for (int i = 0; i < bullet_vector.size(); i++){
        bullet_vector[i].box_triangles_3D = graphics.find_triangles_box(bullet_vector[i].box_points_3D, "both", {1, 1, 1}, {0, 0, 0}, 0);

        for (int j = 0; j < bullet_vector[i].box_triangles_3D.size(); j++){
            all_triangles.emplace_back(bullet_vector[i].box_triangles_3D[j]);
        }
    }


    if (Edit::edit_mode){

        if (Edit::edit_draw_points){
            for (int i = 0; i < Edit::points_points_3D.size(); i++){

                std::vector<Triangle> edit_point_triangles_3D;

                if (i == Edit::points_3D_main_index) edit_point_triangles_3D = graphics.find_triangles_sphere(Edit::points_points_3D[i], "both", {1, 1, 1}, {1, 0, 0}, 0);
                else if (i == Edit::points_3D_sub1_index || i == Edit::points_3D_sub2_index) edit_point_triangles_3D = graphics.find_triangles_sphere(Edit::points_points_3D[i], "both", {1, 0, 0}, {0, 0, 0}, 0);
                else edit_point_triangles_3D = graphics.find_triangles_sphere(Edit::points_points_3D[i], "both", {0, 0, 0}, {1, 1, 1}, 0);

                for (int j = 0; j < edit_point_triangles_3D.size(); j++){
                    all_triangles.emplace_back(edit_point_triangles_3D[j]);
                }
            }
        }

        for (int i = 0; i < Edit::triangles_3D.size(); i++) all_triangles.emplace_back(Edit::triangles_3D[i]);
    }


    std::vector<Triangle> ordered_all_triangles = graphics.order_triangles(all_triangles);
    graphics.store_all_triangles(ordered_all_triangles);
    graphics.find_lines_on_triangles();
    std::vector<std::vector<std::vector<double>>> rot_triangles_points = graphics.rotate_triangles();
    std::vector<std::vector<std::vector<std::vector<double>>>> clipped_rot_triangles_3D_as_lines = graphics.clip_triangles();
    std::vector<std::vector<std::vector<std::vector<double>>>> clipped_rot_triangles_2D_as_lines = graphics.compute_2D_triangles_as_lines(clipped_rot_triangles_3D_as_lines);
    graphics.draw_triangles_as_lines(clipped_rot_triangles_2D_as_lines);






    int zombei_to_remove = -1;
    int bullet_to_remove = -1;


    // Check for collision of all bullets hitting all zombeis
    // for (int i = 0; i < bullet_vector.size(); i++){

    //     for (double j = 0; j < num_zombeis; j++){
    //         if (zombei_vector[j].box_points_3D_body[0][0] <= bullet_vector[i].origin_x &&
    //                 zombei_vector[j].box_points_3D_body[1][0] >= bullet_vector[i].origin_x &&
    //                 zombei_vector[j].box_points_3D_body[0][1] <= bullet_vector[i].origin_y &&
    //                 zombei_vector[j].box_points_3D_body[2][1] >= bullet_vector[i].origin_y &&
    //                 zombei_vector[j].box_points_3D_body[0][2] >= bullet_vector[i].origin_z &&
    //                 zombei_vector[j].box_points_3D_body[4][2] <= bullet_vector[i].origin_z){

    //             zombei_to_remove = j;
    //             bullet_to_remove = i;
    //             break;
    //         }
    //     }

    //     if (zombei_to_remove != -1){
            
    //         zombei_vector.erase(zombei_vector.begin() + zombei_to_remove);
    //         bullet_vector.erase(bullet_vector.begin() + bullet_to_remove);
    //         num_zombeis--;
    //         zombei_to_remove = -1;
    //         bullet_to_remove = -1;
    //     }   

    // }




    // for (int i = 0; i < num_zombeis; i++){
    //     zombei_vector[i].gravitate(world_vector[0]);
    // }


    for (int i = 0; i < bullet_vector.size(); i++){
        bullet_vector[i].move(&graphics);
    }

    for (int i = 0; i < star_vector.size(); i++){
        star_vector[i].find_movement_value(&graphics);
        star_vector[i].move(&graphics);
    }

    graphics.set_color(1, 1, 1);
    graphics.draw_hud();


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


    // Making floor
    floor_points_3D = graphics.make_sphere({(double)960, (double)1060 + 20, (double)1000 + 10000}, 10000, 3);
    floor_triangles_3D = graphics.find_triangles_sphere(floor_points_3D, "both", {0, 0, 0}, {0, 1, 0}, 1.25);


    // Making worlds
    // world_vector.emplace_back(World(&graphics, 960, 1060 + 1100, 1000 + 500, {1, 0, 0}));
    // world_vector.emplace_back(World(&graphics, 960 - 5000, 1060 + 1100 - 3000, 1000 + 500 + 10000, {1, 0, 0}));
    // world_vector.emplace_back(World(&graphics, 960 + 7000, 1060 + 1100 + 1000, 1000 + 500 + 20000, {1, 0, 0}));
    // world_vector.emplace_back(World(&graphics, 960 + 9000, 1060 + 1100 - 2000, 1000 + 500 + 30000, {1, 0, 0}));
    // world_vector.emplace_back(World(&graphics, 960 + 6000, 1060 + 1100 + 8000, 1000 + 500 + 40000, {1, 0, 0}));

    world_vector.emplace_back(World(&graphics, 960 - 5000, 1060 + 1100 - 3000, 1000 + 500 + 10000, {1, 0, 0}));
    world_vector.emplace_back(World(&graphics, 960 + 7000, 1060 + 1100 - 9000, 1000 + 500 + 20000, {1, 0, 0}));
    world_vector.emplace_back(World(&graphics, 960 + 9000, 1060 + 1100 - 2000, 1000 + 500 + 30000, {1, 0, 0}));
    world_vector.emplace_back(World(&graphics, 960 + 6000, 1060 + 1100 - 8000, 1000 + 500 + 40000, {1, 0, 0}));
    world_vector.emplace_back(World(&graphics, 960 - 2500, 1060 + 1100 - 5000, 1000 + 500 + 50000, {1, 0, 0}));
    // world_vector.emplace_back(World(&graphics, 960 + 7000, 1060 + 1100 - 9000, 1000 + 500 + 20000, {1, 0, 0}));
    // world_vector.emplace_back(World(&graphics, 960 + 9000, 1060 + 1100 - 2000, 1000 + 500 + 30000, {1, 0, 0}));
    // world_vector.emplace_back(World(&graphics, 960 + 6000, 1060 + 1100 - 8000, 1000 + 500 + 40000, {1, 0, 0}));




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
    num_zombeis = 10;
    //num_zombeis = 0;

    for (int i = 0; i < num_zombeis; i++){
        random_numx = distribx(gen);
        random_numz = distribz(gen);
        zombei_vector.emplace_back(Zombei(&graphics, random_numx, 1064, random_numz));
    }

    // Randomly setting speed for zombeis.
    for (int i = 0; i < num_zombeis; i++){
        random_nums = distribs(gen);
        zombei_vector[i].speed = random_nums;
    }



    //Making stars

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
    starscape_base_triangle_points_3D = graphics.find_triangles_sphere(starscape_base_points_3D, "outline", {0, 0, 0}, {0, 0, 0}, 0);

    for (int i = 0; i < starscape_base_triangle_points_3D.size(); i++){

        int minx = starscape_base_triangle_points_3D[i].points[0][0];
        int maxx = starscape_base_triangle_points_3D[i].points[1][0];

        if (minx > maxx) std::swap(minx, maxx);


        int miny = starscape_base_triangle_points_3D[i].points[0][1];
        int maxy = starscape_base_triangle_points_3D[i].points[2][1];

        if (miny > maxy) std::swap(miny, maxy);


        int minz = starscape_base_triangle_points_3D[i].points[0][2];
        int maxz = starscape_base_triangle_points_3D[i].points[2][2];

        if (minz > maxz) std::swap(minz, maxz);


        std::uniform_int_distribution<> distrib_starx(minx, maxx);
        std::uniform_int_distribution<> distrib_stary(miny, maxy);
        std::uniform_int_distribution<> distrib_starz(minz, maxz);

        int num_stars = 1;
        //while (num_stars < 5000){
        for (int i = 1; i < num_stars; i++){
            int random_star_numx = distrib_starx(gen);
            int random_star_numy = distrib_stary(gen);
            int random_star_numz = distrib_starz(gen);
            star_vector.emplace_back(Star(&graphics, (double)random_star_numx, (double)random_star_numy, (double)random_star_numz, random_star_numy + 100, random_star_numy - 100));
        }
            
    }

    glutMainLoop();

    return 0;
}



// FIXX:
// -make bow
// -make arm movement better
// -refine zombei leg movement animation
// -comment graphics.find_floor_lines_on_globe
// -investigate large numbers drawing coordinates when clipping
// -make gravity

// To implement culling:
// -write culling method?