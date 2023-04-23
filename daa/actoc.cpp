/**
 * @file actoc.cpp
 * @brief This file reverses the order of vertices
 */
#include <bits/stdc++.h>
using namespace std;
/**
 * @brief Reads vertices of a polygon from a file named "input.txt",
 * reverses the order of vertices, and writes them back to the same file.
 * 
 * @return  0 if successful
 */
int main()
{
  ifstream fin("input.txt");

  int n;
  fin>>n;
  float a;
  float b;
  n--;
  fin>>a;fin>>b;
  vector<pair<float,float>> vertices;
  while(n--)
  {
      float x;
      float y;
      fin>>x>>y;
      vertices.push_back({x,y});
  } 
   n=vertices.size()+1;
   ofstream MyFile("input.txt");
    MyFile<<n<<endl;
    MyFile<<a<<" "<<b<<endl;
    for(int i=vertices.size()-1;i>=0;i--)
    {
        MyFile<<vertices[i].first<<" "<<vertices[i].second<<" "<<endl;
    }
}  

