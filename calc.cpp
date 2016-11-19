//
//  calc.cpp
//  Graphics_Project
//
//  Created by Yi Cao on 10/27/15.
//  Copyright © 2015 Yi Cao. All rights reserved.
//

#include "def.h"
#include "Face.h"
#include "Edge.h"
#include "Point.h"
#include <iostream>
#include <cmath>
using namespace std;

extern float c;
extern int du,oldmy,oldmx;
extern float r,h;

double dot_product(double a[3], double b[3]){
    return (a[0]*b[0]+a[1]*b[1]+a[2]*b[2]);
}

void cross_product(double c[3], double a[3], double b[3]){
    c[0] = a[1]*b[2] - a[2]*b[1];
    c[1] = a[2]*b[0] - a[0]*b[2];
    c[2] = a[0]*b[1] - a[1]*b[0];
}

bool face_adjacency(Face a, Face b){
    int flag = -1;
    
    for (int i = 0; i < FACE_VERTEX_NUM; i++) {
        for (int j = 0; j < FACE_VERTEX_NUM; j++) {
            if (a.p[i].x == b.p[j].x && a.p[i].y == b.p[j].y && a.p[i].z == b.p[j].z)
                flag++;
        }
    }
    
    if (flag == 1) {
        return true;
    }
    return false;
}


double * define_plain(Point a, Point b, Point c){
    
    static double coeffs[4];
    double v1x, v1y, v1z, v2x, v2y, v2z;
    v1x = b.x - a.x;
    v1y = b.y - a.y;
    v1z = b.z - a.z;
    if (CLOCKWISE) {
        v2x = b.x - c.x;
        v2y = b.y - c.y;
        v2z = b.z - c.z;
    } else{
        v2x = c.x - b.x;
        v2y = c.y - b.y;
        v2z = c.z - b.z;
    }
    
    coeffs[0] = v1y*v2z-v1z*v2y;
    coeffs[1] = v1z*v2x-v1x*v2z;
    coeffs[2] = v1x*v2y-v1y*v2x;
    coeffs[3] = -(coeffs[0]*a.x + coeffs[1]*a.y + coeffs[2]*a.z);
    
    return coeffs;
}

double sign(double * plain, Point p){
    double val;
    val = plain[0] * p.x + plain[1] * p.y + plain[2] * p.z + plain[3];
    return val;
}

double * vector(Point a, Point b){
    static double vec[3];
    vec[0] = a.x - b.x;
    vec[1] = a.y - b.y;
    vec[2] = a.z - b.z;
    return vec;
}

bool same_point(Point a, Point b){
    if ((a.x == b.x) && (a.y == b.y) && (a.z == b.z)) {
        return true;
    } else
        return false;
}

double * plain_intersection_vector(double * a, double * b){
    static double vector[3];
    double vec1[3], vec2[3];
    for (int i = 0; i < 3; i++) {
        vec1[i] = a[i];
        vec2[i] = b[i];
    }
    cross_product(vector, vec1, vec2);
    return vector;
}

double * plain_intersection_point(double * a, double * b){
    static double point[3];
    point[0]=0;
    point[2]=(b[2]*a[4]-a[2]*b[4])/(a[2]*b[3]-a[3]*b[2]);
    point[1]=-(a[3]*point[2]+a[4])/a[2];
    return point;
}

bool edge_in_face(Edge e, Face f){
    Point p1 = e.p[0];
    Point p2 = e.p[1];
    int count = 0;
    for (int i = 0; i < FACE_VERTEX_NUM; i++) {
        if (same_point(p1, f.p[i])) {
            count++;
        }
        if (same_point(p2, f.p[i])) {
            count++;
        }
    }
    if (count == 2) {
        return true;
    }
    return false;
}