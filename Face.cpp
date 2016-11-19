//
//  Face.cpp
//  Graphics_Project
//
//  Created by Yi Cao on 10/27/15.
//  Copyright © 2015 Yi Cao. All rights reserved.
//

#include "def.h"
#include "Face.h"

void Face::Fset_values3(Point a, Point b, Point c){
    
    p[0].Pset_values(a.x, a.y, a.z);
    p[1].Pset_values(b.x, b.y, b.z);
    p[2].Pset_values(c.x, c.y, c.z);
    
}

void Face::Fset_values4(Point a, Point b, Point c, Point d){
    
    p[0].Pset_values(a.x, a.y, a.z);
    p[1].Pset_values(b.x, b.y, b.z);
    p[2].Pset_values(c.x, c.y, c.z);
    p[3].Pset_values(d.x, d.y, d.z);
    
}

void Face::Fset_normal(Point a, Point b, Point c){
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
    
    normal[0] = v1y*v2z-v1z*v2y;
    normal[1] = v1z*v2x-v1x*v2z;
    normal[2] = v1x*v2y-v1y*v2x;
}