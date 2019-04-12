// Graph ADT interface for Ass2 (COMP2521)
#include <stdlib.h>
#include <stdio.h>

#include "Graph.h"

struct GraphRep{
	int nV;
	int nE;
	AdjList *outNodeList; // List of out nodes in graph
	AdjList *inNodeList; // List of in nodes in graph
};

static AdjList newAdjListnode(Vertex, int);

Graph newGraph(int noNodes) {
	if (noNodes == 0) return NULL;
	Graph g = malloc(sizeof(g));
	if (g == NULL) return NULL;
	g->nV = noNodes;
	g->nE = 0;
	g->outNodeList = malloc(noNodes * sizeof(AdjList));
	g->inNodeList = malloc(noNodes * sizeof(AdjList));
	for (int i = 0; i < noNodes; i++){
		g->outNodeList[i] = NULL;
		g->inNodeList[i] = NULL;
	}
	return g;
}

int numVerticies(Graph g) {
	if (g == NULL) return 0;
	return g->nV;
}

void  insertEdge(Graph g, Vertex src, Vertex dest, int weight) {
	if (g == NULL || weight <= 0) return;

	// insert to outNodeList
	AdjList newnode = newAdjListnode(dest, weight);
	if (g->outNodeList[src] == NULL) { // No outward edge recorded
		g->outNodeList[src] = newnode;	
	}
	else {
		AdjList curr = g->outNodeList[src];
		while(curr->next != NULL) curr = curr->next;
		curr->next = newnode;
	}

	// insert to inNodeList
	newnode = newAdjListnode(src, weight);
	if (g->inNodeList[dest] == NULL) {  // No inward edge recorded
		g->inNodeList[dest] = newnode;
	}
	else {
		AdjList curr = g->inNodeList[dest];
		while(curr->next != NULL) curr = curr->next;
		curr->next = newnode;
	}
	g->nE++;
}

void  removeEdge(Graph g, Vertex src, Vertex dest) {
	if (g == NULL) return;
	if (!adjacent(g, src, dest)) return;

	// remove edge from outNodeList
	AdjList delete, curr = g->outNodeList[src];
	if (curr->w == dest) { // At the head
		delete = curr;
		g->outNodeList[src] = delete->next;
		free(delete);
	}
	else {
		while(curr->next != NULL) {
			if (curr->next->w == dest) {
				delete = curr->next;
				curr->next = delete->next;
				free(delete);
				break;
			}
			curr = curr->next;
		}
	}

	// remove edge from inNodeList
	curr = g->inNodeList[dest];
	if(curr->w == src) { // At the head
		delete = curr;
		g->inNodeList[dest] = delete->next;
		free(delete);
	}
	else {
		while(curr->next != NULL) {
			if (curr->next->w == src) {
				delete = curr->next;
				curr->next = delete->next;
				free(delete);
				break;
			}
			curr = curr->next;
		}
	}
	g->nE--;
}

bool adjacent(Graph g, Vertex src, Vertex dest) {
	if (g == NULL) return 0;
	AdjList curr = g->outNodeList[src];
	while(curr != NULL) {
		if (curr->w == dest) return true;
		curr = curr->next;
	}
	return false;
}

AdjList outIncident(Graph g, Vertex v) {
	if (g == NULL) return NULL;
	return g->outNodeList[v];
}

AdjList inIncident(Graph g, Vertex v) {
	if (g == NULL) return NULL;
	return g->inNodeList[v];
}

void  freeGraph(Graph g) {
	if (g == NULL) return;

	for(int i = 0; i < g->nV; i++) {
		AdjList curr = g->outNodeList[i], old;
		while(curr != NULL) {
			old = curr;
			curr = curr->next;
			free(old);
		}
		free(g->outNodeList[i]);
	}
	for(int i = 0; i < g->nV; i++) {
		AdjList curr = g->inNodeList[i], old;
		while(curr != NULL) {
			old = curr;
			curr = curr->next;
			free(old);
		}
		free(g->inNodeList[i]);
	}
	free(g->outNodeList);
	free(g->inNodeList);
	free(g);
}

static AdjList newAdjListnode(Vertex w, int weight) {
	AdjList node = malloc(sizeof(node));
	node->weight = weight;
	node->w = w;
	node->next = NULL;
	return node;
}
