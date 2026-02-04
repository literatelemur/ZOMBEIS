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

        
Graphics::Graphics(){   

    zscreendiff = 1000;

    playerx = 960;
    playery = 1060;
    playerz = 0;

    near_plane = 0.1;
    anglex_diff = 0;
    angley_diff = 0;

}


void Graphics::store_all_triangles(std::vector<Triangle> given_all_triangles){
    all_triangles = given_all_triangles;
}


std::vector<std::vector<double>> Graphics::make_sphere(std::vector<double> center, int radius, int num_points){

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


std::vector<Triangle> Graphics::find_triangles_sphere(std::vector<std::vector<double>> sphere_points_3D){

    std::vector<Triangle> triangle_points_3D_sphere;

    for (int i = 0; i < sphere_points_3D.size(); i++){

        // Determining shortest line between each point and all other points.
        double shortest = 9007199254740992;
        double dist1;

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
            }else if (ydist <= xdist && ydist <= zdist){
                larger1 = xdist;
                larger2 = zdist;
            }else if (zdist <= xdist && zdist <= ydist){
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
            }else if (ydist <= xdist && ydist <= zdist){
                larger1 = xdist;
                larger2 = zdist;
            }else if (zdist <= xdist && zdist <= ydist){
                larger1 = xdist;
                larger2 = ydist;
            }

            dist1 = std::sqrt(larger1*larger1 + larger2*larger2);
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

                double larger1 = 0;
                double larger2 = 0;
                if (xdist <= ydist && xdist <= zdist){
                    larger1 = ydist;
                    larger2 = zdist;
                }else if (ydist <= xdist && ydist <= zdist){
                    larger1 = xdist;
                    larger2 = zdist;
                }else if (zdist <= xdist && zdist <= ydist){
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
                }else if (ydist <= xdist && ydist <= zdist){
                    larger1 = xdist;
                    larger2 = zdist;
                }else if (zdist <= xdist && zdist <= ydist){
                    larger1 = xdist;
                    larger2 = ydist;
                }

                dist3 = std::sqrt(larger1*larger1 + larger2*larger2);
                    
                if (dist2 > shortest - shortest * 0.1 && dist2 < shortest + shortest * 0.1 && dist3 > shortest - shortest * 0.1 && dist3 < shortest + shortest * 0.1){

                    triangle_points_3D_sphere.emplace_back(Triangle(this, sphere_points_3D[i], sphere_points_3D[adj_points[a]], sphere_points_3D[k], "both", {0, 0, 0}, {1, 0, 0}));
                }
            }

        }
        
    }
    
    return triangle_points_3D_sphere;
}


std::vector<Triangle> Graphics::find_triangles_box(std::vector<std::vector<double>> box_points_3D){

    std::vector<Triangle> triangle_points_3D_box;

    triangle_points_3D_box.emplace_back(Triangle(this, box_points_3D[0], box_points_3D[1], box_points_3D[3], "both", {1, 1, 1}, {0, 0, 0}));
    triangle_points_3D_box.emplace_back(Triangle(this, box_points_3D[3], box_points_3D[2], box_points_3D[0], "both", {1, 1, 1}, {0, 0, 0}));

    triangle_points_3D_box.emplace_back(Triangle(this, box_points_3D[4], box_points_3D[5], box_points_3D[7], "both", {1, 1, 1}, {0, 0, 0}));
    triangle_points_3D_box.emplace_back(Triangle(this, box_points_3D[7], box_points_3D[6], box_points_3D[4], "both", {1, 1, 1}, {0, 0, 0}));

    triangle_points_3D_box.emplace_back(Triangle(this, box_points_3D[1], box_points_3D[0], box_points_3D[4], "both", {1, 1, 1}, {0, 0, 0}));
    triangle_points_3D_box.emplace_back(Triangle(this, box_points_3D[4], box_points_3D[5], box_points_3D[1], "both", {1, 1, 1}, {0, 0, 0}));

    triangle_points_3D_box.emplace_back(Triangle(this, box_points_3D[3], box_points_3D[1], box_points_3D[5], "both", {1, 1, 1}, {0, 0, 0}));
    triangle_points_3D_box.emplace_back(Triangle(this, box_points_3D[5], box_points_3D[7], box_points_3D[3], "both", {1, 1, 1}, {0, 0, 0}));

    triangle_points_3D_box.emplace_back(Triangle(this, box_points_3D[3], box_points_3D[2], box_points_3D[6], "both", {1, 1, 1}, {0, 0, 0}));
    triangle_points_3D_box.emplace_back(Triangle(this, box_points_3D[6], box_points_3D[7], box_points_3D[3], "both", {1, 1, 1}, {0, 0, 0}));

    triangle_points_3D_box.emplace_back(Triangle(this, box_points_3D[0], box_points_3D[2], box_points_3D[6], "both", {1, 1, 1}, {0, 0, 0}));
    triangle_points_3D_box.emplace_back(Triangle(this, box_points_3D[6], box_points_3D[4], box_points_3D[0], "both", {1, 1, 1}, {0, 0, 0}));

    return triangle_points_3D_box;
}



