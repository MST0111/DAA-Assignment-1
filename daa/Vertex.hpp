/**
 * @file Vertex.hpp
 * @brief This file contains the Vertex class used in the Doubly connected Edge List(DCEL) data structure for polygon representation.
 * 
 */
#ifndef VERTEX_H
#define VERTEX_H

#include <bits/stdc++.h>

using namespace std;
#include "Edge.hpp"
const double PI = 3.14;

class Edge;
/**
 * @brief Class representing a vertex in DCEL
 * @class Vertex
 */
class Vertex
{
    public:

    Edge *inc_edge;
    int id;
    double x, y;
    
    Vertex(int num, double x, double y, Edge *e);
    bool isnotch();
    bool isInsidePolygon(deque<Vertex *> vertices);
    bool isinRect(double xmin, double xmax, double ymin, double ymax);
   
};
/**
 * @brief Construct a new Vertex:: Vertex object
 * 
 * @param num an integer representing the unique identifier for this vertex
 * @param x a double representing the x-coordinate of this vertex
 * @param y a double representing the y-coordinate of this vertex
 * @param e a pointer to an instance of the Edge class that is incident on this vertex
 */
Vertex::Vertex(int num, double x, double y, Edge *e)
{
    this->id = num;
    this->x = x;
    this->y = y;
    this->inc_edge = e;

}
/**
 * @brief Gives whether a point is a notch or not in an unsplitted DCEL
 * 
 * @return true if the vertex is a notch
 * @return false if the vertex is not a notch
 */
bool Vertex::isnotch()
{
     Vertex *aft = this->inc_edge->twin->org;
        Vertex *bef = this->inc_edge->prev->org;

        double x1 = this->x - bef->x;
        double y1 = this->y - bef->y;
        double x2 = this->x - aft->x;
        double y2 = this->y - aft->y;
        double a = x1 * x2 + y1 * y2;
        double b = x1 * y2 - x2 * y1;
        double ang = (atan2(b, a) * 180 / PI);
        double max_angle = 180.00;

        if (ang < 0)
        {
            return true;
        }
        return false;

}
/**
 * @brief Checks whether a vertex is inside the polygon
 * 
 * @param vertices a deque of vertices representing the polygon
 * @return true if the vertex is inside the polygon.
 * @return false if the vertex is not inside the polygon.
 */
bool Vertex::isInsidePolygon(deque<Vertex *> vertices)
{
    auto start = vertices.front();
    int n = vertices.size();
    double x = this->x, y = this->y;
    Vertex *v2;
    for (int i{}; i < n; i++)
    {
        auto v1 = vertices.front();
        vertices.pop_front();
        if (i == n - 1)
        {
            v2 = start;
        }
        else
        {
            v2 = vertices.front();
        }
        double x_cap1 = v2->x - v1->x;
        double y_cap1 = v2->y - v1->y;
        double x_cap2 = x - v1->x, y_cap2 = y - v1->y;
        double res = x_cap1 * y_cap2 - x_cap2 * y_cap1;
        if (res >= 0)
        {
            return false;
        }
    }
    return true;
}
/**
 * @brief Checks whether a vertex is in rectangle or not
 * 
 * The vertices in rectangle found using this boolean function are checked whether they are convex or not and then returns in the set.
 * @param xmax The maximum x-coordinate of the rectangular region.
 * @param xmin The minimum x-coordinate of the rectangular region.
 * @param ymin The minimum y-coordinate of the rectangular region.
 * @param ymax The maximum y-coordinate of the rectangular region.
 * @return true 
 * @return false 
 */
bool Vertex:: isinRect(double xmin, double xmax, double ymin, double ymax)
{
    return this->x > xmin && this->x < xmax && this->y > ymin && this->y < ymax;
}

#endif