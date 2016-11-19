//
//  layer.h
//  CG_Project
//
//  Created by Yi Cao on 11/29/15.
//  Copyright © 2015 Yi Cao. All rights reserved.
//

#ifndef layer_h
#define layer_h

#include "Face.h"
#include "Point.h"
#include "Edge.h"
#include "calc.h"
#include <iostream>
using namespace std;

bool not_contour_edge(Edge a);

//For Face Layering
int propagation(void);
void face_layer(int ver);
void assign_layer_id(void);
void general_label(void);

#endif /* layer_h */