std::vector<Triangle> Graphics::order_triangles(std::vector<Triangle> triangles){

    std::vector<Triangle> ordered_triangles(triangles.size(), Triangle);

    std::vector<double> rando_order_dist_sphere_points_3D;

    // Calculating Euclidian total distance from player to each point.
    for (int i = 0; i < sphere_points_3D.size(); i++){

        double x_dist = abs(sphere_points_3D[i][0] - playerx);
        double y_dist = abs(sphere_points_3D[i][1] - playery);
        double z_dist = abs(sphere_points_3D[i][2] - playerz);

        double total_dist = sqrt(x_dist * x_dist + y_dist * y_dist + z_dist * z_dist);

        rando_order_dist_sphere_points_3D.emplace_back(total_dist);
    }

    // // Mirroring the decsended order vector to the random found order vector.
    // std::vector<double> desc_order_sphere_points_3D = rando_order_dist_sphere_points_3D;

    // // Sorting into a descended order.
    // sort(desc_order_sphere_points_3D.begin(), desc_order_sphere_points_3D.end(), std::greater<>());


    // Step 2: Build index list
    std::vector<double> ordered_indices(sphere_points_3D.size());

    // fill with 0..n-1
    std::iota(ordered_indices.begin(), ordered_indices.end(), 0); 

    // Step 3: Sort ordered_indices according to total distances
    std::sort(ordered_indices.begin(), ordered_indices.end(),
              [&](int a, int b) {
                  return rando_order_dist_sphere_points_3D[a] > rando_order_dist_sphere_points_3D[b];
              });



    // Filling the empty ordered vector with the appropriate points from the given vector using ordered_indices vector.
    for (int i = 0; i < ordered_indices.size(); i++){
        ordered_sphere_points_3D[i] = sphere_points_3D[ordered_indices[i]];
    }

    return ordered_sphere_points_3D;

}


