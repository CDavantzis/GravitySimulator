''' Python Prototype To Outline How The C++ Code Will be Written '''
from math import sqrt, atan2, degrees

G = 6.674e-11

def Force(m1,m2,r):
    return {"Fg":G*m1*m2/(r**2),
            "a1":G*m2/(r**2),
            "a2":G*m1/(r**2)}

def Distance(x1,y1,x2,y2):
    return {"r":sqrt((x2-x1)**2+(y2-y1)**2),
            "theta": degrees(atan2(y2-y1,x2-x1))}

class Simulation():
	def __init__(self,*bodies):
		self.bodies = list(bodies)
		self.time   = 0

	def __len__(self):
		return len(self.bodies)

	def add_body(self,body):
		self.bodies.append(body)


class Body():
	''' Body Object In N-body Simulation '''
	def __init__(self,mass, rx, ry,):
		self.__mass = mass

	m  = property(lambda self: self.__mass)
	mu = property(lambda self: G*self.mass)


class TwoBodySimulation():


	def __init__(self,B1,B2):
		self.bodies = [B1,B2]
		self.time   = 0






