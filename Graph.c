# include <stdio.h>
# include "Graph.h"

Graph newGraph(int noNodes);

void  insertEdge(Graph g, Vertex src, Vertex dest, int weight);
void  removeEdge(Graph g, Vertex src, Vertex dest);
bool  adjacent(Graph g, Vertex src, Vertex dest);
int  numVerticies(Graph g);

AdjList outIncident(Graph g, Vertex v);

AdjList inIncident(Graph g, Vertex v);

void  showGraph(Graph g);

void  freeGraph(Graph g);
