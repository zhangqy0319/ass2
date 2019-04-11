// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef struct PredNode *PredNodep;

ShortestPaths dijkstra(Graph g, Vertex v) {
	assert(g != NULL);
	ShortestPaths throwAway = {0};
	throwAway.noNodes = 0;
	throwAway.src = v;
	throwAway.dist = malloc(numVerticies(g) * sizeof(int));
	throwAway.pred = malloc(numVerticies(g) * sizeof(PredNodep));

	return throwAway;
}

void showShortestPaths(ShortestPaths paths) {

}


void  freeShortestPaths(ShortestPaths paths) {

}
