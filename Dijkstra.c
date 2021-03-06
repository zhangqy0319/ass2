// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define INF __INT_MAX__

typedef struct PredNode *PredNodePtr;

static ShortestPaths newShortestPaths(Graph, Vertex);
static PredNodePtr newPredNode(Vertex);

ShortestPaths dijkstra(Graph g, Vertex v) {
	assert(g != NULL);
	assert(numVerticies(g) > 1);

	ShortestPaths throwAway = newShortestPaths(g, v);
	throwAway.dist[v] = 0; // Set the distance to src equal 0
	PQ todo = newPQ();
	ItemPQ firstnode = {.key = v, .value = 0};
	addPQ(todo, firstnode);
	
	while (!PQEmpty(todo)){
		Vertex curr = dequeuePQ(todo).key;
		AdjList outnode = outIncident(g, curr);
		while (outnode != NULL){ // Get all outIncident's destinations
			Vertex dest = outnode->w;
			int weight = outnode->weight;
			// Distance from src to curr < Distance from src to destination
			if (throwAway.dist[curr] + weight < throwAway.dist[dest]){ 
				throwAway.dist[dest] = throwAway.dist[curr] + weight;
				PredNodePtr predcurr = throwAway.pred[dest], delete;
				while (predcurr != NULL) { // Delete the whole list
					delete = predcurr;
					predcurr = predcurr->next;
					free(delete);
				}
				throwAway.pred[dest] = newPredNode(curr);
				ItemPQ node = {.key = dest, .value = throwAway.dist[dest]};
				addPQ(todo, node);
			}
			else if(throwAway.dist[curr] + weight == throwAway.dist[dest]){
				// If predecessor list is empty
				if (throwAway.pred[dest] == NULL) throwAway.pred[dest] = newPredNode(curr);
				else{
					PredNodePtr predcurr = throwAway.pred[dest];
					while (predcurr->next != NULL) predcurr = predcurr->next;
					predcurr->next = newPredNode(curr);
				}
			}
			outnode = outnode->next;
		}
	}
	for (int i = 0; i < throwAway.noNodes; i++){ // Check unreachable vertices
		if (throwAway.dist[i] == INF) throwAway.dist[i] = 0;
	}
	return throwAway;
}

void showShortestPaths(ShortestPaths paths) {
	printf("Node %d\n", paths.src);
	printf("  Distance\n");
	for(int i = 0; i < paths.noNodes; i++) {
		if (paths.src == i) printf("    %d : X\n", i);
		else printf("    %d : %d\n", i, paths.dist[i]);
	}
	printf("  Preds\n");
	for(int i = 0; i < paths.noNodes; i++) {
		printf("    %d : ", i);
		if(paths.pred[i] == NULL) {
			printf("NULL\n");
		}
		else {
			PredNodePtr temp = paths.pred[i];
			while(temp != NULL) {
				printf("[%d]->", temp->v);
				temp = temp->next;
			}
			printf("NULL\n");			
		}
	}
}


void  freeShortestPaths(ShortestPaths paths) {
	free(paths.dist);
	for (int i = 0; i < paths.noNodes; i++){
		PredNodePtr curr = paths.pred[i], delete;
		while (curr != NULL){
			delete = curr;
			curr = curr->next;
			free(delete);
		}
	}
	free(paths.pred);
}

// Helper functions

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
