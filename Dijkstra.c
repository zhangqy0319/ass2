// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define INF 2147483647

typedef struct PredNode *PredNodePtr;

static ShortestPaths newShortestPaths(Graph, Vertex);
static PredNodePtr newPredNode(Vertex);


ShortestPaths dijkstra(Graph g, Vertex v) {
	assert(g != NULL);
	ShortestPaths throwAway = {0};
	throwAway = newShortestPaths(g, v);
	throwAway.dist[v] = 0; // Set distance to src = 0
	PQ todo = newPQ();
	ItemPQ firstnode;
	firstnode.key = v; 
	firstnode.value = 0; 
	int Visited[numVerticies(g)];
	for (int i = 0; i < numVerticies(g); i++ ) Visited[i] = 0;
	addPQ(todo, firstnode);

	while (!PQEmpty(todo)){
		Vertex curr = dequeuePQ(todo).key;
		Visited[curr] = 1;
		AdjList outnode = outIncident(g, curr);
		while (outnode != NULL){
			Vertex dest = outnode->w;
			int weight = outnode->weight;
			if (throwAway.dist[curr] + weight < throwAway.dist[dest]){
				throwAway.dist[dest] = throwAway.dist[curr] + weight;
				if (throwAway.pred[dest] == NULL) throwAway.pred[dest] = newPredNode(dest);
				else{
					PredNodePtr predcurr = throwAway.pred[dest];
					while (predcurr->next != NULL) predcurr = predcurr->next;
					predcurr->next = newPredNode(dest);
				}
				//if (Visited[dest] == 0) {
					ItemPQ node;
					node.key = dest;
					node.value = throwAway.dist[curr] + weight;
					addPQ(todo, node);
				//}
			}
			outnode = outnode->next;
		}
		
	}
	
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

static PredNodePtr newPredNode(Vertex v){
	PredNodePtr new = malloc(sizeof(PredNodePtr));
	new->v = v;
	new->next = NULL;
	return new;
}
