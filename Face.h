//
//  Face.h
//  Graphics_Project
//
//  Created by Yi Cao on 10/26/15.
//  Copyright © 2015 Yi Cao. All rights reserved.
//


#ifndef Face_h
#define Face_h

#include "Point.h"

class Face{
public:
    Point p[4];
    int id;
    int layer = -1;
    double normal[3];
    bool visible = true;
    bool visited = false;
    bool exist = false;
    void Fset_values3(Point, Point, Point);
    void Fset_values4(Point, Point, Point, Point);
    void Fset_normal(Point, Point, Point);
};

#endif /* Face_h */