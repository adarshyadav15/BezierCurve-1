/*
 * BeizierCurve.h
 *
 *  Created on: Aug 4, 2012
 *      Author: letrungkien7
 */

#ifndef BEIZIERCURVE_H_
#define BEIZIERCURVE_H_

#include <vector>
#include <cmath>
#include<eigen3/Eigen/Core>
#include <GL/glut.h>
#include<iostream>
using namespace std;
using namespace Eigen;
typedef Vector2d Point;
typedef Vector3d Color;
class BeizierCurve {
public:
	void Add(int x, int y);
	void Add(const Point &p);
	void Draw();
	void Outline();
	void Calculate(int num);
	void Initialize();
	void Reset();
	int N();
private:
	vector<Point> P;
	vector<Point> C;
	void CreateFactorialTable();
	void DrawLines(const vector<Point> &P, const Color &color);
	void DrawPoints(const vector<Point> &P);
	double Bernstein(int n,int i, double t);
};
#endif /* BEIZIERCURVE_H_ */
