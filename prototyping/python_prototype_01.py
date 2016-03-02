''' Python Prototype To Outline How The C++ Code Will be Written '''

# Math & Science Research and Sources
# https://en.wikipedia.org/wiki/Gravitational_acceleration
# https://en.wikipedia.org/wiki/Newton%27s_law_of_universal_gravitation
# https://en.wikipedia.org/wiki/Gravitational_two-body_problem
# https://en.wikipedia.org/wiki/Kepler%27s_laws_of_planetary_motion
# https://en.wikipedia.org/wiki/N-body_problem
# https://en.wikipedia.org/wiki/N-body_simulation
# http://physics.tutorvista.com/motion/vector.html
# http://mathinsight.org/vectors_cartesian_coordinates_2d_3d
# http://web.mit.edu/pkrein/Public/Final%20Paper%20UW324.pdf
# http://www.intmath.com/vectors/7-vectors-in-3d-space.php
# http://www.physics.utah.edu/~sid/physics2010/Unit_Vectors.pdf

# Programming Research & Sources
# Better: https://github.com/bengolder/python-geometry/tree/master/geometry
# Simple: http://hplgit.github.io/primer.html/doc/pub/class/._class-readable004.html#sec:class:Vec2D

from math import sqrt, atan2, degrees

G = 6.674e-11

def Force(m1,m2,r):
    return {"Fg":G*m1*m2/(r**2),
            "a1":G*m2/(r**2),
            "a2":G*m1/(r**2)}

def Distance(x1,y1,x2,y2):
    return {"r":sqrt((x2-x1)**2+(y2-y1)**2),
            "theta": degrees(atan2(y2-y1,x2-x1))}

class Point():
	''' Point Class'''
	pass

class Vector():
	''' Vector Class'''
	pass

class Body():
	''' Body Object In N-body Simulation '''
	pass
 
class Simulation():
	''' Plane Class '''
	def __init__(self,*bodies):
		self.bodies = list(bodies)
		self.time   = 0

	def __len__(self):
		return len(self.bodies)

	def add_body(self,body):
		self.bodies.append(body)

	def step_foward(self):
		#make calculations
		self.time += 1







