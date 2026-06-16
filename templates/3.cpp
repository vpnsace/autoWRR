/*AIM- To find the Minimum Spanning Tree (MST) of a connected, undirected weighted graph using Prim's Greedy
Algorithm.*/
//{NAME}

#include <bits/stdc++.h>
using namespace std;
#define V 7
int minKey(int key[], bool mstSet[]){
    int min = INT_MAX, min_index;
    for(int v = 0; v < V; v++)
    if(mstSet[v] == false && key[v] < min) min = key[v], min_index = v;
    return min_index;
}
void printMST(int parent[], int graph[V][V]){
    int total = 0;cout << "Edge \tWeight\n";
    for(int i = 1; i < V; i++){
    cout << parent[i] << " - " << i << "\t" << graph[i][parent[i]] << "\n";
    total += graph[i][parent[i]];}
    cout << "Total MST Weight = " << total;
}
void primMST(int graph[V][V]){
    int parent[V], key[V];
    bool mstSet[V];
    for(int i = 0; i < V; i++) key[i] = INT_MAX, mstSet[i] = false;
    key[0] = 0;
    parent[0] = -1;
    for(int count = 0; count < V - 1; count++){
        int u = minKey(key, mstSet);
        mstSet[u] = true;
        for(int v = 0; v < V; v++)
            if(graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]){
                parent[v] = u; key[v] = graph[u][v];}
    }
    printMST(parent, graph); }
int main(){
    int graph[V][V] = {
        {0,28,0,0,0,10,0},
        {28,0,16,0,0,0,14},
        {0,16,0,12,0,0,0},
        {0,0,12,0,22,0,18},
        {0,0,0,22,0,25,24},
        {10,0,0,0,25,0,0},
        {0,14,0,18,24,0,0}
    };
    primMST(graph); return 0;
}