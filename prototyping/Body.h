#ifndef BODY_H
#define BODY_H

#include <vector>
#include <cmath>

#define G = 6.67e-11



class Body{
private:
	double mass;
	double radius;

	//double rotationTime;

	double x, y;	//position
	double vx, vy;	//velocity
	double fx, fy;	//force



public:
	Body(double mass, 
		double radius, 
		double x, double y
		double vx, double vy);

	void update(double dt);

	double distanceTo(Body b);

	void resetForce();

	void addForce(Body b);


};

#endif



