/**
 * @file main.cpp
 * @brief main file with implementation.
 */
#include <bits/stdc++.h>
#include <fstream>
#include<chrono>
#include "DCEL.hpp"

using namespace std;
/**
 * @brief The number of vertices in a DCEL
 * 
 */
int n;
/**
 * @brief An input file stream for reading the input file
 * 
 */
ifstream fin("input.txt");
ofstream timing("timing.txt",ios::app);
/**
 * @brief Prints the contents of a deque of vertices
 * 
 * This function takes a deque of vertices and prints the IDs of each vertex
 * in the deque, in the order they appear in the deque. The deque is modified
 * during the function call and will be empty after the function returns.
 * 
 * @param q The deque of vertices to print
 */
void print_dq(deque<Vertex *> q)
{
    while (q.size())
    {
        Vertex *v = q.front();
        //cout << v->id << " ";
        q.pop_front();
    }
    //cout << "\n";
} 

/**
 * @brief  The main function for the program
 * 
 * This function is the entry point for the program. It reads input from a file,
 * constructs a DCEL data structure to represent a polygon, splits the polygon
 * into convex polygons, merges any unnecessary diagonals, and outputs the final
 * DCEL to a file. The program takes no command-line arguments
 * 
 * @return 0 if the program executes successfully 
 */
int main()
{
    double t1,t2;

    auto start_time = chrono::high_resolution_clock::now();
    
    fin >> n;

    DCEL *root = new DCEL(n);
    /**
     * @param m  number of diagonals in DCEL
     * 
     */
    int m = 0; // number of diagonals
    /**
     * @param np number of convex polygons
     * 
     */
    int np;// number of convex polygons
    for (int i = 0; i < n; i++)
    {
        double x, y;
        fin >> x >> y;
        Vertex *v = new Vertex(i, x, y, NULL);
        root->vertices[i] = v;
    }
 
    for (int i = 0; i < n; i++)
    {
 
        Edge *e1 = new Edge(root->vertices[i], NULL, NULL, NULL, NULL);
        Edge *e2 = new Edge(root->vertices[(i + 1) % n], NULL, NULL, NULL, NULL);
        
        e1->twin = e2;
        e2->twin = e1;
        root->edges[i] = e1;
        root->twin_edges[i]=e2;
 
        root->vertices[i]->inc_edge = e1;
      
 
       
    }
    for (int i = 0; i < n; ++i)
    {
 
        root->edges[i]->next = root->edges[(i + 1) % n];
        root->edges[(i + 1) % n]->prev = root->edges[i];
    }
    // cout<<"No of faces before split = "<<root->faces.size()<<endl;
    //cout<<"Before Split\n";
    auto a1 = chrono::high_resolution_clock::now();
    root->split(n,m);
    auto a2 = chrono::high_resolution_clock::now();
    t1 = chrono::duration<double>(a2 - a1).count() *1000;
   
    root->fout_the_split();
     // Algorithm to split the concave polygon into convex polygons
    root->summary_faces();
    // cout<<"Diagonals are "<<m<<"\n";
    auto b1 = chrono::high_resolution_clock::now();
    root->merge(n,m); // Merge Algorithm to remove unnecessary diagonals
    auto b2 = chrono::high_resolution_clock::now();
    t2 = chrono::duration<double>(b2 - b1).count() *1000;
    // cout<<"hi?\n";
    root->fout_the_merge();
    
 
    auto end_time = chrono::high_resolution_clock::now();
    double elapsed_time = chrono::duration<double>(end_time - start_time).count() *1000;
    cout << "Elapsed time: " << elapsed_time << " milli seconds" << endl;
    timing<<n<<" "<<elapsed_time<<"\n";
 
    return 0;
}