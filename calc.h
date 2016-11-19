//
//  calc.h
//  Graphics_Project
//
//  Created by Yi Cao on 10/27/15.
//  Copyright © 2015 Yi Cao. All rights reserved.
//

#ifndef calc_h
#define calc_h

double dot_product(double a[3], double b[3]);
void cross_product(double c[3], double a[3], double b[3]);
bool face_adjacency(Face a, Face b);
double * vector(Point a, Point b);
double * define_plain(Point a, Point b, Point c);
int sign(double * plain, Point p);
bool same_point(Point a, Point b);
double * plain_intersection_vector(double * a, double * b);
double * plain_intersection_point(double * a, double * b);
bool edge_in_face(Edge e, Face f);

#endif /* calc_h */