//
//  mouse_action.cpp
//  CG_Project
//
//  Created by Yi Cao on 10/28/15.
//  Partly retrived from http://blog.csdn.net/yhb5566/article/details/7714716
//

#include <GLUT/glut.h>

extern int du,oldmy,oldmx;
extern float r,h;


void Mouse(int button, int state, int x, int y){
    if(state==GLUT_DOWN && button == GLUT_LEFT_BUTTON)
        oldmx=x,oldmy=y;
}

void onMouseMove(int x,int y){
    du += x - oldmx;
    h += y - oldmy ;
    oldmx=x;
    oldmy=y;
}
