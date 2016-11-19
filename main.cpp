//
//  Point.cpp
//  Graphics_Project
//
//  Created by Yi Cao on 10/27/15.
//  Partly retrived from http://blog.csdn.net/yhb5566/article/details/7714716
//


#include <GLUT/glut.h>
#include <cmath>
#include <iostream>
#include "def.h"
#include "mouse_action.h"
#include "read_create.h"
#include "layer.h"


Face face[FACE_NUM];
Face project_face[FACE_NUM];
Edge contour_edge[EDGE_NUM];
Edge project_contour_edge[EDGE_NUM];
Point project_contour_vertices[POINT_NUM];
Point vertex[POINT_NUM];
double depth = 0;
double average_depth = 0;
Graph g;

//For deer.obj
//double view[3]={0,0,-1};
//char const * filename = "deer.obj";
//float r=30.0f,h=0.0f;
//double coeff[6]={0,10,0,0,1,0};

//For M69UT.obj
double view[3]={0,0,-1};
char const * filename = "M69UT.obj";
float r=300.0f,h=0.0f;
double coeff[6]={0,0,0,0,1,0};

//Type 1 for Face; 2 for Mesh; 3 for Contour; 4 for Viewmap; 5 for Constant Visibility Region; 6 for Final Layer; 7 for Vector Representation of Each Layer
int type = 6;
bool seeback = true;

float c=Pi/180;
int du=90,oldmy=-1,oldmx=-1;


void reshape(int w,int h){
    glViewport( 0, 0, w, h );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(75.0f, (float)w/h, 1.0f, 1000.0f);
    glMatrixMode( GL_MODELVIEW );
}


int main(int argc, char *argv[]){
    
    readfile(filename);
    create_contour_edges();
    create_project_contour_edges();
    
    if (type >= 5) {
        general_label();
        create_project_faces();
        
        create_graph();
        rearrange_layers();
    }

    init_color();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(500, 500);
    glutCreateWindow(filename);
    
    glEnable(GL_DEPTH_TEST);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);

    glutMouseFunc(Mouse);
    glutMotionFunc(onMouseMove);
    glutMainLoop();
    return 0;
}  
