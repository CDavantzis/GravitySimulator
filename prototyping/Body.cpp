#include "Body.h"



Body::Body(double mass, 
		double radius, 
		double x, double y 
		double vx = 0, double vy = 0): mass(mass), radius(radius), x(x), y(y), vx(vx), vy(vy){


}



void Body::update(double dt){
//	f = ma; a = dv/dt; f = m*dv/dt; dv = dt*f/m; v = v0 +dv; 
//`	v = ds / dt; ds = dt * v; s = s0 + ds = s0 + dt *v;

	
		vx += dt * fx / mass;
		vy += dt * fy / mass;
		x += dt * vx;
		y += dt * vy;

}

double Body::distanceTo(Body b){
	double dx = x - b.x;
	double dy = y - b.x;
	return sqrt(dx*dx + dy*dy);
	
}

void Body::resetforce(){
	fx = 0;
	fy = 0;
}



//Maybe we could just load array of bodies stored nicely and run a code through it
void Body::addForce(Body b){

	double dist = this.distanceTo(b);

	double F = (G * mass * b.mass) / (dist*dist);
	
	fx += F * (b.x - x) / dist;
	fy += F * (b.y - y) / dist;

}






