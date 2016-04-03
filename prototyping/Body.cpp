

#define DIMENTION 2


Body :: Body(double mass, 
		double radius, 
		std::vector<double> position, 
		std::vector<double> velocity){

	this-> mass = mass;
	this-> radius = radius;

	//there has to be a better way to copy vector
	for(int i = 0; i < DIMENTION; i++){
		this-> position[i] = position[i];
		this-> velocity[i] = velocity[i];
	}


}



void Body :: update(double dt){
//	f = ma; a = dv/dt; f = m*dv/dt; dv = dt*f/m; v = v0 +dv; 
//`	v = ds / dt; ds = dt * v; s = s0 + ds = s0 + dt *v;

	for(int i = 0; i < DIMENTION; i++){
		velocity[i] += dt * force[i] / mass;
		position[i] += dt * velocity[i];
	}

double Body :: distanceTo(Body b){
	double d = 0;
	for(int i = 0; i < DIMENTION; i++){
		d += (position[i] - b.position[i])*(position[i] - b.position[i]);
	}
	return sqrt(d);
	
}

void Body :: resetforce(){
	for(int i = 0; i < DIMENTION; i++){
		force[i] = 0;
	}
}



//Maybe we could just load array of bodies stored nicely and run a code through it
void Body :: addForce(Body b){

	double dist = this.distanceTo(b);
	double F = (G * mass * b.mass) / (dist*dist);
	for(int i = 0; i < DIMENTION; i++){
		force[i] += F * (b.position[i] - position[i]) / dist;
	}

}






