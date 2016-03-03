'''
Citation: 
Mostly Taken From
https://github.com/bengolder/python-geometry
'''

class Base(object):
    @property
    def length(self):
        """get the vector length / amplitude
        """
        # only calculate the length if asked to.
        return math.sqrt(sum(n**2 for n in self))

    def normalized(self):
        """just returns the normalized version of self without editing self in
        place.
        """
        return self * (1 / self.length)

    def toLength(self, number):
        """Get a parallel vector with the input amplitude."""
        # depends on normalized() and __mul__
        # create a vector as long as the number
        return self.normalized() * number

    def __iter__(self):
        """For iterating, the vectors coordinates are represented as a tuple."""
        return self.coords.__iter__()

    def dot(self, other):
        """Gets the dot product of this vector and another.
        """
        return sum((p[0] * p[1]) for p in zip(self, other))

    def __add__(self, other):
        """we want to add single numbers as a way of changing the length of the
        vector, while it would be nice to be able to do vector addition with
        other vectors.
        """
        if isinstance(other, numbers.Number):
            # then add to the length of the vector
            # multiply the number by the normalized self, and then
            # add the multiplied vector to self
            return self.normalized() * other + self
        elif isinstance(other, self.__class__):
            # add all the coordinates together
            # there are probably more efficient ways to do this
            return self.__class__(*(sum(p) for p in zip(self, other)))
        else:
            raise TypeError(
                    "unsupported operand (+/-) for types %s and %s" % (
                        self.__class__, type(other)))

    def __sub__(self, other):
        """Subtract a vector or number
        """
        return self.__add__(other * -1)

    def __mul__(self, other):
        """if with a number, then scalar multiplication of the vector,
            if with a Vector, then dot product, I guess for now, because
            the asterisk looks more like a dot than an X.
            >>> v2 = Vector3d(-4.0, 1.2, 3.5)
            >>> v1 = Vector3d(2.0, 1.1, 0.0)
            >>> v2 * 1.25
            Vector3d(-5.0, 1.5, 4.375)
            >>> v2 * v1 #dot product
            -6.6799999999999997
        """
        if isinstance(other, numbers.Number):
            # scalar multiplication for numbers
            return self.__class__( *((n * other) for n in self))

        elif isinstance(other, self.__class__):
            # dot product for other vectors
            return self.dot(other)
        else:
            raise TypeError(
                    "unsupported operand (multiply/divide) for types %s and %s" % (
                        self.__class__, type(other)))

    def __hash__(self):
        return self.coords.__hash__()

    def __eq__(self, other):
        """I am allowing these to compared to tuples, and to say that yes, they
        are equal. the idea here is that a Vector3d _is_ a tuple of floats, but
        with some extra methods.
        """
        return self.coords == other.coords

    def angleTo(self, other):
        """computes the angle between two vectors
            cos theta = (n * m) / (n.length * m.length)
        """
        cosTheta = (self * other) / (self.length * other.length)
        return math.acos(cosTheta)

class Vector2d(Base):
    def __init__(self, x=0.0, y=0.0):
        VectorBase.__init__(self)
        self.coords = (x, y)

    @property
    def x(self):
        return self[0]
    @x.setter
    def x(self, value):
        self.coords = (value,) + self.coords[1:]

    @property
    def y(self):
        return self[1]
    @y.setter
    def y(self, value):
        self.coords = self.coords[:1] + (value,) + self.coords[2:]

    def asDict(self):
        """return dictionary representation of the vector"""
        return dict( zip( ('x','y'), self.coords ) )

    def __getitem__(self, key):
        """Treats the vector as a tuple or dict for indexes and slicing.
        """
        # dictionary
        if key in ('x','y'):
            return self.asDict()[key]
        # slicing and index calls
        else:
            return self.coords.__getitem__(key)

    def toX(self, number):
        """For getting a copy of the same vector but with a new x value"""
        return self.__class__(number, self[1])

    def toY(self, number):
        """For getting a copy of the same vector but with a new y value"""
        return self.__class__(self[0], number)

    def __repr__(self):
        return 'Vector2d(%s, %s)' % self.coords

class Vector3d(Vector2d):
    def __init__(self, x=0.0, y=0.0, z=0.0):
        Vector2d.__init__(self)
        self.coords = (x, y, z)
   
    def asDict(self):
        """return dictionary representation of the vector"""
        return dict( zip( list('xyz'), self.coords ) )

    def __getitem__(self, key):
        if key in ('x','y','z'):
            return self.asDict()[key]
        else:
            return self.coords.__getitem__(key)

    def cross(self, other):
        """Gets the cross product between two vectors
        """
        x = (self[1] * other[2]) - (self[2] * other[1])
        y = (self[2] * other[0]) - (self[0] * other[2])
        z = (self[0] * other[1]) - (self[1] * other[0])
        return self.__class__(x, y, z)

    def __repr__(self):
        return 'Vector3d(%s, %s, %s)' % self.coords
