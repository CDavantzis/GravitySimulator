#include <vector>
#include <cmath>

#define G = 6.67e-11



class Body{
private:
	double mass;
	double radius;
	//double rotationTime;

	std::vector<double> position;
	std::vector<double> velocity;
	std::vector<double> force;



public:
	Body(double mass, 
		double radius, 
		std::vector<double> position, 
		std::vector<double> velocity);

	void update(double dt);

	double distanceTo(Body b);

	void resetForce();

	void addForce(Body b);


};