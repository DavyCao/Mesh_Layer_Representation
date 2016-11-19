//
//  read_draw.cpp
//  Graphics_Project
//
//  Created by Yi Cao on 10/27/15.
//  Copyright © 2015 Yi Cao. All rights reserved.
//

#include "read_create.h"
#include "def.h"
#include "calc.h"
#include <cmath>

#include <GLUT/GLUT.h>

extern Point vertex[POINT_NUM];
extern Face face[FACE_NUM];
extern Edge contour_edge[EDGE_NUM];
extern Edge project_contour_edge[EDGE_NUM];
extern Face project_face[FACE_NUM];
extern Point project_contour_vertices[POINT_NUM];
extern double view[3];

extern double depth;
extern double average_depth;
double color[1000];


int pcount = 0;
int fcount = 0;
int fcount_invisible = 0;


//Read .obj file
void readfile(char const * filename){
    
    cout << "Obj file read!" << endl;
    ifstream ifs(filename);
    string str, str1, str2, str3;

    int a=0, b=0, c=0, d=0, i=0;
    
    double x=0, y=0, z=0;
    
    while (ifs >> str){
        if (str=="v"){
            ifs >> str;
            x = atof(str.c_str());
            ifs >> str;
            y = atof(str.c_str());
            ifs >> str;
            z = atof(str.c_str());
            //Log average_depth
            average_depth += z;
            //Log depth
            if (z < depth) {
                depth = z;
            }
            vertex[pcount].Pset_values(x, y, z);
            vertex[pcount].id = pcount + 1;
            vertex[pcount].exist = true;
            pcount++;
        }
        
        if (str=="f" && FACE_VERTEX_NUM == 3){
            ifs >> str;
            a = abs(atoi(str.c_str()));
            for (i = 0; i < str.length(); i++){
                if (str[i]=='/'){
                    a = abs(atoi(str.substr(0,i).c_str()));
                }
            }
            ifs >> str;
            b = abs(atoi(str.c_str()));
            for (i = 0; i < str.length(); i++){
                if (str[i]=='/'){
                    b = abs(atoi(str.substr(0,i).c_str()));
                }
            }
            ifs >> str;
            c = abs(atoi(str.c_str()));
            for (i = 0; i < str.length(); i++){
                if (str[i]=='/'){
                    c = abs(atoi(str.substr(0,i).c_str()));
                }
            }
            face[fcount].Fset_values3(vertex[a-1], vertex[b-1], vertex[c-1]);
            face[fcount].Fset_normal(vertex[a-1], vertex[b-1], vertex[c-1]);
            if (dot_product(face[fcount].normal, view) >= 0){
                face[fcount].visible = false;
                fcount_invisible += 1;
            }
            face[fcount].exist = true;
            face[fcount].id = fcount + 1;
            fcount++;
        }
        
        if (str=="f" && FACE_VERTEX_NUM == 4){
            ifs >> str;
            a = abs(atoi(str.c_str()));
            for (i = 0; i < str.length(); i++){
                if (str[i]=='/'){
                    a = abs(atoi(str.substr(0,i).c_str()));
                }
            }
            ifs >> str;
            b = abs(atoi(str.c_str()));
            for (i = 0; i < str.length(); i++){
                if (str[i]=='/'){
                    b = abs(atoi(str.substr(0,i).c_str()));
                }
            }
            ifs >> str;
            c = abs(atoi(str.c_str()));
            for (i = 0; i < str.length(); i++){
                if (str[i]=='/'){
                   c = abs(atoi(str.substr(0,i).c_str()));
                 }
            }
            ifs >> str;
            d = abs(atoi(str.c_str()));
            for (i = 0; i < str.length(); i++){
                if (str[i]=='/'){
                    d = abs(atoi(str.substr(0,i).c_str()));
                }
            }
            face[fcount].Fset_values4(vertex[a-1], vertex[b-1], vertex[c-1], vertex[d-1]);
            face[fcount].Fset_normal(vertex[a-1], vertex[b-1], vertex[c-1]);

            if (dot_product(face[fcount].normal, view) >= 0){
                face[fcount].visible = false;
                fcount_invisible += 1;
            }
            face[fcount].exist = true;
            face[fcount].id = fcount + 1;
            fcount++;
        }
    }
    average_depth /= pcount;
    
    cout << "Vertex number: " << pcount << endl;
    cout << "Face number: " << fcount << endl;
    ifs.close();
}

int sign (double val){
    if (val < average_depth) {
        return -1;
    } else if (val == average_depth){
        return 0;
    } else {
        return 1;
    }
}


