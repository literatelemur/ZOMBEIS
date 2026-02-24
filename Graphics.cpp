#include <GL/glut.h>
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <list>
#include <functional>
#include <numeric>


#include "Graphics.h"
#include "Triangle.h"
#include "Edit.h"

        
Graphics::Graphics(){   

    zscreendiff = 1000;

    playerx = 960;
    playery = 1060;
    playerz = 0;

    near_plane = 0.1;
    anglex_diff = 0;
    angley_diff = 0;

}


std::vector<std::vector<double>> Graphics::make_sphere(std::vector<double> center, double radius, int num_points){

    // Equation of a sphere: (x - 960)^2 + (y - 540)^2 + (z - 10)^2 = radius^2

    std::vector<std::vector<double>> sphere_points_3D;

    if (num_points == 6){

        // 6-sided geodesic dome

        sphere_points_3D = std::vector<std::vector<double>>(6, std::vector<double>(3, 0));

        sphere_points_3D[0][0] = center[0] - radius;
        sphere_points_3D[0][1] = center[1];
        sphere_points_3D[0][2] = center[2];

        sphere_points_3D[1][0] = center[0] + radius;
        sphere_points_3D[1][1] = center[1];
        sphere_points_3D[1][2] = center[2];

        sphere_points_3D[2][0] = center[0];
        sphere_points_3D[2][1] = center[1] - radius;
        sphere_points_3D[2][2] = center[2];

        sphere_points_3D[3][0] = center[0];
        sphere_points_3D[3][1] = center[1] + radius;
        sphere_points_3D[3][2] = center[2];

        sphere_points_3D[4][0] = center[0];
        sphere_points_3D[4][1] = center[1];
        sphere_points_3D[4][2] = center[2] + radius;

        sphere_points_3D[5][0] = center[0];
        sphere_points_3D[5][1] = center[1];
        sphere_points_3D[5][2] = center[2] - radius;

    }else if (num_points == 5){

        sphere_points_3D = std::vector<std::vector<double>>(5, std::vector<double>(3, 0));

        sphere_points_3D[0][0] = center[0] - radius;
        sphere_points_3D[0][1] = center[1];
        sphere_points_3D[0][2] = center[2];

        sphere_points_3D[1][0] = center[0] + radius;
        sphere_points_3D[1][1] = center[1];
        sphere_points_3D[1][2] = center[2];

        // sphere_points_3D[2][0] = center[0];
        // sphere_points_3D[2][1] = center[1] - radius;
        // sphere_points_3D[2][2] = center[2];

        sphere_points_3D[2][0] = center[0];
        sphere_points_3D[2][1] = center[1] + radius;
        sphere_points_3D[2][2] = center[2];

        sphere_points_3D[3][0] = center[0];
        sphere_points_3D[3][1] = center[1];
        sphere_points_3D[3][2] = center[2] + radius;

        sphere_points_3D[4][0] = center[0];
        sphere_points_3D[4][1] = center[1];
        sphere_points_3D[4][2] = center[2] - radius;


    }else if (num_points == 4){

        // 2-sided flat plane

        sphere_points_3D = std::vector<std::vector<double>>(4, std::vector<double>(3, 0));

        sphere_points_3D[0][0] = center[0] - radius;
        sphere_points_3D[0][1] = center[1];
        sphere_points_3D[0][2] = center[2];

        sphere_points_3D[1][0] = center[0] + radius;
        sphere_points_3D[1][1] = center[1];
        sphere_points_3D[1][2] = center[2];

        sphere_points_3D[2][0] = center[0];
        sphere_points_3D[2][1] = center[1];
        sphere_points_3D[2][2] = center[2] + radius * sqrt(3);

        sphere_points_3D[3][0] = center[0];
        sphere_points_3D[3][1] = center[1];
        sphere_points_3D[3][2] = center[2] - radius * sqrt(3);


    }else if (num_points == 3){

        // 2-sided flat plane

        sphere_points_3D = std::vector<std::vector<double>>(3, std::vector<double>(3, 0));

        sphere_points_3D[0][0] = center[0] - radius;
        sphere_points_3D[0][1] = center[1];
        sphere_points_3D[0][2] = center[2];

        sphere_points_3D[1][0] = center[0] + radius;
        sphere_points_3D[1][1] = center[1];
        sphere_points_3D[1][2] = center[2];

        sphere_points_3D[2][0] = center[0];
        sphere_points_3D[2][1] = center[1];
        sphere_points_3D[2][2] = center[2] - radius * sqrt(3);

    } else if (num_points == 12){

        // copied attempt at 12-sided geodesic sphere AKA icosaphere (based on golden ratio):

        double phi = 1.6180339887;
        sphere_points_3D = { {center[0] + -1 * radius,  center[1] + phi * radius,  center[2] + 0 * radius}, {center[0] + 1 * radius,  center[1] + phi * radius,  center[2] + 0 * radius}, {center[0] + -1 * radius, center[1] + -phi * radius,  center[2] + 0 * radius}, {center[0] + 1 * radius, center[1] + -phi * radius,  center[2] + 0 * radius},
            {center[0] + 0 * radius, center[1] + -1 * radius,  center[2] + phi * radius}, {center[0] + 0 * radius,  center[1] + 1 * radius,  center[2] + phi * radius}, {center[0] + 0 * radius, center[1] + -1 * radius, center[2] + -phi * radius}, {center[0] + 0 * radius,  center[1] + 1 * radius, center[2] + -phi * radius},
            {center[0] + phi * radius,  center[1] + 0 * radius, center[2] + -1 * radius}, {center[0] + phi * radius,  center[1] + 0 * radius,  center[2] + 1 * radius}, {center[0] + -phi * radius,  center[1] + 0 * radius, center[2] + -1 * radius}, {center[0] + -phi * radius,  center[1] + 0 * radius,  center[2] + 1 * radius} };
    }

    return sphere_points_3D;
}


