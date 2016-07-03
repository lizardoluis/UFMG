import math

class Point:
    def __init__(self, coord):
        self.x = coord[0]
        self.y = coord[1] 
        self.z = coord[2]

    def __str__(self):
        return "(%.3f, %.3f, %.3f)" % (self.x, self.y, self.z)

    def distance(self, p):
        return math.sqrt(pow(self.x - p.x, 2) + pow(self.y - p.y, 2) + pow(self.z - p.z, 2))
