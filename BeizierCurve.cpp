/*
 * BeizierCurve.cpp
 *
 *  Created on: Aug 4, 2012
 *      Author: letrungkien7
 */

#include "BeizierCurve.h"

double fac[33];

void BeizierCurve::Add(int x, int y){
	P.push_back(Point(x,y));
}

void BeizierCurve::Add(const Point &p){
	P.push_back(p);
}

void BeizierCurve::DrawLines(const vector<Point> &P, const Color & color){
	glColor3dv(color.data());
	glBegin(GL_LINE_STRIP);
	for(int i=0, n=P.size(); i<n; ++i){
		glVertex2dv(P[i].data());
	}
	glEnd();
}

void BeizierCurve::DrawPoints(const vector<Point> &P){
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(5.0);
	glBegin(GL_POINTS);
	for(int i=0, n=P.size(); i<n; ++i){
		glVertex2dv(P[i].data());
	}
	glEnd();
}

void BeizierCurve::Outline(){
	DrawLines(P,Color(0,1,0));
	DrawPoints(P);
}

void BeizierCurve::Draw(){
	DrawLines(C, Color(1,0,0));
}

void BeizierCurve::Calculate(int num){
	double step,basic,t;
	int icount, jcount;
	C.clear();
	C.resize(num);
	icount =0;
	t=0;
	step = (double)1.0/(num-1);

	for(int i = 0; i< num; ++i, t+=step){
		if((1.0-t)<5e-6)
			t =1.0;
		C[i]<<0.0, 0.0;
		jcount =0;
		for(int j =0, len = P.size(); j< len; ++j){
			basic = Bernstein( len-1, j, t);
			C[icount] += basic*P[jcount];
			jcount++;
		}
		icount ++;
	}
}

void BeizierCurve::CreateFactorialTable(){
	fac[0] = 1.0;
	fac[1] = 1.0;
	fac[2] = 2.0;
	fac[3] = 6.0;
	fac[4] = 24.0;
	fac[5] = 120.0;
	fac[6] = 720.0;
	fac[7] = 5040.0;
	fac[8] = 40320.0;
	fac[9] = 362880.0;
	fac[10] = 3628800.0;
	fac[11] = 39916800.0;
	fac[12] = 479001600.0;
	fac[13] = 6227020800.0;
	fac[14] = 87178291200.0;
	fac[15] = 1307674368000.0;
	fac[16] = 20922789888000.0;
	fac[17] = 355687428096000.0;
	fac[18] = 6402373705728000.0;
	fac[19] = 121645100408832000.0;
	fac[20] = 2432902008176640000.0;
	fac[21] = 51090942171709440000.0;
	fac[22] = 1124000727777607680000.0;
	fac[23] = 25852016738884976640000.0;
	fac[24] = 620448401733239439360000.0;
	fac[25] = 15511210043330985984000000.0;
	fac[26] = 403291461126605635584000000.0;
	fac[27] = 10888869450418352160768000000.0;
	fac[28] = 304888344611713860501504000000.0;
	fac[29] = 8841761993739701954543616000000.0;
	fac[30] = 265252859812191058636308480000000.0;
	fac[31] = 8222838654177922817725562880000000.0;
	fac[32] = 263130836933693530167218012160000000.0;

}

double BeizierCurve::Bernstein(int n, int i, double t){
	double basis;
	double ti; /* t^i */
	double tni; /* (1 - t)^i */

	if (t == 0.0 && i == 0)
		ti = 1.0;
	else
		ti = pow(t, i);

	if (n == i && t == 1.0)
		tni = 1.0;
	else
		tni = pow((1 - t), (n - i));

	basis = (fac[n]/ (fac[n-i]*fac[i])) * ti * tni;
	return basis;
}

void BeizierCurve::Initialize(){
	CreateFactorialTable();
}

int BeizierCurve::N(){
	return P.size();
}

void BeizierCurve::Reset(){
	P.clear();
	C.clear();
}