std::vector<std::vector<std::vector<std::vector<double>>>> Graphics::find_floor_lines_on_globe(std::vector<Triangle> triangles_3D_sphere){
    std::vector<std::vector<std::vector<std::vector<double>>>> floor_points_3D;
    

    // Going through each triangle plane on the icosahedron globe and finding floor line start and end points based on scaled difference between points.
    floor_points_3D.emplace_back();
    floor_points_3D.emplace_back();
    

    for (int i = 0; i < triangles_3D_sphere.size(); i++){
            
        double xline_base1_start = triangles_3D_sphere[i].points[0][0];
        double yline_base1_start = triangles_3D_sphere[i].points[0][1];
        double zline_base1_start = triangles_3D_sphere[i].points[0][2];

        double xline_base1_end = triangles_3D_sphere[i].points[1][0];
        double yline_base1_end = triangles_3D_sphere[i].points[1][1];
        double zline_base1_end = triangles_3D_sphere[i].points[1][2];
        
        double xline_base2_start = triangles_3D_sphere[i].points[2][0];
        double yline_base2_start = triangles_3D_sphere[i].points[2][1];
        double zline_base2_start = triangles_3D_sphere[i].points[2][2];

        double xline_base2_end = triangles_3D_sphere[i].points[1][0];
        double yline_base2_end = triangles_3D_sphere[i].points[1][1];
        double zline_base2_end = triangles_3D_sphere[i].points[1][2];

        double xline_base3_start = triangles_3D_sphere[i].points[0][0];
        double yline_base3_start = triangles_3D_sphere[i].points[0][1];
        double zline_base3_start = triangles_3D_sphere[i].points[0][2];

        double xline_base3_end = triangles_3D_sphere[i].points[2][0];
        double yline_base3_end = triangles_3D_sphere[i].points[2][1];
        double zline_base3_end = triangles_3D_sphere[i].points[2][2];


        // Scale determines the number of lines on icosaphere.
        // Starting value and increment value should match and be evenly multiplied into 1.0.
        for (int s = 1; s < 10; s++){

            double scale = s / 10.0;

            double xline_start = xline_base1_start + scale * (xline_base1_end - xline_base1_start);
            double yline_start = yline_base1_start + scale * (yline_base1_end - yline_base1_start);
            double zline_start = zline_base1_start + scale * (zline_base1_end - zline_base1_start);

            double xline_end = xline_base2_start + scale * (xline_base2_end - xline_base2_start);
            double yline_end = yline_base2_start + scale * (yline_base2_end - yline_base2_start);
            double zline_end = zline_base2_start + scale * (zline_base2_end - zline_base2_start);

            floor_points_3D[0].emplace_back();
            floor_points_3D[0][floor_points_3D[0].size() - 1].emplace_back();
            floor_points_3D[0][floor_points_3D[0].size() - 1].emplace_back();

            floor_points_3D[0][floor_points_3D[0].size() - 1][0].emplace_back(xline_start);
            floor_points_3D[0][floor_points_3D[0].size() - 1][0].emplace_back(yline_start);
            floor_points_3D[0][floor_points_3D[0].size() - 1][0].emplace_back(zline_start);

            floor_points_3D[0][floor_points_3D[0].size() - 1][1].emplace_back(xline_end);
            floor_points_3D[0][floor_points_3D[0].size() - 1][1].emplace_back(yline_end);
            floor_points_3D[0][floor_points_3D[0].size() - 1][1].emplace_back(zline_end);



            xline_start = xline_base1_start + scale * (xline_base1_end - xline_base1_start);
            yline_start = yline_base1_start + scale * (yline_base1_end - yline_base1_start);
            zline_start = zline_base1_start + scale * (zline_base1_end - zline_base1_start);

            xline_end = xline_base3_start + scale * (xline_base3_end - xline_base3_start);
            yline_end = yline_base3_start + scale * (yline_base3_end - yline_base3_start);
            zline_end = zline_base3_start + scale * (zline_base3_end - zline_base3_start);

            floor_points_3D[1].emplace_back();
            floor_points_3D[1][floor_points_3D[1].size() - 1].emplace_back();
            floor_points_3D[1][floor_points_3D[1].size() - 1].emplace_back();

            floor_points_3D[1][floor_points_3D[1].size() - 1][0].emplace_back(xline_start);
            floor_points_3D[1][floor_points_3D[1].size() - 1][0].emplace_back(yline_start);
            floor_points_3D[1][floor_points_3D[1].size() - 1][0].emplace_back(zline_start);

            floor_points_3D[1][floor_points_3D[1].size() - 1][1].emplace_back(xline_end);
            floor_points_3D[1][floor_points_3D[1].size() - 1][1].emplace_back(yline_end);
            floor_points_3D[1][floor_points_3D[1].size() - 1][1].emplace_back(zline_end);

        }
    }

    return floor_points_3D;
}


// std::vector<std::vector<std::vector<std::vector<double>>>> Graphics::find_floor_lines_on_globe(std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> triangle_points_3D_sphere){
//     std::vector<std::vector<std::vector<std::vector<double>>>> floor_points_3D;
    

//     // Going through each triangle plane on the icosahedron globe and finding floor line start and end points based on scaled difference between points.
//     floor_points_3D.emplace_back();
//     floor_points_3D.emplace_back();


//     std::vector<std::vector<std::vector<double>>> triangle_planes_already_lined;

//     for (int i = 0; i < triangle_points_3D_sphere.size(); i++){
//         for (int j = 0; j < triangle_points_3D_sphere[i].size(); j++){
//             for (int l = 0; l < triangle_points_3D_sphere[i][j].size(); l++){
                
//                 // Checking to see if triangle plane has already been given floor lines. If so, it is skipped.
//                 int skip_count;
//                 bool skip = false;
//                 for (int t = 0; t < triangle_planes_already_lined.size(); t++){
//                     skip_count = 0;

//                     for (int p = 0; p < triangle_planes_already_lined[t].size(); p++){
//                         for (int pp = 0; pp < triangle_points_3D_sphere[i][j][l].size(); pp++){

