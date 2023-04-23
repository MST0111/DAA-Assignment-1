/**
 * @file Edge.hpp
 * @brief This file contains the Edge class used in the Doubly connected Edge List(DCEL) data structure for polygon representation.

 * 
 */
#ifndef EDGE_H
#define EDGE_H

#include <bits/stdc++.h>
#include "Face.hpp"
using namespace std;
class Vertex;
class Face;
/**
 * @brief Class to represent the Edge entity in the DCEL data structure.
 * @class Edge
 */
class Edge
{
 
    public:
    
    Edge *twin, *next, *prev; // pointing from this->twin->org to org;
    Vertex *org;              // destination can be obtained using this->twin->org;
    Face *right; // right can be obtained using this->twin->right;
    bool isrequired;
 
    Edge(Vertex *org, Edge *tw, Edge *nex, Edge *pre, Face *l)
    {
        this->org = org;
        this->twin = tw;
        this->next = nex;
        this->prev = pre;
        this->right = l;
        this->isrequired = true;
    }
    bool isPresentInFace(Face* curr_face);
};
/**
 * @brief Checks if an edge is present in a given face.
 * 
 * @param curr_face curr_face Pointer to the face to check.
 * @return true If the edge is present in the face.
 * @return false If the edge is not present in the face.
 */
bool Edge::isPresentInFace(Face* curr_face)
{
    Edge* start=curr_face->inc_edge;
    Edge* temp=start;
    do{
        if(temp==this){
            return true;
        }
        temp=temp->next;
    }while(temp!=start);
    return false;

}

#endif