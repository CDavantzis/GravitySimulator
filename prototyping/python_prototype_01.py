''' Python Prototype To Outline How The C++ Code Will be Written '''

# Math & Science Research and Sources
# http://scienceworld.wolfram.com/physics/topics/CelestialMechanics.html
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
# http://astrowww.phys.uvic.ca/~tatum/celmechs.html
# http://web.mit.edu/8.01t/www/materials/modules/chapter25.pdf
# https://en.wikipedia.org/wiki/Orbital_mechanics
# Programming Research & Sources
# Better: https://github.com/bengolder/python-geometry/tree/master/geometry
# Simple: http://hplgit.github.io/primer.html/doc/pub/class/._class-readable004.html#sec:class:Vec2D
# http://astronomy.stackexchange.com/questions/7806/exercise-2d-orbital-mechanics-simulation-python
# https://en.wikipedia.org/wiki/Celestial_mechanics
# http://www.cs.cmu.edu/~scandal/alg/nbody.html
# http://www.luc.edu/faculty/dslavsk/courses/phys301/classnotes/celestialmechanics.pdf
# http://physics.princeton.edu/~fpretori/Nbody/intro.htm
# https://en.wikipedia.org/wiki/Cartesian_coordinate_system
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
	def __init__(self,mass,x,y,z):
		self.__mass = mass

	m  = property(lambda self: self.__mass)
	mu = property(lambda self: G*self.mass)


class TwoBodySimulation():
	#https://en.wikipedia.org/wiki/Gravitational_two-body_problem
	#https://en.wikipedia.org/wiki/Two-body_problem
	#https://en.wikipedia.org/wiki/Kepler_orbit
	#https://en.wikipedia.org/wiki/Kepler_problem
	#https://en.wikipedia.org/wiki/Equation_of_the_center
	#http://www.astro.cornell.edu/~berthoud/alpsat/chapter4a.html
	#https://en.wikipedia.org/wiki/Jacobi_coordinates
	#http://scienceworld.wolfram.com/physics/Two-BodyProblem.html

	def __init__(self,B1,B2):
		self.bodies = [B1,B2]
		self.time   = 0