//                             if (triangle_planes_already_lined[t][p][0] == triangle_points_3D_sphere[i][j][l][pp][0] &&
//                                     triangle_planes_already_lined[t][p][1] == triangle_points_3D_sphere[i][j][l][pp][1] &&
//                                     triangle_planes_already_lined[t][p][2] == triangle_points_3D_sphere[i][j][l][pp][2]){
//                                 skip_count++;
//                             }

//                         }

//                     }

//                     if (skip_count == 3){
//                         skip = true;
//                     }
//                 }


//                 if (!skip){
//                     double xline_base1_start = triangle_points_3D_sphere[i][j][l][0][0];
//                     double yline_base1_start = triangle_points_3D_sphere[i][j][l][0][1];
//                     double zline_base1_start = triangle_points_3D_sphere[i][j][l][0][2];

//                     double xline_base1_end = triangle_points_3D_sphere[i][j][l][1][0];
//                     double yline_base1_end = triangle_points_3D_sphere[i][j][l][1][1];
//                     double zline_base1_end = triangle_points_3D_sphere[i][j][l][1][2];
                    
//                     double xline_base2_start = triangle_points_3D_sphere[i][j][l][2][0];
//                     double yline_base2_start = triangle_points_3D_sphere[i][j][l][2][1];
//                     double zline_base2_start = triangle_points_3D_sphere[i][j][l][2][2];

//                     double xline_base2_end = triangle_points_3D_sphere[i][j][l][1][0];
//                     double yline_base2_end = triangle_points_3D_sphere[i][j][l][1][1];
//                     double zline_base2_end = triangle_points_3D_sphere[i][j][l][1][2];

//                     double xline_base3_start = triangle_points_3D_sphere[i][j][l][0][0];
//                     double yline_base3_start = triangle_points_3D_sphere[i][j][l][0][1];
//                     double zline_base3_start = triangle_points_3D_sphere[i][j][l][0][2];

//                     double xline_base3_end = triangle_points_3D_sphere[i][j][l][2][0];
//                     double yline_base3_end = triangle_points_3D_sphere[i][j][l][2][1];
//                     double zline_base3_end = triangle_points_3D_sphere[i][j][l][2][2];


//                     // Scale determines the number of lines on icosaphere.
//                     // Starting value and increment value should match and be evenly multiplied into 1.0.
//                     for (int s = 1; s < 10; s++){

//                         double scale = s / 10.0;

//                         double xline_start = xline_base1_start + scale * (xline_base1_end - xline_base1_start);
//                         double yline_start = yline_base1_start + scale * (yline_base1_end - yline_base1_start);
//                         double zline_start = zline_base1_start + scale * (zline_base1_end - zline_base1_start);

//                         double xline_end = xline_base2_start + scale * (xline_base2_end - xline_base2_start);
//                         double yline_end = yline_base2_start + scale * (yline_base2_end - yline_base2_start);
//                         double zline_end = zline_base2_start + scale * (zline_base2_end - zline_base2_start);

//                         floor_points_3D[0].emplace_back();
//                         floor_points_3D[0][floor_points_3D[0].size() - 1].emplace_back();
//                         floor_points_3D[0][floor_points_3D[0].size() - 1].emplace_back();

//                         floor_points_3D[0][floor_points_3D[0].size() - 1][0].emplace_back(xline_start);
//                         floor_points_3D[0][floor_points_3D[0].size() - 1][0].emplace_back(yline_start);
//                         floor_points_3D[0][floor_points_3D[0].size() - 1][0].emplace_back(zline_start);

//                         floor_points_3D[0][floor_points_3D[0].size() - 1][1].emplace_back(xline_end);
//                         floor_points_3D[0][floor_points_3D[0].size() - 1][1].emplace_back(yline_end);
//                         floor_points_3D[0][floor_points_3D[0].size() - 1][1].emplace_back(zline_end);



//                         xline_start = xline_base1_start + scale * (xline_base1_end - xline_base1_start);
//                         yline_start = yline_base1_start + scale * (yline_base1_end - yline_base1_start);
//                         zline_start = zline_base1_start + scale * (zline_base1_end - zline_base1_start);

//                         xline_end = xline_base3_start + scale * (xline_base3_end - xline_base3_start);
//                         yline_end = yline_base3_start + scale * (yline_base3_end - yline_base3_start);
//                         zline_end = zline_base3_start + scale * (zline_base3_end - zline_base3_start);

