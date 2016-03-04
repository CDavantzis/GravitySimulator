import math
import numbers


class Vector2D:
    '''
    help from:
        http://hplgit.github.io/primer.html/doc/pub/class/._class-readable004.html#sec:class:Vec2D
        https://github.com/bengolder/python-geometry/blob/master/geometry/vector.py
        https://github.com/bengolder/python-geometry/blob/master/geometry/vector2d.py
    '''
    def __init__(self, x, y):
        self.x = x
        self.y = y

    __abs__ = lambda self: math.sqrt(self.x**2 + self.y**2)                              # Calculate Norm
    __str__ = lambda self: 'Vector2D({0}, {1})'.format(self.x, self.y)                   # String Represitation 
    __eq__  = lambda self, other: self.x == other.x and self.y == other.y                # Check if equal
    __ne__  = lambda self, other: not self.__eq__(other)                                 # Check if not equal
    
    normalized = lambda self:  self * (1 / abs(self))                                    # Normalized Vector 
    
    add_length = lambda self, length: self.normalized() * length + self                  # Add to vector length
    sub_length = lambda self, length: self.Normalize() * -length + self                  # Subtract from vector length
    mul_length = lambda self, other:  self.__class__(self.x * other, self.y*other)       # Scalar Multiplication
    
    add_vector = lambda self, other:  self.__class__(self.x + other.x, self.y + other.y) # Add vectors
    sub_vector = lambda self, other:  self.__class__(self.x - other.x, self.y - other.y) # Subtract vectors
    mul_vector = lambda self, other:  self.x*other.x + self.y*other.y                    # Dot Product

    __mul__ = lambda self, val: self.mul_vector(val) if isinstance(val, self.__class__) else self.mul_length(val)
    __add__ = lambda self, val: self.add_vector(val) if isinstance(val, self.__class__) else self.add_length(val)
    __sub__ = lambda self, val: self.sub_vector(val) if isinstance(val, self.__class__) else self.sub_length(val)
    __div__ = lambda self, val: self.__mul__(val**-1)

    def ZERO(self):
        ''' Zero in place '''
        self.x, self.y = 0,0

class Body():
    '''
    help from:
        https://sites.google.com/a/ucsc.edu/krumholz/teaching-and-courses/ast119_w15/class-11
    '''
    G = 6.674e-11
    def __init__(self,mass,Cx=0,Cy=0,Vx=0,Vy=0,Fx=0,Fy=0):
        self.m = mass
        self.r = Vector2D(Cx,Cy)
        self.f = Vector2D(Fx,Fy)

    _d_from = lambda self, other: abs(self.r - other.r)
    _f_from = lambda self, other: (self.r-other.r)*((self.G*self.m*other.m)/(self._d_from(other)**2))
    _a_from = lambda self, other: self._f_from(other)/(self.m)

    def __str__(self):
        return str(self.r)

class Simulation():
    def __init__(self,*bodies):
        self.bodies = list(bodies)
        
    def __str__(self):
        return str([[b.r.x,b.r.y] for b in self.bodies])

class BruteForce(Simulation):
    def _sum_forces(self):
        n = len(self.bodies)
        for b1,b2 in iter((self.bodies[i],self.bodies[j]) for i in range(n) for j in range(n) if i != j):
            b1.f += b1._f_from(b2)

    def step(self,dt=1):
        self._sum_forces()
        for b in self.bodies:
            a = b.f/b.m
            v = a*dt
            b.r += v*dt
            b.f.ZERO()


b1 = Body(10,100,0)
b2 = Body(100,0,90)
sim = BruteForce(b1,b2)

for i in range(100):
    print sim
    sim.step()

