// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define INF 2147483647

typedef struct PredNode *PredNodePtr;

static ShortestPaths newShortestPaths(Graph, Vertex);
static PredNodePtr newPredNode(int);


ShortestPaths dijkstra(Graph g, Vertex v) {
	assert(g != NULL);
	ShortestPaths throwAway = {0};
	throwAway = newShortestPaths(g, v);
	throwAway.dist[v] = 0; // Set distance to src = 0
	
	return throwAway;
}

void showShortestPaths(ShortestPaths paths) {
	return;
}


void  freeShortestPaths(ShortestPaths paths) {
	return;
}

static ShortestPaths newShortestPaths(Graph g, Vertex v){
	ShortestPaths new;
	int numnode = numVerticies(g);
	new.noNodes = numnode;
	new.src = v;
	new.dist = malloc(numnode * sizeof(int));
	assert(new.dist != NULL);
	for (int i = 0; i < numnode; i++) new.dist[i] = INF;
	new.pred = malloc(numnode * sizeof(PredNodePtr));
	assert(new.pred != NULL);
	for (int i = 0; i < numnode; i++) new.pred[i] = NULL;
	return new;
}

static PredNodePtr newPredNode(int v){
	PredNodePtr new = malloc(sizeof(PredNodePtr));
	new->v = v;
	new->next = NULL;
	return new;
}