//                         floor_points_3D[1].emplace_back();
//                         floor_points_3D[1][floor_points_3D[1].size() - 1].emplace_back();
//                         floor_points_3D[1][floor_points_3D[1].size() - 1].emplace_back();

//                         floor_points_3D[1][floor_points_3D[1].size() - 1][0].emplace_back(xline_start);
//                         floor_points_3D[1][floor_points_3D[1].size() - 1][0].emplace_back(yline_start);
//                         floor_points_3D[1][floor_points_3D[1].size() - 1][0].emplace_back(zline_start);

//                         floor_points_3D[1][floor_points_3D[1].size() - 1][1].emplace_back(xline_end);
//                         floor_points_3D[1][floor_points_3D[1].size() - 1][1].emplace_back(yline_end);
//                         floor_points_3D[1][floor_points_3D[1].size() - 1][1].emplace_back(zline_end);

//                     }

//                     triangle_planes_already_lined.emplace_back();
//                     triangle_planes_already_lined[triangle_planes_already_lined.size()-1].emplace_back();
//                     triangle_planes_already_lined[triangle_planes_already_lined.size()-1][triangle_planes_already_lined[triangle_planes_already_lined.size()-1].size()-1].emplace_back(triangle_points_3D_sphere[i][j][l][0][0]);
//                     triangle_planes_already_lined[triangle_planes_already_lined.size()-1][triangle_planes_already_lined[triangle_planes_already_lined.size()-1].size()-1].emplace_back(triangle_points_3D_sphere[i][j][l][0][1]);
//                     triangle_planes_already_lined[triangle_planes_already_lined.size()-1][triangle_planes_already_lined[triangle_planes_already_lined.size()-1].size()-1].emplace_back(triangle_points_3D_sphere[i][j][l][0][2]);

//                     triangle_planes_already_lined[triangle_planes_already_lined.size()-1].emplace_back();
//                     triangle_planes_already_lined[triangle_planes_already_lined.size()-1][triangle_planes_already_lined[triangle_planes_already_lined.size()-1].size()-1].emplace_back(triangle_points_3D_sphere[i][j][l][1][0]);
//                     triangle_planes_already_lined[triangle_planes_already_lined.size()-1][triangle_planes_already_lined[triangle_planes_already_lined.size()-1].size()-1].emplace_back(triangle_points_3D_sphere[i][j][l][1][1]);
//                     triangle_planes_already_lined[triangle_planes_already_lined.size()-1][triangle_planes_already_lined[triangle_planes_already_lined.size()-1].size()-1].emplace_back(triangle_points_3D_sphere[i][j][l][1][2]);

//                     triangle_planes_already_lined[triangle_planes_already_lined.size()-1].emplace_back();
//                     triangle_planes_already_lined[triangle_planes_already_lined.size()-1][triangle_planes_already_lined[triangle_planes_already_lined.size()-1].size()-1].emplace_back(triangle_points_3D_sphere[i][j][l][2][0]);
//                     triangle_planes_already_lined[triangle_planes_already_lined.size()-1][triangle_planes_already_lined[triangle_planes_already_lined.size()-1].size()-1].emplace_back(triangle_points_3D_sphere[i][j][l][2][1]);
//                     triangle_planes_already_lined[triangle_planes_already_lined.size()-1][triangle_planes_already_lined[triangle_planes_already_lined.size()-1].size()-1].emplace_back(triangle_points_3D_sphere[i][j][l][2][2]);
                    
//                 }

//             }


//         }   

//     }

//     return floor_points_3D;
// }


