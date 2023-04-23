import math

def polygon_sort(coords):
    n = len(coords)
    center_x = sum(x for x, y in coords) / n
    center_y = sum(y for x, y in coords) / n
    sorted_coords = sorted(coords, key=lambda coord: (math.atan2(coord[1] - center_y, coord[0] - center_x) + 2 * math.pi) % (2 * math.pi))
    return sorted_coords

with open('input.txt', 'r') as f:
    num_vertices = int(f.readline().strip())
    vertices = [tuple(map(float, line.strip().split())) for line in f]

sorted_vertices = polygon_sort(vertices)

with open('input.txt', 'w') as f:
    f.write(f"{num_vertices}\n")
    for x, y in sorted_vertices:
        f.write(f"{x} {y}\n")
