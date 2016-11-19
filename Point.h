//
//  Point.h
//  Graphics_Project
//
//  Created by Yi Cao on 10/26/15.
//  Copyright © 2015 Yi Cao. All rights reserved.
//

#ifndef Point_h
#define Point_h
#include "def.h"

class Point{
public:
    double x,y,z;
    int id;
//    int pcv_index;
    bool traversed = false;
//    bool in_pce[POINT_NUM];
    bool exist = false;
    void Pset_values(double, double, double);
};

#endif /* Point_h */
