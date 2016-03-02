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




