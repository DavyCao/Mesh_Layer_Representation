//
//  read_draw.h
//  Graphics_Project
//
//  Created by Yi Cao on 10/27/15.
//  Copyright © 2015 Yi Cao. All rights reserved.
//

#ifndef read_draw_h
#define read_draw_h

#include <fstream>
#include <string>
#include "Face.h"
#include "Point.h"
#include "Edge.h"
#include "Graph.h"
#include "calc.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

void readfile(char const * filename);
void create_contour_edges(void);
void create_project_contour_edges(void);
void create_project_faces(void);


void init_color(void);
void draw_edge(Edge e);
void draw_vector_edge(Edge e);
void draw_face(Face f);
void display(void);

#endif /* read_draw_h */
