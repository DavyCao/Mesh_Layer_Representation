//
//  Graph.cpp
//  CG_Project
//
//  Created by Yi Cao on 10/28/15.
//  Copyright © 2015 Yi Cao. All rights reserved.
//

#include "Graph.h"

extern int layer;
extern double depth;
extern double view[3];
extern Face face[FACE_NUM];
extern Face project_face[FACE_NUM];
extern Graph g;

bool point_in_face(Point p, Face f){
    Point a;
    Face b;
    double temp1[3];
    double temp2[3];
    double vec1[3],vec2[3],vec3[3];

    a.Pset_values(p.x, p.y, depth);
    if (FACE_VERTEX_NUM == 3) {
        b.Fset_values3(f.p[0], f.p[1], f.p[2]);
    }
    if (FACE_VERTEX_NUM == 4) {
        b.Fset_values4(f.p[0], f.p[1], f.p[2], f.p[3]);
    }
    for (int i = 0; i < FACE_VERTEX_NUM; i++) {
        if (view[0] != 0) {
            b.p[i].x = depth;
        } else if (view[1] != 0){
            b.p[i].y = depth;
        } else {
            b.p[i].z = depth;
        }
    }

    for (int i = 0; i < FACE_VERTEX_NUM; i++) {
        for (int j = 0; j < 3; j++) {
            vec1[j] = vector(b.p[(i+1)%FACE_VERTEX_NUM], b.p[i])[j];
            vec2[j] = vector(a, b.p[i])[j];
            vec3[j] = vector(b.p[(i+2)%FACE_VERTEX_NUM], b.p[i])[j];
        }
        
        cross_product(temp1, vec1, vec2);
        cross_product(temp2, vec1, vec3);
        
        if (dot_product(temp1, temp2) < 0)
            return false;

    }
    return true;
}

bool face_overlap(Face a, Face b){
    Point p1,p2;
    double p1x,p1y,p1z,p2x,p2y,p2z;
    for (int i = 0; i < FACE_VERTEX_NUM; i++) {
        p1x += a.p[i].x;
        p1y += a.p[i].y;
        p1z += a.p[i].z;
        p2x += b.p[i].x;
        p2y += b.p[i].y;
        p2z += b.p[i].z;
    }
    p1x /= FACE_VERTEX_NUM;
    p1y /= FACE_VERTEX_NUM;
    p1z /= FACE_VERTEX_NUM;
    p2x /= FACE_VERTEX_NUM;
    p2y /= FACE_VERTEX_NUM;
    p2z /= FACE_VERTEX_NUM;
    
    p1.Pset_values(p1x, p1y, p1z);
    p2.Pset_values(p2x, p2y, p2z);
    
    if (point_in_face(p1,b) || point_in_face(p2,a)) {
        return true;
    }
    return false;
}

//Create the Adjacency-Occlusion Graph
void create_graph(){
//    cout << time(nullptr) << endl;
    for (int i = 0; i < FACE_NUM; i++) {
        if (!face[i].exist) {
            break;
        }
        for (int j = 0; j < FACE_NUM; j++) {
            if (!face[j].exist) {
                break;
            }
            if (face_overlap(face[i], face[j]) && (face[i].visible) && (face[j].visible) && (face[i].layer != face[j].layer)) {
                if (view[0] != 0) {
                    if ((face[i].p[0].x > face[j].p[0].x)) {
                        g.edge[face[i].layer-1][face[j].layer-1]=true;
                    }
                } else if (view[1] != 0) {
                    if ((face[i].p[0].y > face[j].p[0].y)) {
                        g.edge[face[i].layer-1][face[j].layer-1]=true;
                    }
                } else {
                    if ((face[i].p[0].z > face[j].p[0].z)) {
                        g.edge[face[i].layer-1][face[j].layer-1]=true;
                    }
                }
                
            }
        }
    }
//    cout << time(nullptr) << endl;

}

int outgoing_arcs(int i){
    int arcs = 0;
    for (int j = 0; j < layer; j++) {
        arcs += g.edge[i][j];
    }
    return arcs;
}

int incoming_arcs(int i){
    int arcs = 0;
    for (int j = 0; j < layer; j++) {
        arcs += g.edge[j][i];
    }
    return arcs;
}

int max_outgoing_arc(){
    int max = 0, max_layer = 0, layer_out;
    for (int i = 0; i < layer; i++) {
        layer_out = outgoing_arcs(i);
        if (layer_out > max){
            max = layer_out;
            max_layer = i;
        }
    }
    return max_layer;
}

void rearrange_layers(){
    int new_layer_num = 1;
    for (int i = 0; i < FACE_NUM; i++) {
        if (!face[i].exist) {
            break;
        }
        if (face[i].visible) {
            if (max_outgoing_arc() == face[i].layer-1) {
                project_face[i].layer = 1;
            }
            for (int k = 0; k < layer; k++) {
                if (incoming_arcs((face[i].layer-1)) == k) {
                    new_layer_num = max(new_layer_num, 1+k);
                    project_face[i].layer = 1+k;
                    for (int j = 0; j < FACE_VERTEX_NUM; j++) {
                        if (view[0] != 0) {
                            project_face[i].p[j].x = project_face[i].layer * (-5);
                        } else if (view[1] != 0) {
                            project_face[i].p[j].y = project_face[i].layer * (-5);
                        } else {
                            project_face[i].p[j].z = project_face[i].layer * (-5);
                        }
                    }
                }
            }
        }
    }
    cout << "Final Layer: " << new_layer_num << endl;
}