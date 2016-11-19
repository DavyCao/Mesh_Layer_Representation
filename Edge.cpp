//
//  Edge.cpp
//  CG_Project
//
//  Created by Yi Cao on 10/27/15.
//  Copyright © 2015 Yi Cao. All rights reserved.
//

#include "Edge.h"

void Edge::Eset_values(Point a, Point b){
    p[0].Pset_values(a.x, a.y, a.z);
    p[1].Pset_values(b.x, b.y, b.z);
}