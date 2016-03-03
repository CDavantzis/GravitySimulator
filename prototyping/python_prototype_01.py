''' Python Prototype To Outline How The C++ Code Will be Written '''
from math import sqrt, atan2, degrees
from itertools import permutations

G = 6.674e-11

def Force(m1,m2,r):
    return {"Fg":G*m1*m2/(r**2),
            "a1":G*m2/(r**2),
            "a2":G*m1/(r**2)}

def Distance(x1,y1,x2,y2):
    return {"r":sqrt((x2-x1)**2+(y2-y1)**2),
            "theta": degrees(atan2(y2-y1,x2-x1))}

class Body():
    def __init__(self,mass,Cx=0,Cy=0,Vx=0,Vy=0,Fx=0,Fy=0):
        self.mass = mass
        self.Cx = Cx
        self.Cy = Cy
        self.Vx = Vx 
        self.Vy = Vy
        self.Fx = Fx 
        self.Fy = Vy
    
    def __repr__(self):
        return str((self.Cx,self.Cy))

    def update(self,dt=.5):
        self.Vx += dt * self.Fx / self.mass
        self.Vy += dt * self.Fy / self.mass
        self.Cx += dt * self.Vx
        self.Cy += dt * self.Vy
        self.zeroForces()

    def distanceTo(self, other):
        dx = self.Cx-other.Cx
        dy = self.Cy-other.Cy
        r  = sqrt(dx**2+dy**2)
        return dx, dy, r

    def zeroForces(self):
        self.Fx = 0
        self.Fy = 0

    def addForces(self, other):
        dx, dy, r = self.distanceTo(other)
        F = G*self.mass*other.mass/(r**2)
        self.Fx += F * dx / r
        self.Fy += F * dy / r


class Simulation():
    def __init__(self,*bodies):
        self.bodies = list(bodies)

    def __str__(self):
        return str(self.bodies)

class TwoBody(Simulation):
    #https://en.wikipedia.org/wiki/Two-body_problem
    #https://en.wikipedia.org/wiki/Gravitational_two-body_problem
    #http://www.astro.cornell.edu/~berthoud/alpsat/chapter4a.html
    #http://scienceworld.wolfram.com/physics/Two-BodyProblem.html
    def __addForces(self):
        n = len(self.bodies)
        for i,j in iter((i,j) for i in range(n) for j in range(n) if i != j):
            self.bodies[i].addForces(self.bodies[j])

    def step(self):
        self.__addForces()
        for body in self.bodies:
            body.update()

class NBody_BruteForce(Simulation):
    def __addForces(self):
        n = len(self.bodies)
        for i,j in iter((i,j) for i in range(n) for j in range(n) if i != j):
            self.bodies[i].addForces(self.bodies[j])

    def step(self):
        self.__addForces()
        for body in self.bodies:
            body.update()

class NBody_BarnesHut(Simulation):
    pass

class NBody_Fastmultipole(Simulation):
    pass

class NBody_ParticalMesh(Simulation):
    pass

class NBody_P3M(Simulation):
    pass

class NBody_PMTree(Simulation):
    pass

class NBody_MeanField(Simulation):
    pass 

B1 = Body(2000,0,0)
B2 = Body(10,100,0,Vx=0,Vy=14)