std::vector<std::vector<std::vector<std::vector<double>>>> Graphics::clip_triangles(std::vector<Triangle> triangles){

    std::vector<std::vector<std::vector<std::vector<double>>>> clipped_triangles_as_lines;

    for (int i = 0; i < triangles.size(); i++){

        std::vector<std::vector<double>> line1;
        line1.emplace_back();
        line1[0].emplace_back(triangles[i].points[0][0]);
        line1[0].emplace_back(triangles[i].points[0][1]);
        line1[0].emplace_back(triangles[i].points[0][2]);

        line1.emplace_back();
        line1[1].emplace_back(triangles[i].points[1][0]);
        line1[1].emplace_back(triangles[i].points[1][1]);
        line1[1].emplace_back(triangles[i].points[1][2]);


        std::vector<double> clipped_coor_diffs_line1 = clip_3D_line(line1);


        std::vector<std::vector<double>> line2;
        line2.emplace_back();
        line2[0].emplace_back(triangles[i].points[1][0]);
        line2[0].emplace_back(triangles[i].points[1][1]);
        line2[0].emplace_back(triangles[i].points[1][2]);

        line2.emplace_back();
        line2[1].emplace_back(triangles[i].points[2][0]);
        line2[1].emplace_back(triangles[i].points[2][1]);
        line2[1].emplace_back(triangles[i].points[2][2]);

        std::vector<double> clipped_coor_diffs_line2 = clip_3D_line(line2);


        std::vector<std::vector<double>> line3;

        line3.emplace_back();
        line3[0].emplace_back(triangles[i].points[2][0]);
        line3[0].emplace_back(triangles[i].points[2][1]);
        line3[0].emplace_back(triangles[i].points[2][2]);

        line3.emplace_back();
        line3[1].emplace_back(triangles[i].points[0][0]);
        line3[1].emplace_back(triangles[i].points[0][1]);
        line3[1].emplace_back(triangles[i].points[0][2]);


        std::vector<double> clipped_coor_diffs_line3 = clip_3D_line(line3);



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
    }

    return clipped_triangles_as_lines;

}


std::vector<std::vector<std::vector<std::vector<double>>>> Graphics::clip_sphere_lines(std::vector<std::vector<std::vector<std::vector<double>>>> lines_points_3D){

    std::vector<std::vector<std::vector<std::vector<double>>>> clipped_lines_points_3D;

    // Iterating through all points on an object to compute the 2D window view point counterparts for a 3D object as observed by an eye behind the window.
    for (int i = 0; i < lines_points_3D.size(); i++){
        clipped_lines_points_3D.emplace_back();

        for (int j = 0; j < lines_points_3D[i].size(); j++){
            clipped_lines_points_3D[i].emplace_back();


            clipped_lines_points_3D[i][j].emplace_back();
            clipped_lines_points_3D[i][j][0].emplace_back(0);
            clipped_lines_points_3D[i][j][0].emplace_back(0);
            clipped_lines_points_3D[i][j][0].emplace_back(0);


            clipped_lines_points_3D[i][j].emplace_back();
            clipped_lines_points_3D[i][j][1].emplace_back(0);
            clipped_lines_points_3D[i][j][1].emplace_back(0);
            clipped_lines_points_3D[i][j][1].emplace_back(0);


            std::vector<double> clipped_coor_diffs = clip_3D_line(lines_points_3D[i][j]);
            
            double x1_clip_diff = clipped_coor_diffs[0];
            double y1_clip_diff = clipped_coor_diffs[1];
            double z1_clip_diff = clipped_coor_diffs[2];

            double x2_clip_diff = clipped_coor_diffs[3];
            double y2_clip_diff = clipped_coor_diffs[4];
            double z2_clip_diff = clipped_coor_diffs[5];

            



            if (x1_clip_diff == -100000 && y1_clip_diff == -100000 && z1_clip_diff == -100000 &&
                    x2_clip_diff == -100000 && y2_clip_diff == -100000 && z2_clip_diff == -100000){

                clipped_lines_points_3D[i][j][0][0] = -100000;
                clipped_lines_points_3D[i][j][0][1] = -100000;
                clipped_lines_points_3D[i][j][0][2] = -100000;

                clipped_lines_points_3D[i][j][1][0] = -100000;
                clipped_lines_points_3D[i][j][1][1] = -100000;
                clipped_lines_points_3D[i][j][1][2] = -100000;

            }else{

                // Returning diff to objective point so that it can be plugged into compute_2D_point.
                double x_3D = x1_clip_diff + playerx;
                double y_3D = y1_clip_diff + playery;
                double z_3D = z1_clip_diff + playerz;

                std::vector<double> point_3D = {x_3D, y_3D, z_3D};

                clipped_lines_points_3D[i][j][0][0] = point_3D[0];
                clipped_lines_points_3D[i][j][0][1] = point_3D[1];
                clipped_lines_points_3D[i][j][0][2] = point_3D[2];


                x_3D = x2_clip_diff + playerx;
                y_3D = y2_clip_diff + playery;
                z_3D = z2_clip_diff + playerz;

                point_3D = {x_3D, y_3D, z_3D};


                clipped_lines_points_3D[i][j][1][0] = point_3D[0];
                clipped_lines_points_3D[i][j][1][1] = point_3D[1];
                clipped_lines_points_3D[i][j][1][2] = point_3D[2];
            }

        }
    }


    return clipped_lines_points_3D;

}


