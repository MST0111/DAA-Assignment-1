/**
 * @file DCEL.hpp
 * @brief Header file for a doubly-connected edge list (DCEL) implementation
 * 
 */
#ifndef DCEL_H
#define DCEL_H

#include <bits/stdc++.h>
#include "Vertex.hpp"
#include "Face.hpp"
#include "Edge.hpp"
using namespace std;
/**
 * @brief Output file stream for writing the output of the split algorithm.
 * 
 */
ofstream fout("output.txt");
/**
 * @brief Output file stream for writing the polygon vertices.
 * 
 */
ofstream poly("polygon.txt");
/**
 * @brief Output file stream for writing the output of the merge algorithm.
 * 
 */
ofstream merg("merge.txt");

class Vertex;
class Face;
/**
 * @brief Check if a vertex is reflex or not.
 * 
 * @param A The vertex for which the reflex angle is to be calculated.
 * @param B The next vertex in the polygon.
 * @param C The previous vertex in the polygon.
 * @return true if the vertex is reflex.
 * @return false if the vertex is not reflex.
 */
bool isreflex(Vertex *A, Vertex *B, Vertex *C)
{
    double x1 = B->x - A->x;
    double y1 = B->y - A->y;
    double x2 = B->x - C->x;
    double y2 = B->y - C->y;
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
 * @brief Check if two vertices lie on the same side of a line formed by two other vertices
 * 
 * @param v1 The first vertex
 * @param v2 The second vertex
 * @param v3 The third vertex forming the line
 * @param v4 The fourth vertex forming the line
 * @return true if v1 and v2 lie on the same side of the line formed by v3 and v4.
 * @return false if v1 and v2 do not lie on the same side of the line formed by v3 and v4.
 */
bool lieonsameside(Vertex *v1, Vertex *v2, Vertex *v3, Vertex *v4)
{
 
    double c = (v1->x) * (v2->y) - (v2->x) * (v1->y);
    double y21 = v2->y - v1->y;
    double x21 = v2->x - v1->x;
    double val1 = (v3->x) * y21 - (v3->y) * x21;
    double val2 = (v4->x) * y21 - (v4->y) * x21;
    double res = (val1 - c) * (val2 - c);
 
    if (res > 0)
    {
        return true;
    }
    return false;
}
/**
 * @brief Returns the previous vertex of a given vertex in a face.
 * 
 * @param f A pointer to the face
 * @param v A pointer to the vertex whose previous vertex is to be found
 * @return A pointer to the previous vertex (Vertex*) 
 */
Vertex* prev_vertex(Face* f,Vertex* v)
{
    Vertex* res;
    Edge* e = f->inc_edge;
    Edge* e1 = e;
    do{
        e1 = e1->prev;
        if(e1 ->org == v){
            e1 = e1->prev;
            res = e1->org;
            return res;
        }
    }
    while(e1 != e);
    return res;

}
/**
 * @brief Returns the next vertex of a given vertex in a given face.
 * 
 * @param f pointer to the face in which the next vertex is to be found.
 * @param v pointer to the vertex whose next vertex is to be found.
 * @return A pointer to the next vertex (Vertex*)  
 */
Vertex* next_vertex(Face* f,Vertex* v)
{
    Vertex* res;
    Edge* e = f->inc_edge;
    Edge* e1 = e;
    do{
        e1 = e1->next;
        if(e1 ->org == v){
            e1 = e1->next;
            res = e1->org;
            return res;
        }
    }
    while(e1 != e);
    return res;

}
/**
 * @brief An implementation of a doubly-connected edge list (DCEL) data structure.
 * @class DCEL
 */
class DCEL
{
 
public:
    vector<Vertex *> vertices;
    vector<Edge *> edges;
    vector<Edge*> twin_edges;
    vector<Face *> faces;
    vector<Edge*>LLE;
    DCEL(int n);
    void fout_the_split();
    void fout_the_merge();
    void summary_faces();
    void split(int n,int& diagonals);
    void merge(int n,int& m);
    void rotate(Face* f);
    bool isconvex(Vertex* v);
    
};
/**
 * @brief Construct a new DCEL::DCEL object
 * 
 * @param n no of vertices
 */
DCEL::DCEL(int n)
{
    vertices.resize(n);
    edges.resize(n);
    twin_edges.resize(n);
    faces.resize(0);

}
/**
 * @brief Outputs the information of the DCEL to polygon.txt
 * This function prints the information of the vertices and edges in the DCEL to a file stream polygon.txt using script.py script
 */
void DCEL::fout_the_split()
{
    int n = this->vertices.size();
    fout << "Number of Vertices = " << n << endl;
    fout << "Printing Vertices info\n";
    for (int i = 0; i < n; i++)
    {
        fout << "Point " << i + 1 << " (" << this->vertices[i]->x << "," << this->vertices[i]->y << ")" << endl;
    }
 
    int es = this->edges.size();
    fout << "Number of Edges = " << es << endl;
    poly << es << endl;
 
    for (int i = 0; i < es; i++)
    {
        fout << "Edges between point " << this->edges[i]->org->id << " and " << this->edges[i]->next->org->id << endl;
        poly << this->edges[i]->org->x << " " << this->edges[i]->org->y << " " << this->edges[i]->next->org->x << " " << this->edges[i]->next->org->y;
        if (i != es - 1)
        {
            poly << "\n";
        }
    }
    fout << endl;
}
/**
 * @brief Debugging the face
 * Outputs a summary of the faces in the DCEL object to a file.
 * This function iterates through each face in the DCEL object and outputs its ID and the IDs of the
 * vertices that make up its boundary to the file associated with the ofstream object 'fout'.
 * Additionally, it outputs the total number of faces in the DCEL object at the beginning of the file.
 */
void DCEL::summary_faces() 

{
   // cout<<"brdr\n";

    fout<<"No of faces are "<<this->faces.size()<<"\n";
    for(auto face:this->faces){
        if(face == NULL){
            // cout<<"Here\n";
        }
        fout<<"Face id is "<<face->id<<"\n";
        Edge* inc=face->inc_edge;
        // cout<<"Vertices ";
        auto temp=inc;
        do{
            fout<<temp->org->id<<" ";
            temp=temp->next;
        }while(temp!=inc);
        fout<<"\n";
    }
}
/**
 * @brief Outputs the information of the DCEL after merging to merge.txt
 * This function prints the information of the vertices and edges in the DCEL after merging to 
 */
void DCEL::fout_the_merge()
{
    int cnt = 0;
    // cout<<"ded\n";
    for(auto e:this->edges){
        if(e->isrequired){
            cnt++;
        }
    }
    merg<<cnt;
    for(auto p:this->edges){
        if(p->isrequired){
            merg<<"\n"<<p->org->x<<" "<<p->org->y<<" "<<p->next->org->x<<" "<<p->next->org->y;
            
        }
    }


}
/**
 * @brief Checks whether a vertex is convex or not in the original polygon.
 * 
 * @param v Pointer to the vertex to be checked.
 * @return true if the vertex is convex.
 * @return false if the vertex is not convex.
 */
bool DCEL::isconvex(Vertex* v){
    int n=this->vertices.size();
   Vertex* prev=this->vertices[(v->id-1)<0?(v->id-1)%n+n:v->id-1];
   Vertex* next=this->vertices[(v->id+1)%n];
   return !isreflex(prev,v,next);
}

void DCEL::rotate(Face* f){
    auto r=f->inc_edge;
    do{
        //cout<<r->org->id<<" to ";
        r=r->next;
    }while(r !=f->inc_edge);
}
/**
 * @brief splitting the polygon 
 * 
 * @param n  no of vertices
 * @param diagonals no of diagonals having initial value '0' & present in DCEL after splitting 
 */
void DCEL:: split(int n,int& diagonals)
{
    // cout
    
    // Algorithm implementation
    
    deque<Vertex *> L, P;
    // Step 1
    for (int i = 0; i < n; i++)
    {
        P.push_back(this->vertices[i]);
    } 
    // Step 2 
    int m = 1;
    int sz = n;
    L.push_back(this->vertices[0]);
    // Step 3 
    int itr = 0;
   
    while (sz > 3 and ++itr)
    {
        // 3.1
        // if(m>2*n) break;

        Vertex *v1 = *(prev(L.end()));
        Vertex *v2;
        deque<Vertex *> ptemp = P;
 
        if (ptemp.back() == v1)
        {
            v2 = ptemp.front();
        }
        else
        {
            while (ptemp.size())
            {
                Vertex *vv = ptemp.front();
                ptemp.pop_front();
                if (vv == v1)
                {
                    v2 = ptemp.front();
                    break;
                }
            }
        }
        // 3.2
        L = {v1, v2};
        int i = 2;
        Vertex *va = v1;
        Vertex *vb = v2;
        Vertex *vc;
        deque<Vertex *> Pd = P;
        Vertex *lass = Pd.back();
        if (lass == vb)
        {
            vc = Pd.front();
        }
        else
        {
            while (Pd.size())
            {
                // cout<<"f\n";
                Vertex *v = Pd.front();
                Pd.pop_front();
                if (v == vb)
                {
                    vc = Pd.front();
                    break;
                }
            }
            //cout<<"\n\n\n";
        }
 
        // 3.2
 
        // 3.3
       
        while (!isreflex(va, vb, vc) and !isreflex(vb, vc, v1) and !isreflex(vc, v1, v2) and L.size() < sz)
        {
            L.push_back(vc);
            i++;
 
            va = vb;
            vb = vc;
            deque<Vertex *> polo = P;
            if (polo.back() == vc)
            {
                vc = polo.front();
            }
            else
            {
                while (polo.size())
                {
                    Vertex *polofront = polo.front();
                    polo.pop_front();
                    if (polofront == vc)
                    {
                        vc = polo.front();
                        break;
                    }
                }
            }
             
        }
        // cout<<"itr = "<<itr<<" and L.size() = "<<L.size()<<endl;
        //cout<<"Should be here\n";
        // 3.3
 
        // 3.4
        if (L.size() != P.size())
        {
            // 3.4.1
            
            deque<Vertex *> LPVS;
            for (auto it : P)
            {
                bool found = false;
                for (auto e : L)
                {
                    if (it == e)
                    {
                        found = true;
                        break;
                    }
                }
 
                if (!found and (it)->isnotch())
                {
                    LPVS.push_back(it);
                }
 
                // 3.4.1
            }
            // 3.4.2
 
            while (LPVS.size())
            {
                double xmin, xmax, ymin, ymax;
                deque<Vertex *> temp = L;
                xmin = temp.front()->x; xmax = xmin;
                ymin = temp.front()->y; ymax = ymin;
                temp.pop_front();
                while (temp.size())
                {
                    Vertex *ff = temp.front(); temp.pop_front();
                    xmin = min(xmin, ff->x); xmax = max(xmax, ff->x);
                    ymin = min(ymin, ff->y); ymax = max(ymax, ff->y);
                }
 
                bool backward = false;
                while (!backward and LPVS.size() > 0)
                {
 
                    Vertex *v;
                    deque<Vertex *> pol;
                    do
                    {
                        v = *(LPVS.begin());
                        if (!v->isinRect( xmin, xmax, ymin, ymax))
                        {
                        }
                        else
                        {
                            pol.push_back(v);
                        }
                        LPVS.pop_front();
                        // LPVS.pop_front();
                    } while (LPVS.size() > 0);
 
                    while (pol.size() > 0)
                    {
                        Vertex *ab = pol.front();
                        LPVS.push_back(ab);
                        pol.pop_front();
                    }
 
                    if (LPVS.size())
                    {
                        v = LPVS.front();
 
                        if (v->isInsidePolygon(L))
                        { 
                            unordered_set<Vertex *> VTR;
                            Vertex *last = L.back();
                            unordered_set<Vertex *> unwanted;
                            for (auto e : L)
                            {
                                if (lieonsameside(v1, v, e, last))
                                {
                                   unwanted.insert(e);
                                }
                            }
                            deque<Vertex *> LL;
                            for (auto e : L)
                            {
                                if (!unwanted.count(e))
                                {
                                    LL.push_back(e);
                                }
                            }
                            L = LL;
 
                            backward = true;
                            LPVS.pop_front();
                            v = LPVS.front();
                            // MP1 ends
                        }
                        else
                        {
                            LPVS.pop_front();
                        }
                    }
                }
            }
            // 3.4.2
        }
 
        if (L.size() and L.back() != v2)
        {
            Vertex *Front = L.front();
            Vertex *Back = L.back();
            bool pq = false;
            if (Front->inc_edge->prev->org == Back)
            {
                pq = true;
            }
 
            if (!pq)
            {
                diagonals++;
                // 3.5.1 write Lm as partition
                Edge *rev = new Edge(Front, NULL, NULL, NULL, NULL);
                Edge *diag = new Edge(Back, NULL, NULL, NULL, NULL);
                //cout<<"Adding diagonal from "<<diag->org->id<<" to "<<rev->org->id<<"\n";
                diag->twin = rev;
                rev->twin = diag;
 
                Edge* ea = Front->inc_edge;
                Edge* eaprevold = ea->prev;
                Edge* eb = Back->inc_edge;
                Edge* ebprevold = eb->prev;
 
                diag->next = ea;
                ea->prev = diag;
                rev->next = eb;
                eb->prev = rev;
 
 
                diag->prev = ebprevold;
                ebprevold->next = diag;
                rev->prev = eaprevold;
                eaprevold->next = rev;
                Edge* pk = diag;
                do{
                    //cout<<pk->org->id<<" ";
                    pk = pk->next;
                }
                while(pk!=diag);
                //cout<<"\n";
 
 
 
 
 
                this->edges.push_back(diag);
                //update
                this->twin_edges.push_back(rev);
                
                Face* curr_face = new Face(diag,this->faces.size());
                
                diag->right = curr_face;
                this->faces.push_back(curr_face);
                Front->inc_edge = rev;
                this->LLE.push_back(diag);
 
                // 3.5.1
                // 3.5.2
            }
 
            deque<Vertex *> PP;
            Vertex *front_el = L.front();
            Vertex *back_el = L.back();
            for (auto e1 : P)
            {
                bool flag = false;
                for (auto e2 : L)
                {
                    if (e1 == e2)
                    {
                        flag = true;
                        break;
                    }
                }
 
                if (!flag or (e1 == front_el) or (e1 == back_el))
                {
                    PP.push_back(e1);
                }
            }
            P.clear();
            while (PP.size())
            {
                Vertex *gg = PP.front();
                PP.pop_front();
                P.push_back(gg);
            }
 
            sz = sz - L.size() + 2;
            // 3.5.2
        }
        else
        {
           // cout<<"failed at iteration "<<itr<<"\n";
            // Vertex* fg = L.front();
            Vertex* gh = P.front();
            P.pop_front();
            P.push_back(gh);
            // continue;
            // L.pop_front();
            // continue;
            // L.push_back(fg);

        }
        // 3.6
        // m = m + 1;
        // deque<Vertex *> df = L;
        // while (df.size())
        // {
        //     Vertex *lm = df.front();
        //     df.pop_front();
        // }

        
    }
        
 
 
 
 
    for(Face* f:this->faces)
    {
        Edge* e = f->inc_edge;
        Edge* dup = e;
        do{
            dup->right = f;
            //cout<<dup->org->id<<" ";
            dup = dup->next;
        }
        while(dup != e);
       // cout<<endl;
    }
 
    // cout<<"Remained Faces adding :";
    Face* new_face = new Face(NULL,this->faces.size());
    Edge* tt;
    bool ff = false;
    for(auto ed:this->edges)
    {
        if(ed->right == NULL){
           // cout<<"Missed "<<ed->org->id<<endl;
            tt = ed;
            ff= true;
            break;
        }
    }
 
    if(ff){
        new_face->inc_edge = tt;
        Edge* t1 = tt;
        do{
            t1 ->right = new_face;
            t1 = t1 ->next;
        }
        while(t1 != tt);
        this->faces.push_back(new_face);
    }
  
 
 
 
 
    ff = false;

 
    // cout<<"\nRemained Faces adding :";
    Face* new_face_rev = new Face(NULL,this->faces.size());
    int ss = this->twin_edges.size();
    for(int i=n;i<ss;i++){  
        Edge* et = this->twin_edges[i];
        if(et->right == NULL){
            tt = et;
            ff = true;
            break;
        }
 
    }
   
 
    if(ff){
        new_face_rev->inc_edge = tt;
        Edge* t1 = tt;
        do{
            t1->right = new_face_rev;
            t1 = t1 ->next;
        }
        while(t1 != tt);
        this->faces.push_back(new_face_rev);
    }
            //   cout<<"Flag\n";
    // cout<<"\n";
 
 
 
 
    cout << "Done Splitting\n";

}
/**
 * @brief This function merges adjacent triangles of the polygon using the polygon partitioning algorithm.
 * 
 * 
 * @param n no of vertices 
 * @param m no of diagonals after splitting in DCEL
 */
void DCEL::merge(int n,int& m)
{
   
    unordered_map<Vertex*,vector<pair<int,Vertex*>>>LPV;
    vector<bool>LDP;
    deque<int>LUP;
    int np = m+1;
    for(int i=0;i<np;++i){
        LDP.push_back(true);
        LUP.push_back(i);
    }
    
    // build LPV
    for(auto v:this->vertices){
        vector<pair<int,Vertex*>>tempvect;
        for(auto f:this->faces){

            bool found = false;
            Edge* orig = f->inc_edge;
            Edge* dup = orig;
            do{
                dup = dup->next;
                if(dup->org == v){
                    found = true;
                    break;
                }
            }
            while(dup!=orig);
            if(found){
                Vertex* next_vertex;
                orig = f->inc_edge;
                dup = orig;
                do{
                    dup = dup->next;
                    if(dup->org == v){
                        next_vertex = dup->next->org;
                    }
                }
                while(dup!=orig);
                pair<int, Vertex*> yy = {f->id,next_vertex};
                if(abs(next_vertex->id - v->id)!=1){
                    tempvect.push_back(yy);
                }
                
            }
        }

        LPV[v] = tempvect;
    }



    for(int j=0;j<m;++j)
    {
     
        // 3.1
         //cout<<j<<" rocky"<<endl;
        Vertex *vs = LLE[j]->org;
        Vertex* vt = LLE[j]->twin->org;
        // cout<<"diagonal from ";
        // cout<<vs->id<<" "<<vt->id<<endl;
        
      
        if((LPV[vs].size()>2 && LPV[vt].size()>2) || (LPV[vs].size()>2 && this->isconvex(vt)) || (LPV[vt].size()>2 && this->isconvex(vs)) || (this->isconvex(vt) && this->isconvex(vs)) )
        {
            // 3.2.1
            Vertex* j2 = vt;
            Vertex* i2 = vs;
            Vertex* j3 = next_vertex(LLE[j]->right,vt);
            Vertex* i1 = prev_vertex(LLE[j]->right,vs);
            // 3.2.2
            int u;
         
            for(auto e: LPV[vt]){
                 
                int g1 = e.first;
                Vertex*g2 = e.second;
                if(g2 == vs){
                    u = g1;
                    break;
                }
            }
            
            // 3.2.3
            Vertex* j1 = prev_vertex(LLE[j]->twin->right,vt);
            Vertex* i3 = next_vertex(LLE[j]->twin->right,vs);


            // 3.2.4
            if(!isreflex(i1,i2,i3) && !isreflex(j1,j2,j3)){
                np++;
                
                
                Edge* ea = this->LLE[j]->prev;
                Edge* ec = this->LLE[j]->next;
                Edge* eb = this->LLE[j]->twin->next;
                Edge* ed = this->LLE[j]->twin->prev;

                ea->next = eb;
                eb->prev = ea;
                ec->prev = ed;
                ed->next = ec;




                LLE[j]->isrequired = false;
                LDP[j] = false;
                LDP[u] = false;
                LDP[np] = true;
                LUP[j] = np;
                LUP[u] = np;

                for(int h = 0;h<np-2;++h){
                    if(LUP[h] == j || LUP[h] == u){
                        LUP[h] = np;
                    }
                }
            }

        }



    }

    cout<<"Done Merging\n";
    // cout<<"here\n";



}

#endif