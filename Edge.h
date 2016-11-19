//
//  Edge.h
//  CG_Project
//
//  Created by Yi Cao on 10/27/15.
//  Copyright © 2015 Yi Cao. All rights reserved.
//

#ifndef Edge_h
#define Edge_h


#include "Point.h"

class Edge{
public:
    Point p[2];
    int id;
    bool contour = true;
    bool exist = false;
    void Eset_values(Point, Point);
    int count = 0;
};

#endif /* Edge_h */
