/*AIM- To find the single-source shortest paths from a given source vertex to all other vertices in a weighted graph using
Dijkstra's Greedy Algorithm.*/
//{NAME}

#include <bits/stdc++.h>
using namespace std;
#define V 6
int minDistance(int Distance[], bool chkVertex[])
{
 int min = INT_MAX, min_index;
 for(int v=0;v<V;v++)
 if(chkVertex[v]==false && Distance[v]<min)
 min=Distance[v], min_index=v;
 return min_index;
}
void Dijk(int graph[V][V])
{
 int Distance[V]; bool chkVertex[V];
 for(int i=0;i<V;i++) Distance[i]=INT_MAX, chkVertex[i]=false;
 Distance[0] = 0;
 for(int count=0;count<V-1;count++)
 {
 int u = minDistance(Distance, chkVertex);
 chkVertex[u] = true;
 for(int v=0;v<V;v++)
 if(graph[u][v] && chkVertex[v]==false &&
 graph[u][v]+Distance[u]<Distance[v])
 Distance[v] = graph[u][v] + Distance[u];
 }
 cout << "Vertex\tDistance\n";
 for(int i=0;i<V;i++) cout << i << "\t" << Distance[i] << "\n";
}
int main()
{
 int graph[V][V] = {
 {0,4,5,0,0,0},{4,0,11,9,7,0},
 {5,11,0,0,3,0},{0,9,0,0,13,2},
 {0,7,3,13,0,6},{0,0,0,2,6,0}
 };
 Dijk(graph); return 0;
}