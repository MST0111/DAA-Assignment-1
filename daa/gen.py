import random
import math
import matplotlib.pyplot as plt
import sys
 
num_vertices = int(sys.argv[1]) # specify the number of vertices
 
# generate random x, y coordinates for the vertices
vertices = [(random.uniform(-250, 250), random.uniform(-250, 250)) for _ in range(num_vertices)]
 
# sort the vertices in clockwise order
center = tuple(map(sum, zip(*vertices)))  # calculate the center of the polygon
center = (center[0] / num_vertices, center[1] / num_vertices)
vertices = sorted(vertices, key=lambda vertex: (math.atan2(vertex[1] - center[1], vertex[0] - center[0]) + 2 * math.pi) % (2 * math.pi))
 
 
vertices = vertices[::-1]
 
 
# write the vertices to a text file
file = open('input.txt', 'w')
file.write(f'{num_vertices}\n')
 
for vertex in vertices:
    file.write(f'{vertex[0]} {vertex[1]}\n')