bool contour_exist (Point a, Point b){
    for (int i = 0; i < EDGE_NUM; i++) {
        if (!contour_edge[i].exist) {
            break;
        }
        if ((same_point(contour_edge[i].p[0], a) && same_point(contour_edge[i].p[1], b)) || (same_point(contour_edge[i].p[0], b) && same_point(contour_edge[i].p[1], a) )) {
            return true;
        }
    }
    return false;
}


//Type 3: Contour
void create_contour_edges(void){
    int count = 0;
    int v[2];
    for (int i = 0; i < FACE_NUM; i++){
        if (!face[i].exist) {
            break;
        }

        if (face[i].visible) {
            for (int j = 0; j < FACE_NUM; j++){
                if (!face[j].exist) {
                    break;
                }
                if (face_adjacency(face[i], face[j]) && !face[j].visible) {
                    int index = 0;
                    for (int k = 0; k < FACE_VERTEX_NUM; k++) {
                        for (int l = 0; l < FACE_VERTEX_NUM; l++) {
                            if (face[i].p[k].x == face[j].p[l].x && face[i].p[k].y == face[j].p[l].y && face[i].p[k].z == face[j].p[l].z){
                                v[index]=k;
                                index=1;
                            }
                        }
                    }
                    if (!contour_exist(face[i].p[v[0]], face[i].p[v[1]])) {
                        contour_edge[count].Eset_values(face[i].p[v[0]], face[i].p[v[1]]);
                        contour_edge[count].exist = true;
                        contour_edge[count].id = count + 1;
                        count++;
                    }
                }
            }
        }
    }
    cout << "Contour edges: "  << count << endl;
}

//Type 4: Projected Contour
void create_project_contour_edges(void){
    int count = 0;
    for (int i = 0; i < EDGE_NUM; i++){
        if (!contour_edge[i].exist) {
            break;
        }
        project_contour_edge[count].Eset_values(contour_edge[i].p[0], contour_edge[i].p[1]);
        if (view[0]!=0) {
            project_contour_edge[count].p[0].x = depth;
            project_contour_edge[count].p[1].x = depth;
        } else if (view[1]!=0){
            project_contour_edge[count].p[0].y = depth;
            project_contour_edge[count].p[1].y = depth;
        } else{
            project_contour_edge[count].p[0].z = depth;
            project_contour_edge[count].p[1].z = depth;
        }

        project_contour_edge[count].exist = true;
        project_contour_edge[count].id = count + 1;
        count++;
    }
    cout << "Project Contour Edges: "  << count << endl;
}


//Type 5: Projected Faces
void create_project_faces(void){
    int count = 0;
    for (int i = 0; i < FACE_NUM; i++){
        if (!face[i].exist) {
            break;
        }
        if (FACE_VERTEX_NUM == 3)
            project_face[count].Fset_values3(face[i].p[0],face[i].p[1],face[i].p[2]);
        if (FACE_VERTEX_NUM == 4)
            project_face[count].Fset_values4(face[i].p[0],face[i].p[1],face[i].p[2],face[i].p[3]);
        for (int j = 0; j < FACE_VERTEX_NUM; j++) {
            if (view[0] != 0) {
                project_face[count].p[j].x = face[count].layer * (-5);
            } else if (view[1] != 0){
                project_face[count].p[j].y = face[count].layer * (-5);
            } else{
                project_face[count].p[j].z = face[count].layer * (-5);
            }

        }
        project_face[count].exist = true;
        project_face[count].id = count + 1;
        count++;
    }
    cout << "Project Faces: "  << count << endl;
}

void draw_edge(Edge e){
    glVertex3d(e.p[0].x, e.p[0].y, e.p[0].z);
    glVertex3d(e.p[1].x, e.p[1].y, e.p[1].z);
}

void draw_vector_edge(Edge e){
    for (int i = 0; i < FACE_NUM; i++) {
        if (!face[i].exist) {
            break;
        }
        if (edge_in_face(e, face[i]) && face[i].visible) {
            if (view[0] != 0) {
                e.p[0].x = project_face[i].layer * (-15);
                e.p[1].x = project_face[i].layer * (-15);
            } else if (view[1] != 0) {
                e.p[0].y = project_face[i].layer * (-15);
                e.p[1].y = project_face[i].layer * (-15);
            } else {
                e.p[0].z = project_face[i].layer * (-15);
                e.p[1].z = project_face[i].layer * (-15);
            }
            glVertex3d(e.p[0].x, e.p[0].y, e.p[0].z);
            glVertex3d(e.p[1].x, e.p[1].y, e.p[1].z);
            continue;
        }
    }
}

void draw_face(Face f){
    for (int i = 0; i < FACE_VERTEX_NUM; i++) {
        glVertex3d(f.p[i].x, f.p[i].y, f.p[i].z);
    }
}

//Generate color for faces
void init_color(void){
    for (int i = 0; i < 1000; i++) {
        color[i] = rand() * 1.0 / RAND_MAX;
    }
}