std::vector<double> Graphics::clip_3D_line(std::vector<std::vector<double>> line_points_3D){

    double x_diff1 = line_points_3D[0][0] - playerx;
    double y_diff1 = line_points_3D[0][1] - playery;
    double z_diff1 = line_points_3D[0][2] - playerz + near_plane;

    double x_diff2 = line_points_3D[1][0] - playerx;
    double y_diff2 = line_points_3D[1][1] - playery;
    double z_diff2 = line_points_3D[1][2] - playerz + near_plane;


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

    // Iterating through all points on a given vector of triangles to compute the 2D window view point counterparts for a 3D object as observed by an eye behind the window.
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

    return triangles_2D_as_lines;

}


std::vector<double> Graphics::compute_2D_point(std::vector<double> point_3D){

    std::vector<double> point_2D(2, 0);

    // Determining the adjusted x and y 3D differences when considering turning.
    double z_3D_diff = point_3D[2] - playerz;

    double turnx_diff_3D = tan(anglex_diff) * z_3D_diff;
    double turny_diff_3D = tan(angley_diff) * z_3D_diff;

    // Computing the 2D window view point counterparts for a 3D object as observed by an eye behind the window.
    double x_3D_diff = point_3D[0] - playerx + turnx_diff_3D;
    double y_3D_diff = point_3D[1] - playery + turny_diff_3D;
    

    double anglex = atan2(x_3D_diff, z_3D_diff);

    double angley = atan2(y_3D_diff, z_3D_diff);


    double x_2D_diff = tan(anglex) * zscreendiff;
    double y_2D_diff = tan(angley) * zscreendiff;


    point_2D[0] = 960 + x_2D_diff;
    point_2D[1] = 540 + y_2D_diff;

    return point_2D;

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
                glBegin(GL_TRIANGLES);
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

                glBegin(GL_LINES);
                    glVertex2f(valid_points[0][0], valid_points[0][1]);
                    glVertex2f(valid_points[1][0], valid_points[1][1]);
                    glVertex2f(valid_points[2][0], valid_points[2][1]);
                glEnd();

            
            }else if (valid_points.size() == 4){

                glBegin(GL_TRIANGLES);
                    glVertex2f(valid_points[0][0], valid_points[0][1]);
                    glVertex2f(valid_points[1][0], valid_points[1][1]);
                    glVertex2f(valid_points[2][0], valid_points[2][1]);
                    glVertex2f(valid_points[3][0], valid_points[3][1]);
                glEnd();

                set_color(all_triangles[i].outline_color[0], all_triangles[i].outline_color[1], all_triangles[i].outline_color[2]);
                
                glBegin(GL_LINES);
                    glVertex2f(valid_points[0][0], valid_points[0][1]);
                    glVertex2f(valid_points[1][0], valid_points[1][1]);
                    glVertex2f(valid_points[2][0], valid_points[2][1]);
                    glVertex2f(valid_points[3][0], valid_points[3][1]);
                glEnd();
                
            }

        }

    }
}


void Graphics::draw_floor_lines(std::vector<std::vector<std::vector<std::vector<double>>>> floor_points_2D){

    for (int i = 0; i < floor_points_2D.size(); i++){
        for (int j = 0; j < floor_points_2D[i].size(); j++){
            if (floor_points_2D[i][j][0][0] != -100000 && floor_points_2D[i][j][1][0] != -100000 &&
                    floor_points_2D[i][j][0][1] != -100000 && floor_points_2D[i][j][1][1] != -100000){
                
                glBegin(GL_LINES);
                    glVertex2f(floor_points_2D[i][j][0][0], floor_points_2D[i][j][0][1]);
                    glVertex2f(floor_points_2D[i][j][1][0], floor_points_2D[i][j][1][1]);
                glEnd();

            }
        }
    }

}


void Graphics::draw_hud(){

    glBegin(GL_LINES);
        glVertex2f(1920 / 2 - 15, 1080 / 2);
        glVertex2f(1920 / 2 + 15, 1080 / 2);
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(1920 / 2, 1080 / 2 - 15);
        glVertex2f(1920 / 2, 1080 / 2 + 15);
    glEnd();
}


void Graphics::set_color(int r, int g, int b){
    glColor3f(r, g, b);
}


void Graphics::present_frame(){
    // Present the rendered frame
    glFlush();
}