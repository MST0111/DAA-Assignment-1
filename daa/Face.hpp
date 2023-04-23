/**
 * @file Face.hpp
 * @brief This file contains the Face class used in the Doubly connected Edge List(DCEL) data structure for polygon representation.
 * 
 */
#ifndef FACE_H
#define FACE_H

#include <bits/stdc++.h>
using namespace std;

class Edge;
/**
 * @brief Class representing a Face in DCEL data Structure.
 * @class Face
 */
class Face
{
public:
    int id;
    Edge *inc_edge;
    Face(Edge *ed, int id)
    {
        this->inc_edge = ed;
        this->id = id;
    }
};

#endif