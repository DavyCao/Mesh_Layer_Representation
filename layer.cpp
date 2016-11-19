//
//  layer.cpp
//  CG_Project
//
//  Created by Yi Cao on 11/29/15.
//  Copyright © 2015 Yi Cao. All rights reserved.
//

#include "layer.h"

extern Edge contour_edge[EDGE_NUM];
extern Face face[FACE_NUM];
extern int pcount;
extern int fcount;
extern int fcount_invisible;

int layer = 1;
int num = 0;

bool not_contour_edge(Edge a){
    for (int i = 0; i < EDGE_NUM; i++) {
        if (contour_edge[i].exist == false) {
            break;
        }
        if ((same_point(a.p[0], contour_edge[i].p[0]) && same_point(a.p[1], contour_edge[i].p[1])) || (same_point(a.p[0], contour_edge[i].p[1]) && same_point(a.p[1], contour_edge[i].p[0]))) {
            return false;
        }
    }
    return true;
}

void face_layer(int ver){//Find faces nearby, and assign the same layer id if the common edge is not contour
    Edge temp;
    int v[2];
    for (int i = 0; i < FACE_NUM; i++) {
        if (face_adjacency(face[ver], face[i]) && face[i].layer == -1 && face[i].visible){//If adjacent face not layered
            int index = 0;
            for (int k = 0; k < FACE_VERTEX_NUM; k++) {
                for (int l = 0; l < FACE_VERTEX_NUM; l++) {
                    if (same_point(face[ver].p[l], face[i].p[k])){
                        v[index]=k;//Record intersection edge's vertices
                        index=1;
                    }
                }
            }
            temp.Eset_values(face[i].p[v[0]], face[i].p[v[1]]);
            if (not_contour_edge(temp)) {
                face[i].layer = layer;
                num++;
                //                cout << "Face: " << i << "; Layer: " << face[i].layer << endl;
                //                cout << num << endl;
            }
        }
    }
}

//Used for finding faces already layered but not visited
int propagation(void){
    for (int i = 0; i < FACE_NUM; i++) {
        if (face[i].layer != -1 && face[i].visited == false)
            return i;
    }
    return -1;
}


void assign_layer_id(void){
    while (1) {
        int target_face_id = propagation();
        if (target_face_id >= 0) {
            face_layer(target_face_id);
        } else{
            break;
        }
        face[target_face_id].visited = true;
    }
}

void general_label(void){
    //    cout << fcount_invisible << endl;
    while (num < (fcount - fcount_invisible)) {// We only label visible faces
        for (int i = 0; i < FACE_NUM; i++) {// Find one face not layered and exit
            if (!face[i].exist) {
                break;
            }
            if (face[i].layer == -1 && face[i].visible){
                face[i].layer = layer;
                //                cout << "Face: " << i << "; Layer: " << face[i].layer << endl;
                num++;
                break;
            }
        }
        assign_layer_id();
        layer++;
    }
    cout << "Face Layered: " << num << "; Total Layers: " << --layer << endl;
}
