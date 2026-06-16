/*AIM- To find the Minimum Spanning Tree of a graph using Kruskal's Greedy Algorithm with Union-Find (Disjoint Set
Union) data structure.*/
//{NAME}

#include <bits/stdc++.h>
using namespace std;
struct Edge { int src, dest, weight; };
struct subset { int parent, rank; };
int find(subset s[], int i)
{
 if(s[i].parent != i) s[i].parent = find(s, s[i].parent);
 return s[i].parent;
}
void Union(subset s[], int x, int y)
{
 if(s[x].rank < s[y].rank) s[x].parent = y;
 else if(s[x].rank > s[y].rank) s[y].parent = x;
 else { s[y].parent = x; s[x].rank++; }
}
bool cmp(Edge a, Edge b) { return a.weight < b.weight; }
int main()
{
 int V, n; cin >> V >> n;
 Edge a[n], result[V-1]; subset s[V];
 for(int i=0;i<=n-1;i++) cin >> a[i].src >> a[i].dest >> a[i].weight;
 sort(a, a+n, cmp);
 for(int i=0;i<V;i++) { s[i].parent=i; s[i].rank=0; }
 int i=0, k=0;
 while(i < V-1)
 {
 Edge next_edge = a[k++];
 int x = find(s, next_edge.src);
 int y = find(s, next_edge.dest);
 if(x != y) { result[i++] = next_edge; Union(s, x, y); }
 }
 printf("Edges in MST:\n");
 for(int j=0;j<i;j++)
 printf("%d %d == %d\n", result[j].src, result[j].dest, result[j].weight);
}