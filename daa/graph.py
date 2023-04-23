import matplotlib.pyplot as plt

# Open the file containing the vertices
with open('split_timings.txt', 'r') as f:
    lines = f.readlines()

# Parse the vertices from the file
vertices = []
for line in lines:
    coords = line.strip().split()
    x, y = float(coords[0]), float(coords[1])
    vertices.append((x, y))

# Plot the vertices using Matplotlib
fig, ax = plt.subplots()
x_values, y_values = zip(*vertices)
ax.plot(x_values, y_values)
plt.xlabel('Number of vertices ')
plt.ylabel('Execution Time in milliseconds')
plt.show()
