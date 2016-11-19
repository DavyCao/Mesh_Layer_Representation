//
//  Graph.h
//  CG_Project
//
//  Created by Yi Cao on 10/28/15.
//  Copyright © 2015 Yi Cao. All rights reserved.
//

#ifndef Graph_h
#define Graph_h

#include "def.h"
#include "Point.h"
#include "Edge.h"
#include "Face.h"
#include "calc.h"
#include <iostream>
using namespace std;

class Graph{
public:
    Point p[GRAPH_MAX_VERTEX_NUM];
    bool edge[10000][10000];
    bool acyclic = true;
};

#endif /* Graph_h */

bool point_in_face(Point a, Face b);
bool face_overlap(Face a, Face b);
void create_graph();
int incoming_arcs(int i);
int outgoing_arcs(int i);
int max_outgoing_arc();
void rearrange_layers();