std::vector<std::vector<double>> Graphics::make_box(std::vector<double> center, double top_length, double side_length, double depth){
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


std::vector<Triangle> Graphics::find_triangles_sphere(std::vector<std::vector<double>> sphere_points_3D, std::string draw_type, std::vector<double> full_color, std::vector<double> outline_color, int lines_scale){

    std::vector<Triangle> triangles_points_3D_sphere;

    double shortest = std::numeric_limits<double>::max();
    double dist1;
    
    // Determining shortest line between first point and all other points.
    for (int j = 1; j < sphere_points_3D.size(); j++){

        double xdist = std::abs(sphere_points_3D[j][0] - sphere_points_3D[0][0]);
        double ydist = std::abs(sphere_points_3D[j][1] - sphere_points_3D[0][1]);
        double zdist = std::abs(sphere_points_3D[j][2] - sphere_points_3D[0][2]);

        dist1 = xdist*xdist + ydist*ydist + zdist*zdist;

        if (dist1 < shortest){
            shortest = dist1;
        }
    }


    for (int i = 0; i < sphere_points_3D.size(); i++){

        // Finding all adjacent points with shortest line between points.
        std::vector<int> adj_points;
        for (int j = 0; j < sphere_points_3D.size(); j++){
            if (i == j){continue;}

            double xdist = std::abs(sphere_points_3D[j][0] - sphere_points_3D[i][0]);
            double ydist = std::abs(sphere_points_3D[j][1] - sphere_points_3D[i][1]);
            double zdist = std::abs(sphere_points_3D[j][2] - sphere_points_3D[i][2]);

            dist1 = xdist*xdist + ydist*ydist + zdist*zdist;

            if (dist1 > shortest - shortest * 0.1 && dist1 < shortest + shortest * 0.1){
                adj_points.emplace_back(j);
            }
        }

        // Determining if adjacent points have same shortest line between adjacent point's adjcent points so that a full equilateral triangle is found.
        double dist2;
        double dist3;

        for (int a = 0; a < adj_points.size(); a++){

            for (int k = 0; k < sphere_points_3D.size(); k++){

                if (k == i || k == adj_points[a] || i == adj_points[a]){continue;}

                double xdist = std::abs(sphere_points_3D[k][0] - sphere_points_3D[adj_points[a]][0]);
                double ydist = std::abs(sphere_points_3D[k][1] - sphere_points_3D[adj_points[a]][1]);
                double zdist = std::abs(sphere_points_3D[k][2] - sphere_points_3D[adj_points[a]][2]);

                dist2 = xdist*xdist + ydist*ydist + zdist*zdist;


                xdist = std::abs(sphere_points_3D[k][0] - sphere_points_3D[i][0]);
                ydist = std::abs(sphere_points_3D[k][1] - sphere_points_3D[i][1]);
                zdist = std::abs(sphere_points_3D[k][2] - sphere_points_3D[i][2]);

                dist3 = xdist*xdist + ydist*ydist + zdist*zdist;
                    

                if (i < adj_points[a] && adj_points[a] < k && dist2 > shortest - shortest * 0.1 && dist2 < shortest + shortest * 0.1 && dist3 > shortest - shortest * 0.1 && dist3 < shortest + shortest * 0.1){
                    
                    triangles_points_3D_sphere.emplace_back(Triangle(this, sphere_points_3D[i], sphere_points_3D[adj_points[a]], sphere_points_3D[k], draw_type, full_color, outline_color, lines_scale));
                }
            }

        }
        
    }
    
    return triangles_points_3D_sphere;
}


std::vector<Triangle> Graphics::find_triangles_box(std::vector<std::vector<double>> box_points_3D, std::string draw_type, std::vector<double> full_color, std::vector<double> outline_color, int lines_scale){

    std::vector<Triangle> triangle_points_3D_box;

    triangle_points_3D_box.emplace_back(Triangle(this, box_points_3D[0], box_points_3D[1], box_points_3D[3], draw_type, full_color, outline_color, lines_scale));
    triangle_points_3D_box.emplace_back(Triangle(this, box_points_3D[3], box_points_3D[2], box_points_3D[0], draw_type, full_color, outline_color, lines_scale));

    triangle_points_3D_box.emplace_back(Triangle(this, box_points_3D[4], box_points_3D[5], box_points_3D[7], draw_type, full_color, outline_color, lines_scale));
    triangle_points_3D_box.emplace_back(Triangle(this, box_points_3D[7], box_points_3D[6], box_points_3D[4], draw_type, full_color, outline_color, lines_scale));

    triangle_points_3D_box.emplace_back(Triangle(this, box_points_3D[1], box_points_3D[0], box_points_3D[4], draw_type, full_color, outline_color, lines_scale));
    triangle_points_3D_box.emplace_back(Triangle(this, box_points_3D[4], box_points_3D[5], box_points_3D[1], draw_type, full_color, outline_color, lines_scale));

    triangle_points_3D_box.emplace_back(Triangle(this, box_points_3D[3], box_points_3D[1], box_points_3D[5], draw_type, full_color, outline_color, lines_scale));
    triangle_points_3D_box.emplace_back(Triangle(this, box_points_3D[5], box_points_3D[7], box_points_3D[3], draw_type, full_color, outline_color, lines_scale));

    triangle_points_3D_box.emplace_back(Triangle(this, box_points_3D[3], box_points_3D[2], box_points_3D[6], draw_type, full_color, outline_color, lines_scale));
    triangle_points_3D_box.emplace_back(Triangle(this, box_points_3D[6], box_points_3D[7], box_points_3D[3], draw_type, full_color, outline_color, lines_scale));

    triangle_points_3D_box.emplace_back(Triangle(this, box_points_3D[0], box_points_3D[2], box_points_3D[6], draw_type, full_color, outline_color, lines_scale));
    triangle_points_3D_box.emplace_back(Triangle(this, box_points_3D[6], box_points_3D[4], box_points_3D[0], draw_type, full_color, outline_color, lines_scale));

    return triangle_points_3D_box;
}


std::vector<Triangle> Graphics::order_triangles(std::vector<Triangle> triangles){

    std::vector<Triangle> ordered_triangles;

    std::vector<double> rando_order_dist_triangles;

    // Calculating Euclidian total distance from player to each point.
    for (int i = 0; i < triangles.size(); i++){

        double x_dist1 = abs(triangles[i].points[0][0] - playerx);
        double y_dist1 = abs(triangles[i].points[0][1] - playery);
        double z_dist1 = abs(triangles[i].points[0][2] - playerz);

        double total_dist1 = sqrt(x_dist1 * x_dist1 + y_dist1 * y_dist1 + z_dist1 * z_dist1);


        double x_dist2 = abs(triangles[i].points[1][0] - playerx);
        double y_dist2 = abs(triangles[i].points[1][1] - playery);
        double z_dist2 = abs(triangles[i].points[1][2] - playerz);

        double total_dist2 = sqrt(x_dist2 * x_dist2 + y_dist2 * y_dist2 + z_dist2 * z_dist2);


        double x_dist3 = abs(triangles[i].points[2][0] - playerx);
        double y_dist3 = abs(triangles[i].points[2][1] - playery);
        double z_dist3 = abs(triangles[i].points[2][2] - playerz);

        double total_dist3 = sqrt(x_dist3 * x_dist3 + y_dist3 * y_dist3 + z_dist3 * z_dist3);

        double average_dist = (total_dist1 + total_dist2 + total_dist3) / 3;

        rando_order_dist_triangles.emplace_back(average_dist);
    }


    // Building index vector.
    std::vector<int> ordered_indices(triangles.size());

    // Filling index vector with 0..n-1.
    std::iota(ordered_indices.begin(), ordered_indices.end(), 0); 

    // Sorting ordered_indices according to average distances.
    std::sort(ordered_indices.begin(), ordered_indices.end(),
              [&](int a, int b) {
                  return rando_order_dist_triangles[a] > rando_order_dist_triangles[b];
              });



    // Filling the empty ordered vector with the appropriate points from the given vector using ordered_indices vector.
    for (int i = 0; i < ordered_indices.size(); i++){
        ordered_triangles.emplace_back(triangles[ordered_indices[i]]);
    }

    return ordered_triangles;

}


void Graphics::store_all_triangles(std::vector<Triangle> given_all_triangles){
    all_triangles = given_all_triangles;
}


void Graphics::find_lines_on_triangles(){
    
    // Going through each triangle plane in the vector of triangles and finding line start and end points based on scaled difference between points.
    for (int i = 0; i < all_triangles.size(); i++){
            
        if (all_triangles[i].line_scale > 0 && all_triangles[i].line_scale < 101){

            std::vector<std::vector<std::vector<std::vector<double>>>> lines_points_3D;
            lines_points_3D.emplace_back();
            lines_points_3D.emplace_back();

            double xline_base1_start = all_triangles[i].points[0][0];
            double yline_base1_start = all_triangles[i].points[0][1];
            double zline_base1_start = all_triangles[i].points[0][2];

            double xline_base1_end = all_triangles[i].points[1][0];
            double yline_base1_end = all_triangles[i].points[1][1];
            double zline_base1_end = all_triangles[i].points[1][2];
            
            double xline_base2_start = all_triangles[i].points[2][0];
            double yline_base2_start = all_triangles[i].points[2][1];
            double zline_base2_start = all_triangles[i].points[2][2];

            double xline_base2_end = all_triangles[i].points[1][0];
            double yline_base2_end = all_triangles[i].points[1][1];
            double zline_base2_end = all_triangles[i].points[1][2];

            double xline_base3_start = all_triangles[i].points[0][0];
            double yline_base3_start = all_triangles[i].points[0][1];
            double zline_base3_start = all_triangles[i].points[0][2];

            double xline_base3_end = all_triangles[i].points[2][0];
            double yline_base3_end = all_triangles[i].points[2][1];
            double zline_base3_end = all_triangles[i].points[2][2];


            // Scale determines the number of lines on triangle.
            // Starting value and increment value should match and be evenly multiplied into last value of scale.
            for (int s = all_triangles[i].line_scale; s < 100; s += all_triangles[i].line_scale){

                // s must be int for precision, but it is reduced to a number between 0 and 1.
                double scale = s / 100.0;

                double xline_start = xline_base1_start + scale * (xline_base1_end - xline_base1_start);
                double yline_start = yline_base1_start + scale * (yline_base1_end - yline_base1_start);
                double zline_start = zline_base1_start + scale * (zline_base1_end - zline_base1_start);

                double xline_end = xline_base2_start + scale * (xline_base2_end - xline_base2_start);
                double yline_end = yline_base2_start + scale * (yline_base2_end - yline_base2_start);
                double zline_end = zline_base2_start + scale * (zline_base2_end - zline_base2_start);

                lines_points_3D[0].emplace_back();
                lines_points_3D[0][lines_points_3D[0].size() - 1].emplace_back();
                lines_points_3D[0][lines_points_3D[0].size() - 1].emplace_back();

                lines_points_3D[0][lines_points_3D[0].size() - 1][0].emplace_back(xline_start);
                lines_points_3D[0][lines_points_3D[0].size() - 1][0].emplace_back(yline_start);
                lines_points_3D[0][lines_points_3D[0].size() - 1][0].emplace_back(zline_start);

                lines_points_3D[0][lines_points_3D[0].size() - 1][1].emplace_back(xline_end);
                lines_points_3D[0][lines_points_3D[0].size() - 1][1].emplace_back(yline_end);
                lines_points_3D[0][lines_points_3D[0].size() - 1][1].emplace_back(zline_end);



                xline_start = xline_base1_start + scale * (xline_base1_end - xline_base1_start);
                yline_start = yline_base1_start + scale * (yline_base1_end - yline_base1_start);
                zline_start = zline_base1_start + scale * (zline_base1_end - zline_base1_start);

                xline_end = xline_base3_start + scale * (xline_base3_end - xline_base3_start);
                yline_end = yline_base3_start + scale * (yline_base3_end - yline_base3_start);
                zline_end = zline_base3_start + scale * (zline_base3_end - zline_base3_start);

                lines_points_3D[1].emplace_back();
                lines_points_3D[1][lines_points_3D[1].size() - 1].emplace_back();
                lines_points_3D[1][lines_points_3D[1].size() - 1].emplace_back();

                lines_points_3D[1][lines_points_3D[1].size() - 1][0].emplace_back(xline_start);
                lines_points_3D[1][lines_points_3D[1].size() - 1][0].emplace_back(yline_start);
                lines_points_3D[1][lines_points_3D[1].size() - 1][0].emplace_back(zline_start);

                lines_points_3D[1][lines_points_3D[1].size() - 1][1].emplace_back(xline_end);
                lines_points_3D[1][lines_points_3D[1].size() - 1][1].emplace_back(yline_end);
                lines_points_3D[1][lines_points_3D[1].size() - 1][1].emplace_back(zline_end);

            }

            all_triangles[i].lines_points_3D = std::move(lines_points_3D);
        }
    }
}


std::vector<std::vector<std::vector<std::vector<double>>>> Graphics::clip_triangles(){

    std::vector<std::vector<std::vector<std::vector<double>>>> clipped_triangles_as_lines;

    for (int i = 0; i < all_triangles.size(); i++){

        std::vector<std::vector<double>> line1;
        line1.emplace_back();
        line1[0].emplace_back(all_triangles[i].points[0][0]);
        line1[0].emplace_back(all_triangles[i].points[0][1]);
        line1[0].emplace_back(all_triangles[i].points[0][2]);

        line1.emplace_back();
        line1[1].emplace_back(all_triangles[i].points[1][0]);
        line1[1].emplace_back(all_triangles[i].points[1][1]);
        line1[1].emplace_back(all_triangles[i].points[1][2]);


        std::vector<double> clipped_coor_diffs_line1 = clip_line(line1);


        std::vector<std::vector<double>> line2;
        line2.emplace_back();
        line2[0].emplace_back(all_triangles[i].points[1][0]);
        line2[0].emplace_back(all_triangles[i].points[1][1]);
        line2[0].emplace_back(all_triangles[i].points[1][2]);

        line2.emplace_back();
        line2[1].emplace_back(all_triangles[i].points[2][0]);
        line2[1].emplace_back(all_triangles[i].points[2][1]);
        line2[1].emplace_back(all_triangles[i].points[2][2]);

        std::vector<double> clipped_coor_diffs_line2 = clip_line(line2);


        std::vector<std::vector<double>> line3;

        line3.emplace_back();
        line3[0].emplace_back(all_triangles[i].points[2][0]);
        line3[0].emplace_back(all_triangles[i].points[2][1]);
        line3[0].emplace_back(all_triangles[i].points[2][2]);

        line3.emplace_back();
        line3[1].emplace_back(all_triangles[i].points[0][0]);
        line3[1].emplace_back(all_triangles[i].points[0][1]);
        line3[1].emplace_back(all_triangles[i].points[0][2]);


        std::vector<double> clipped_coor_diffs_line3 = clip_line(line3);



        std::vector<std::vector<double>> clipped_coor_line1;


        if (clipped_coor_diffs_line1[0] != -100000 && clipped_coor_diffs_line1[1] != -100000 && clipped_coor_diffs_line1[2] != -100000 && 
                clipped_coor_diffs_line1[3] != -100000 && clipped_coor_diffs_line1[4] != -100000 && clipped_coor_diffs_line1[5] != -100000){

            clipped_coor_line1.emplace_back();
            clipped_coor_line1[0].emplace_back(playerx + clipped_coor_diffs_line1[0]);
            clipped_coor_line1[0].emplace_back(playery + clipped_coor_diffs_line1[1]);
            clipped_coor_line1[0].emplace_back(playerz + clipped_coor_diffs_line1[2]);


            clipped_coor_line1.emplace_back();
            clipped_coor_line1[1].emplace_back(playerx + clipped_coor_diffs_line1[3]);
            clipped_coor_line1[1].emplace_back(playery + clipped_coor_diffs_line1[4]);
            clipped_coor_line1[1].emplace_back(playerz + clipped_coor_diffs_line1[5]);


        }else{

            clipped_coor_line1.emplace_back();
            clipped_coor_line1[0].emplace_back(-100000);
            clipped_coor_line1[0].emplace_back(-100000);
            clipped_coor_line1[0].emplace_back(-100000);


            clipped_coor_line1.emplace_back();
            clipped_coor_line1[1].emplace_back(-100000);
            clipped_coor_line1[1].emplace_back(-100000);
            clipped_coor_line1[1].emplace_back(-100000);
        }


        


        std::vector<std::vector<double>> clipped_coor_line2;

        if (clipped_coor_diffs_line2[0] != -100000 && clipped_coor_diffs_line2[1] != -100000 && clipped_coor_diffs_line2[2] != -100000 && 
                clipped_coor_diffs_line2[3] != -100000 && clipped_coor_diffs_line2[4] != -100000 && clipped_coor_diffs_line2[5] != -100000){

            clipped_coor_line2.emplace_back();
            clipped_coor_line2[0].emplace_back(playerx + clipped_coor_diffs_line2[0]);
            clipped_coor_line2[0].emplace_back(playery + clipped_coor_diffs_line2[1]);
            clipped_coor_line2[0].emplace_back(playerz + clipped_coor_diffs_line2[2]);


            clipped_coor_line2.emplace_back();
            clipped_coor_line2[1].emplace_back(playerx + clipped_coor_diffs_line2[3]);
            clipped_coor_line2[1].emplace_back(playery + clipped_coor_diffs_line2[4]);
            clipped_coor_line2[1].emplace_back(playerz + clipped_coor_diffs_line2[5]);

        }else{

            clipped_coor_line2.emplace_back();
            clipped_coor_line2[0].emplace_back(-100000);
            clipped_coor_line2[0].emplace_back(-100000);
            clipped_coor_line2[0].emplace_back(-100000);


            clipped_coor_line2.emplace_back();
            clipped_coor_line2[1].emplace_back(-100000);
            clipped_coor_line2[1].emplace_back(-100000);
            clipped_coor_line2[1].emplace_back(-100000);
        }


        std::vector<std::vector<double>> clipped_coor_line3;

        if (clipped_coor_diffs_line3[0] != -100000 && clipped_coor_diffs_line3[1] != -100000 && clipped_coor_diffs_line3[2] != -100000 && 
                clipped_coor_diffs_line3[3] != -100000 && clipped_coor_diffs_line3[4] != -100000 && clipped_coor_diffs_line3[5] != -100000){

            clipped_coor_line3.emplace_back();
            clipped_coor_line3[0].emplace_back(playerx + clipped_coor_diffs_line3[0]);
            clipped_coor_line3[0].emplace_back(playery + clipped_coor_diffs_line3[1]);
            clipped_coor_line3[0].emplace_back(playerz + clipped_coor_diffs_line3[2]);


            clipped_coor_line3.emplace_back();
            clipped_coor_line3[1].emplace_back(playerx + clipped_coor_diffs_line3[3]);
            clipped_coor_line3[1].emplace_back(playery + clipped_coor_diffs_line3[4]);
            clipped_coor_line3[1].emplace_back(playerz + clipped_coor_diffs_line3[5]);

        }else{

            clipped_coor_line3.emplace_back();
            clipped_coor_line3[0].emplace_back(-100000);
            clipped_coor_line3[0].emplace_back(-100000);
            clipped_coor_line3[0].emplace_back(-100000);


            clipped_coor_line3.emplace_back();
            clipped_coor_line3[1].emplace_back(-100000);
            clipped_coor_line3[1].emplace_back(-100000);
            clipped_coor_line3[1].emplace_back(-100000);
        }


        clipped_triangles_as_lines.emplace_back();
        
        clipped_triangles_as_lines[i].emplace_back();
        clipped_triangles_as_lines[i][0].emplace_back();
        clipped_triangles_as_lines[i][0][0].emplace_back(clipped_coor_line1[0][0]);
        clipped_triangles_as_lines[i][0][0].emplace_back(clipped_coor_line1[0][1]);
        clipped_triangles_as_lines[i][0][0].emplace_back(clipped_coor_line1[0][2]);

        clipped_triangles_as_lines[i][0].emplace_back();
        clipped_triangles_as_lines[i][0][1].emplace_back(clipped_coor_line1[1][0]);
        clipped_triangles_as_lines[i][0][1].emplace_back(clipped_coor_line1[1][1]);
        clipped_triangles_as_lines[i][0][1].emplace_back(clipped_coor_line1[1][2]);



        clipped_triangles_as_lines[i].emplace_back();
        clipped_triangles_as_lines[i][1].emplace_back();
        clipped_triangles_as_lines[i][1][0].emplace_back(clipped_coor_line2[0][0]);
        clipped_triangles_as_lines[i][1][0].emplace_back(clipped_coor_line2[0][1]);
        clipped_triangles_as_lines[i][1][0].emplace_back(clipped_coor_line2[0][2]);

        clipped_triangles_as_lines[i][1].emplace_back();
        clipped_triangles_as_lines[i][1][1].emplace_back(clipped_coor_line2[1][0]);
        clipped_triangles_as_lines[i][1][1].emplace_back(clipped_coor_line2[1][1]);
        clipped_triangles_as_lines[i][1][1].emplace_back(clipped_coor_line2[1][2]);



        clipped_triangles_as_lines[i].emplace_back();
        clipped_triangles_as_lines[i][2].emplace_back();
        clipped_triangles_as_lines[i][2][0].emplace_back(clipped_coor_line3[0][0]);
        clipped_triangles_as_lines[i][2][0].emplace_back(clipped_coor_line3[0][1]);
        clipped_triangles_as_lines[i][2][0].emplace_back(clipped_coor_line3[0][2]);

        clipped_triangles_as_lines[i][2].emplace_back();
        clipped_triangles_as_lines[i][2][1].emplace_back(clipped_coor_line3[1][0]);
        clipped_triangles_as_lines[i][2][1].emplace_back(clipped_coor_line3[1][1]);
        clipped_triangles_as_lines[i][2][1].emplace_back(clipped_coor_line3[1][2]);



        // Clipping triangle lines across the triangle.
        std::vector<std::vector<std::vector<std::vector<double>>>> clipped_lines_points_3D;

        // Iterating through all points on all lines on all triangles to clip the lines.
        for (int j = 0; j < all_triangles[i].lines_points_3D.size(); j++){
            clipped_lines_points_3D.emplace_back();

            for (int k = 0; k < all_triangles[i].lines_points_3D[j].size(); k++){
                clipped_lines_points_3D[j].emplace_back();


                clipped_lines_points_3D[j][k].emplace_back();
                clipped_lines_points_3D[j][k][0].emplace_back(0);
                clipped_lines_points_3D[j][k][0].emplace_back(0);
                clipped_lines_points_3D[j][k][0].emplace_back(0);


                clipped_lines_points_3D[j][k].emplace_back();
                clipped_lines_points_3D[j][k][1].emplace_back(0);
                clipped_lines_points_3D[j][k][1].emplace_back(0);
                clipped_lines_points_3D[j][k][1].emplace_back(0);


                std::vector<double> clipped_coor_diffs = clip_line(all_triangles[i].lines_points_3D[j][k]);
                
                double x1_clip_diff = clipped_coor_diffs[0];
                double y1_clip_diff = clipped_coor_diffs[1];
                double z1_clip_diff = clipped_coor_diffs[2];

                double x2_clip_diff = clipped_coor_diffs[3];
                double y2_clip_diff = clipped_coor_diffs[4];
                double z2_clip_diff = clipped_coor_diffs[5];

                



                if (x1_clip_diff == -100000 && y1_clip_diff == -100000 && z1_clip_diff == -100000 &&
                        x2_clip_diff == -100000 && y2_clip_diff == -100000 && z2_clip_diff == -100000){

                    clipped_lines_points_3D[j][k][0][0] = -100000;
                    clipped_lines_points_3D[j][k][0][1] = -100000;
                    clipped_lines_points_3D[j][k][0][2] = -100000;

                    clipped_lines_points_3D[j][k][1][0] = -100000;
                    clipped_lines_points_3D[j][k][1][1] = -100000;
                    clipped_lines_points_3D[j][k][1][2] = -100000;

                }else{

                    // Returning diff to objective point so that it can be plugged into compute_2D_point.
                    double x_3D = x1_clip_diff + playerx;
                    double y_3D = y1_clip_diff + playery;
                    double z_3D = z1_clip_diff + playerz;

                    std::vector<double> point_3D = {x_3D, y_3D, z_3D};

                    clipped_lines_points_3D[j][k][0][0] = point_3D[0];
                    clipped_lines_points_3D[j][k][0][1] = point_3D[1];
                    clipped_lines_points_3D[j][k][0][2] = point_3D[2];


                    x_3D = x2_clip_diff + playerx;
                    y_3D = y2_clip_diff + playery;
                    z_3D = z2_clip_diff + playerz;

                    point_3D = {x_3D, y_3D, z_3D};


                    clipped_lines_points_3D[j][k][1][0] = point_3D[0];
                    clipped_lines_points_3D[j][k][1][1] = point_3D[1];
                    clipped_lines_points_3D[j][k][1][2] = point_3D[2];
                }

            }
        }

        all_triangles[i].clipped_lines_points_3D = std::move(clipped_lines_points_3D);
        std::vector<std::vector<std::vector<std::vector<double>>>>().swap(all_triangles[i].lines_points_3D);
    }


    return clipped_triangles_as_lines;
}


std::vector<double> Graphics::clip_line(std::vector<std::vector<double>> line_points_3D){

    double x_diff1 = line_points_3D[0][0] - playerx;
    double y_diff1 = line_points_3D[0][1] - playery;
    double z_diff1 = line_points_3D[0][2] - playerz;

    double x_diff2 = line_points_3D[1][0] - playerx;
    double y_diff2 = line_points_3D[1][1] - playery;
    double z_diff2 = line_points_3D[1][2] - playerz;


    double x1_clip_diff;
    double y1_clip_diff;
    double z1_clip_diff;

    double x2_clip_diff;
    double y2_clip_diff;
    double z2_clip_diff;


    
    // Determining if clipping is necessary (when z value reaches behind player).
    if (z_diff1 < near_plane && z_diff2 < near_plane){

        x1_clip_diff = -100000;
        y1_clip_diff = -100000;
        z1_clip_diff = -100000;

        x2_clip_diff = -100000;
        y2_clip_diff = -100000;
        z2_clip_diff = -100000;


    }else if (z_diff1 < near_plane){

        double ratio_along = (near_plane - z_diff1) / (line_points_3D[1][2] - line_points_3D[0][2]);
        double x1_clip = line_points_3D[0][0] + ratio_along * (line_points_3D[1][0] - line_points_3D[0][0]);
        double y1_clip = line_points_3D[0][1] - ratio_along * (line_points_3D[0][1] - line_points_3D[1][1]);


        x1_clip_diff = x1_clip - playerx;
        y1_clip_diff = y1_clip - playery;
        z1_clip_diff = near_plane;

        x2_clip_diff = x_diff2;
        y2_clip_diff = y_diff2;
        z2_clip_diff = z_diff2;



    }else if (z_diff2 < near_plane){

        x1_clip_diff = x_diff1;
        y1_clip_diff = y_diff1;
        z1_clip_diff = z_diff1;

        double ratio_along = (near_plane - z_diff2) / (line_points_3D[0][2] - line_points_3D[1][2]);
        double x2_clip = line_points_3D[1][0] + ratio_along * (line_points_3D[0][0] - line_points_3D[1][0]);
        double y2_clip = line_points_3D[1][1] - ratio_along * (line_points_3D[1][1] - line_points_3D[0][1]);
        double z2_clip = near_plane;


        x2_clip_diff = x2_clip - playerx;
        y2_clip_diff = y2_clip - playery;
        z2_clip_diff = near_plane;


    }else{

        x1_clip_diff = x_diff1;
        y1_clip_diff = y_diff1;
        z1_clip_diff = z_diff1;

        x2_clip_diff = x_diff2;
        y2_clip_diff = y_diff2;
        z2_clip_diff = z_diff2;
    }

    std::vector<double> clipped_coor_diffs;
    clipped_coor_diffs.emplace_back(x1_clip_diff);
    clipped_coor_diffs.emplace_back(y1_clip_diff);
    clipped_coor_diffs.emplace_back(z1_clip_diff);
    clipped_coor_diffs.emplace_back(x2_clip_diff);
    clipped_coor_diffs.emplace_back(y2_clip_diff);
    clipped_coor_diffs.emplace_back(z2_clip_diff);

    return clipped_coor_diffs;
}


std::vector<std::vector<std::vector<std::vector<double>>>> Graphics::compute_2D_triangles_as_lines(std::vector<std::vector<std::vector<std::vector<double>>>> clipped_triangles_as_lines){

    std::vector<std::vector<std::vector<std::vector<double>>>> triangles_2D_as_lines;

    // Iterating through all points on a given vector of clipped triangles to compute the 2D window view point counterparts for a 3D object as observed by an eye behind the window.
    for (int i = 0; i < clipped_triangles_as_lines.size(); i++){
        triangles_2D_as_lines.emplace_back();
        triangles_2D_as_lines[i].emplace_back();

        if (clipped_triangles_as_lines[i][0][0][0] != -100000 && clipped_triangles_as_lines[i][0][0][1] != -100000 && clipped_triangles_as_lines[i][0][0][2] != -100000 &&
                clipped_triangles_as_lines[i][0][1][0] != -100000 && clipped_triangles_as_lines[i][0][1][1] != -100000 && clipped_triangles_as_lines[i][0][1][2] != -100000){

            triangles_2D_as_lines[i][0].emplace_back(compute_2D_point(clipped_triangles_as_lines[i][0][0]));
            triangles_2D_as_lines[i][0].emplace_back(compute_2D_point(clipped_triangles_as_lines[i][0][1]));
        }else{
            triangles_2D_as_lines[i][0].emplace_back(std::vector<double>{-100000, -100000});
            triangles_2D_as_lines[i][0].emplace_back(std::vector<double>{-100000, -100000});
        }


        triangles_2D_as_lines[i].emplace_back();

        if (clipped_triangles_as_lines[i][1][0][0] != -100000 && clipped_triangles_as_lines[i][1][0][1] != -100000 && clipped_triangles_as_lines[i][1][0][2] != -100000 &&
                clipped_triangles_as_lines[i][1][1][0] != -100000 && clipped_triangles_as_lines[i][1][1][1] != -100000 && clipped_triangles_as_lines[i][1][1][2] != -100000){

            triangles_2D_as_lines[i][1].emplace_back(compute_2D_point(clipped_triangles_as_lines[i][1][0]));
            triangles_2D_as_lines[i][1].emplace_back(compute_2D_point(clipped_triangles_as_lines[i][1][1]));
        }else{
            triangles_2D_as_lines[i][1].emplace_back(std::vector<double>{-100000, -100000});
            triangles_2D_as_lines[i][1].emplace_back(std::vector<double>{-100000, -100000});
        }


        triangles_2D_as_lines[i].emplace_back();

        if (clipped_triangles_as_lines[i][2][0][0] != -100000 && clipped_triangles_as_lines[i][2][0][1] != -100000 && clipped_triangles_as_lines[i][2][0][2] != -100000 &&
                clipped_triangles_as_lines[i][2][1][0] != -100000 && clipped_triangles_as_lines[i][2][1][1] != -100000 && clipped_triangles_as_lines[i][2][1][2] != -100000){
                    
            triangles_2D_as_lines[i][2].emplace_back(compute_2D_point(clipped_triangles_as_lines[i][2][0]));
            triangles_2D_as_lines[i][2].emplace_back(compute_2D_point(clipped_triangles_as_lines[i][2][1]));
        }else{
            triangles_2D_as_lines[i][2].emplace_back(std::vector<double>{-100000, -100000});
            triangles_2D_as_lines[i][2].emplace_back(std::vector<double>{-100000, -100000});
        }

    }

    

    // Computing 2D coordinates for each point on each line on each line direction on each triangle.
    for (int i = 0; i < all_triangles.size(); i++){
        std::vector<std::vector<std::vector<std::vector<double>>>> clipped_lines_points_2D;

        for (int j = 0; j < all_triangles[i].clipped_lines_points_3D.size(); j++){
            clipped_lines_points_2D.emplace_back();

            for (int k = 0; k < all_triangles[i].clipped_lines_points_3D[j].size(); k++){
                clipped_lines_points_2D[j].emplace_back();

                std::vector<double> point_2D = compute_2D_point(all_triangles[i].clipped_lines_points_3D[j][k][0]);
                clipped_lines_points_2D[j][k].emplace_back(point_2D);

                point_2D = compute_2D_point(all_triangles[i].clipped_lines_points_3D[j][k][1]);
                clipped_lines_points_2D[j][k].emplace_back(point_2D);
            }

        }
        
        all_triangles[i].clipped_lines_points_2D = std::move(clipped_lines_points_2D);
        std::vector<std::vector<std::vector<std::vector<double>>>>().swap(all_triangles[i].clipped_lines_points_3D);

    }


    return triangles_2D_as_lines;

}


std::vector<double> Graphics::compute_2D_point(std::vector<double> point_3D){

    // Old way that utilizes shearing and distorts when angle increases.

    //std::vector<double> point_2D(2, 0);

    // // Determining the adjusted x and y 3D differences when considering turning.
    // double z_3D_diff = point_3D[2] - playerz;

    // double turnx_diff_3D = tan(anglex_diff) * z_3D_diff;
    // double turny_diff_3D = tan(angley_diff) * z_3D_diff;

    // // Computing the 2D window view point counterparts for a 3D object as observed by an eye behind the window.
    // double x_3D_diff = point_3D[0] - playerx + turnx_diff_3D;
    // double y_3D_diff = point_3D[1] - playery + turny_diff_3D;
    

    // double anglex = atan2(x_3D_diff, z_3D_diff);
    // double angley = atan2(y_3D_diff, z_3D_diff);


    // double x_2D_diff = tan(anglex) * zscreendiff;
    // double y_2D_diff = tan(angley) * zscreendiff;


    // point_2D[0] = 960 + x_2D_diff;
    // point_2D[1] = 540 + y_2D_diff;

    // return point_2D;





    // New way found by chatgpt.

    std::vector<double> point_2D(2, 0);

    // Translate
    double rel_x_3D = point_3D[0] - playerx;
    double rel_y_3D = point_3D[1] - playery;
    double rel_z_3D = point_3D[2] - playerz;

    // If you rotate a 2D point (x, z) by angle θ around the origin:

    // x' = x cosθ − z sinθ
    // z' = x sinθ + z cosθ

    // Yaw (turning around Y axis).
    double cos_x = cos(anglex_diff);
    double sin_x = sin(anglex_diff);

    double rel_turned_x_3D = rel_x_3D * cos_x - rel_z_3D * sin_x;
    double rel_turned_z_for_x_3D = rel_x_3D * sin_x + rel_z_3D * cos_x;

    // Pitch (turning around X axis).
    double cos_y = cos(angley_diff);
    double sin_y = sin(angley_diff);

    double rel_turned_y_3D = rel_y_3D * cos_y - rel_turned_z_for_x_3D * sin_y;
    double rel_turned_z_for_y_3D = rel_y_3D * sin_y + rel_turned_z_for_x_3D * cos_y;

    // Prevent divide by zero
    if (rel_turned_z_for_y_3D <= 0.001) rel_turned_z_for_y_3D = 0.001;

    double x_2D_diff = (rel_turned_x_3D / rel_turned_z_for_y_3D) * zscreendiff;
    double y_2D_diff = (rel_turned_y_3D / rel_turned_z_for_y_3D) * zscreendiff;


    // double x_2D_diff = tan(anglex) * zscreendiff;
    // double y_2D_diff = tan(angley) * zscreendiff;


    point_2D[0] = 960 + x_2D_diff;
    point_2D[1] = 540 + y_2D_diff;

    return point_2D;



    // Exact copy from chatgpt.

    // std::vector<double> point_2D(2, 0);

    // // Translate
    // double x = point_3D[0] - playerx;
    // double y = point_3D[1] - playery;
    // double z = point_3D[2] - playerz;

    // // Yaw (Y axis)
    // double cosYaw = cos(anglex_diff);
    // double sinYaw = sin(anglex_diff);

    // double xz_x = x * cosYaw - z * sinYaw;
    // double xz_z = x * sinYaw + z * cosYaw;

    // // Pitch (X axis)
    // double cosPitch = cos(angley_diff);
    // double sinPitch = sin(angley_diff);

    // double yz_y = y * cosPitch - xz_z * sinPitch;
    // double yz_z = y * sinPitch + xz_z * cosPitch;

    // // Prevent divide by zero
    // if (yz_z <= 0.001) yz_z = 0.001;

    // double x_2D = (xz_x / yz_z) * zscreendiff;
    // double y_2D = (yz_y / yz_z) * zscreendiff;

    // point_2D[0] = 960 + x_2D;
    // point_2D[1] = 540 + y_2D;

    // return point_2D;

}


void Graphics::clear_draw_screen(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
    glClear(GL_COLOR_BUFFER_BIT);
}


void Graphics::draw_triangles_as_lines(std::vector<std::vector<std::vector<std::vector<double>>>> triangles_2D_as_lines){

    for (int i = 0; i < triangles_2D_as_lines.size(); i++){
        
        // Iterating through each point to see if it is already present in triangles_2D_as_lines. If so, only one copy is made because duplicates mess up drawing function.

        std::vector<std::vector<double>> valid_points;
        for (int j = 0; j < triangles_2D_as_lines[i].size(); j++){

            if (triangles_2D_as_lines[i][j][0][0] != -100000 && triangles_2D_as_lines[i][j][0][1] != -100000 && 
                    triangles_2D_as_lines[i][j][1][0] != -100000 && triangles_2D_as_lines[i][j][1][1] != -100000){


                for (int k = 0; k < triangles_2D_as_lines[i][j].size(); k++){
                    
                    bool exists = false;
                    for (int l = 0; l < valid_points.size(); l++){

                        if (triangles_2D_as_lines[i][j][k][0] == valid_points[l][0] && 
                                triangles_2D_as_lines[i][j][k][1] == valid_points[l][1]){
                            exists = true;
                        }
                    }

                    if (!exists){
                        valid_points.emplace_back();
                        valid_points[valid_points.size()-1].emplace_back(triangles_2D_as_lines[i][j][k][0]);
                        valid_points[valid_points.size()-1].emplace_back(triangles_2D_as_lines[i][j][k][1]);
                    }
                }
            }
        }

        if (all_triangles[i].draw_type == "outline"){

            set_color(all_triangles[i].outline_color[0], all_triangles[i].outline_color[1], all_triangles[i].outline_color[2]);

            if (valid_points.size() == 3){
                glBegin(GL_LINE_LOOP);
                    glVertex2d(valid_points[0][0], valid_points[0][1]);
                    glVertex2d(valid_points[1][0], valid_points[1][1]);
                    glVertex2d(valid_points[2][0], valid_points[2][1]);
                glEnd();

            
            }else if (valid_points.size() == 4){
                glBegin(GL_LINE_LOOP);
                    glVertex2d(valid_points[0][0], valid_points[0][1]);
                    glVertex2d(valid_points[1][0], valid_points[1][1]);
                    glVertex2d(valid_points[2][0], valid_points[2][1]);
                    glVertex2d(valid_points[3][0], valid_points[3][1]);
                glEnd();
                
            }


        }else if (all_triangles[i].draw_type == "full"){

            set_color(all_triangles[i].full_color[0], all_triangles[i].full_color[1], all_triangles[i].full_color[2]);
            
            if (valid_points.size() == 3){
                glBegin(GL_TRIANGLES);
                    glVertex2d(valid_points[0][0], valid_points[0][1]);
                    glVertex2d(valid_points[1][0], valid_points[1][1]);
                    glVertex2d(valid_points[2][0], valid_points[2][1]);
                glEnd();

            
            }else if (valid_points.size() == 4){
                glBegin(GL_POLYGON);
                    glVertex2d(valid_points[0][0], valid_points[0][1]);
                    glVertex2d(valid_points[1][0], valid_points[1][1]);
                    glVertex2d(valid_points[2][0], valid_points[2][1]);
                    glVertex2d(valid_points[3][0], valid_points[3][1]);
                glEnd();
                
            }

        } else if(all_triangles[i].draw_type == "both"){


            set_color(all_triangles[i].full_color[0], all_triangles[i].full_color[1], all_triangles[i].full_color[2]);

            if (valid_points.size() == 3){

                glBegin(GL_TRIANGLES);
                    glVertex2f(valid_points[0][0], valid_points[0][1]);
                    glVertex2f(valid_points[1][0], valid_points[1][1]);
                    glVertex2f(valid_points[2][0], valid_points[2][1]);
                glEnd();

                set_color(all_triangles[i].outline_color[0], all_triangles[i].outline_color[1], all_triangles[i].outline_color[2]);

                glBegin(GL_LINE_LOOP);
                    glVertex2f(valid_points[0][0], valid_points[0][1]);
                    glVertex2f(valid_points[1][0], valid_points[1][1]);
                    glVertex2f(valid_points[2][0], valid_points[2][1]);
                glEnd();

            
            }else if (valid_points.size() == 4){

                glBegin(GL_POLYGON);
                    glVertex2f(valid_points[0][0], valid_points[0][1]);
                    glVertex2f(valid_points[1][0], valid_points[1][1]);
                    glVertex2f(valid_points[2][0], valid_points[2][1]);
                    glVertex2f(valid_points[3][0], valid_points[3][1]);
                glEnd();

                set_color(all_triangles[i].outline_color[0], all_triangles[i].outline_color[1], all_triangles[i].outline_color[2]);
                
                glBegin(GL_LINE_LOOP);
                    glVertex2f(valid_points[0][0], valid_points[0][1]);
                    glVertex2f(valid_points[1][0], valid_points[1][1]);
                    glVertex2f(valid_points[2][0], valid_points[2][1]);
                    glVertex2f(valid_points[3][0], valid_points[3][1]);
                glEnd();
                
            }

        }


        
        // Drawing each line on each line direction on each triangle for the lines going across the triangle.
        for (int j = 0; j < all_triangles[i].clipped_lines_points_2D.size(); j++){
            for (int k = 0; k < all_triangles[i].clipped_lines_points_2D[j].size(); k++){
                    
                if (all_triangles[i].clipped_lines_points_2D[j][k][0][0] != -100000 && all_triangles[i].clipped_lines_points_2D[j][k][1][0] != -100000 &&
                        all_triangles[i].clipped_lines_points_2D[j][k][0][1] != -100000 && all_triangles[i].clipped_lines_points_2D[j][k][1][1] != -100000){

                    set_color(all_triangles[i].outline_color[0], all_triangles[i].outline_color[1], all_triangles[i].outline_color[2]);

                    glBegin(GL_LINES);
                        glVertex2f(all_triangles[i].clipped_lines_points_2D[j][k][0][0], all_triangles[i].clipped_lines_points_2D[j][k][0][1]);
                        glVertex2f(all_triangles[i].clipped_lines_points_2D[j][k][1][0], all_triangles[i].clipped_lines_points_2D[j][k][1][1]);
                    glEnd();

                }
            }
        }

    }

}


void Graphics::draw_hud(){

    if (!Edit::edit_mode){
        glBegin(GL_LINES);
            glVertex2f(1920 / 2 - 15, 1080 / 2);
            glVertex2f(1920 / 2 + 15, 1080 / 2);
        glEnd();

        glBegin(GL_LINES);
            glVertex2f(1920 / 2, 1080 / 2 - 15);
            glVertex2f(1920 / 2, 1080 / 2 + 15);
        glEnd();

    } else{
        glBegin(GL_LINES);
            glVertex2f(1920 / 2 - 15, 1080 / 2 - 15);
            glVertex2f(1920 / 2 + 15, 1080 / 2 + 15);
        glEnd();

        glBegin(GL_LINES);
            glVertex2f(1920 / 2 - 15, 1080 / 2 + 15);
            glVertex2f(1920 / 2 + 15, 1080 / 2 - 15);
        glEnd();


        glBegin(GL_LINES);
            glVertex2f(0 + 100, 0 + 150);
            glVertex2f(0 + 100, 0 + 100);
        glEnd();

        glBegin(GL_LINES);
            glVertex2f(0 + 100, 0 + 100);
            glVertex2f(0 + 150, 0 + 100);
        glEnd();

        
        glBegin(GL_LINES);
            glVertex2f(1920 - 150, 0 + 100);
            glVertex2f(1920 - 100, 0 + 100);
        glEnd();

        glBegin(GL_LINES);
            glVertex2f(1920 - 100, 0 + 100);
            glVertex2f(1920 - 100, 0 + 150);
        glEnd();


        glBegin(GL_LINES);
            glVertex2f(1920 - 100, 1080 - 150);
            glVertex2f(1920 - 100, 1080 - 100);
        glEnd();

        glBegin(GL_LINES);
            glVertex2f(1920 - 100, 1080 - 100);
            glVertex2f(1920 - 150, 1080 - 100);
        glEnd();


        glBegin(GL_LINES);
            glVertex2f(0 + 150, 1080 - 100);
            glVertex2f(0 + 100, 1080 - 100);
        glEnd();

        glBegin(GL_LINES);
            glVertex2f(0 + 100, 1080 - 100);
            glVertex2f(0 + 100, 1080 - 150);
        glEnd();

    }
}


void Graphics::set_color(int r, int g, int b){
    glColor3f(r, g, b);
}


void Graphics::present_frame(){
    // Present the rendered frame
    glFlush();
}