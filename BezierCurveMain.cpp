/*
 * BezierCurveMain.cpp
 *
 *  Created on: Aug 4, 2012
 *      Author: letrungkien7
 */
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <GL/glut.h>
#include <eigen3/Eigen/Core>

#include "BeizierCurve.h"

#define MAXPOINTS 33
#define PI 3.1415
#define STEP 1
#define NUMCYCLEPOINTS 20

using namespace std;
using namespace Eigen;
GLsizei wh = 1000;
GLsizei ww = 1000;

GLsizei clip_w = 1000;
GLsizei clip_h = 1000;

BeizierCurve bCurve;
vector<BeizierCurve> cycle;
Point origin;
double radius;


void InitCircle(const Point &origin, double radius, int num = 20){
	double angle;
	vector<Point> points(num);
	cycle.resize(num);
	for(int i=0; i<num; ++i){
		angle = (double)i/num *2*PI;
		points[i]<<radius*cos(angle), radius*sin(angle);
		points[i]+=origin;
	}
	for(int i=0; i<NUMCYCLEPOINTS-1; i+=2){
		for(int j= 0; j< 3; j++){
			cycle[i].Add(points[(i+j)%NUMCYCLEPOINTS]);
		}
		cycle[i].Calculate(5);
	}
}

void DrawCircle(){
	glColor3f(0,0,1);
	for(int i=0; i<20; ++i){
		cycle[i].Draw();
		cycle[i].Outline();
	}

}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0,1.0,1.0,1.0);
	bCurve.Outline();
	bCurve.Draw();
	DrawCircle();
	glFlush();
}

void reshape(int w, int h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-(GLdouble)clip_w/2.0, (GLdouble)clip_w/2.0,-(GLdouble)clip_h/2.0, (GLdouble)clip_h/2.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouse(int button, int state, int x, int y){
	switch(button){
	case GLUT_LEFT_BUTTON:
		if(state==GLUT_DOWN && bCurve.N()<MAXPOINTS){
			bCurve.Add((double)(x-ww/2),(double)(wh/2-y));
			bCurve.Calculate(1000);
		}
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void keyboard(unsigned char c, int x, int y){
	switch(c){
	case 27:
		exit(1);
		break;
	case 'r':
		bCurve.Reset();
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void initialize(){
	bCurve.Initialize();
	origin << 0,0;
	radius = 400;
	InitCircle(origin, radius);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ww, wh) ;
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);

	initialize();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape) ;
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop() ;

	return 0;
}
