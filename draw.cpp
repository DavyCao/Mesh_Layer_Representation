//
//  draw.cpp
//  CG_Project
//
//  Created by Yi Cao on 12/3/15.
//  Partly retrived from http://blog.csdn.net/yhb5566/article/details/7714716
//

#include <GLUT/GLUT.h>
#include "read_create.h"
#include <cmath>
#include "def.h"

extern float c;
extern int du,oldmy,oldmx;
extern float r,h;
extern int type;
extern Point vertex[POINT_NUM];
extern Face face[FACE_NUM];
extern Edge contour_edge[EDGE_NUM];
extern Edge project_contour_edge[EDGE_NUM];
extern Face project_face[FACE_NUM];
extern Point project_contour_vertices[POINT_NUM];
extern bool seeback;
extern double color[1000];
extern double coeff[6];


//Display 3D Model
void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    gluLookAt(r*cos(c*du),  0.5*h, r*sin(c*du), coeff[0], coeff[1], coeff[2], coeff[3], coeff[4], coeff[5]);
    
    //Face
    if (type == 1) {
        glBegin(GL_TRIANGLES);
        for (int i = 0; i < FACE_NUM; i++){
            if ((face[i].visible || seeback)) {
                glColor3d(std::abs(face[i].normal[2]), 0, 0);
                draw_face(face[i]);
            }
        }
    }
    
    //Mesh
    if (type == 2) {
        glColor3d(0,0,1);
        double facex, facey, facez;
        glBegin(GL_LINES);
        for (int i = 0; i < FACE_NUM; i++){
            if (face[i].visible || seeback) {
                for (int j = 0; j < FACE_VERTEX_NUM; j++){
                    glVertex3d(face[i].p[j].x, face[i].p[j].y, face[i].p[j].z);
                    glVertex3d(face[i].p[(j+1)%3].x, face[i].p[(j+1)%3].y, face[i].p[(j+1)%3].z);
                }
                //Draw normal vectors
                //            facex = (face[i].p[0].x + face[i].p[1].x + face[i].p[2].x) / 3;
                //            facey = (face[i].p[0].y + face[i].p[1].y + face[i].p[2].y) / 3;
                //            facez = (face[i].p[0].z + face[i].p[1].z + face[i].p[2].z) / 3;
                //            glVertex3d(facex, facey, facez);
                //            glVertex3d(facex+face[i].normal[0], facey+face[i].normal[1], facez+face[i].normal[2]);
                
                //Test plain function (Same functionalites with 'Draw normal vectors')
                double * coeffs;
                coeffs = define_plain(face[i].p[0], face[i].p[1], face[i].p[2]);
                facex = (face[i].p[0].x + face[i].p[1].x + face[i].p[2].x) / 3;
                facey = (face[i].p[0].y + face[i].p[1].y + face[i].p[2].y) / 3;
                facez = (face[i].p[0].z + face[i].p[1].z + face[i].p[2].z) / 3;
                glVertex3d(facex, facey, facez);
                glVertex3d(facex+coeffs[0], facey+coeffs[1], facez+coeffs[2]);
            }
        }
    }
    
    //Contour
    if (type == 3) {
        glBegin(GL_LINES);
        for (int i = 0; i < EDGE_NUM; i++){
            if (!contour_edge[i].exist) {
                break;
            }
            draw_edge(contour_edge[i]);
        }
    }
    
    //Viewmap
    if (type == 4) {
        glBegin(GL_LINES);
        for (int i = 0; i < EDGE_NUM; i++){
            if (!project_contour_edge[i].exist) {
                break;
            }
            draw_edge(project_contour_edge[i]);
        }
    }
    
    //Constant Visibility Region
    if (type == 5) {
        glBegin(GL_TRIANGLES);
        for (int i = 0; i < FACE_NUM; i++){
            if (face[i].visible) {
                int layer_id = face[i].layer;
                if (layer_id > 0) {
                    glColor3d(color[layer_id+11], color[layer_id+17], color[layer_id+29]);
                    draw_face(face[i]);
                }
                
            }
        }
    }
    
    //Final Layer
    if (type == 6) {
        glBegin(GL_TRIANGLES);
        for (int i = 0; i < FACE_NUM; i++){
            if (face[i].visible) {
                int layer_id = project_face[i].layer;
                glColor3d(color[layer_id+11], color[layer_id+17], color[layer_id+29]);
                draw_face(project_face[i]);
            }
        }
    }
    
    //Vector Layer Representation
    if (type == 7) {
        glBegin(GL_LINES);
        for (int i = 0; i < EDGE_NUM; i++){
            if (!contour_edge[i].exist) {
                break;
            }
            draw_vector_edge(contour_edge[i]);
        }
    }
    
    glEnd();
    glFlush();
    glutSwapBuffers();
}
