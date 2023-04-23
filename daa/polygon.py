import matplotlib.pyplot as plt
from matplotlib.patches import Polygon

# Open the input file
with open("input.txt", "r") as f:
    # Read the number of vertices
    num_vertices = int(f.readline())

    # Read the x and y coordinates of the vertices
    x_coords = []
    y_coords = []
    for i in range(num_vertices):
        coords = f.readline().split()
        x_coords.append(float(coords[0]))
        y_coords.append(float(coords[1]))

# Create the polygon
poly = Polygon(list(zip(x_coords, y_coords)), edgecolor='green', lw=2, facecolor='none')

# Plot the polygon
fig, ax = plt.subplots()
ax.add_patch(poly)
ax.set_xlim(min(x_coords)-1, max(x_coords)+1)
ax.set_ylim(min(y_coords)-1, max(y_coords)+1)
ax.set_aspect('equal')
plt.show()