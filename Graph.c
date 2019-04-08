// Graph ADT interface for Ass2 (COMP2521)
#include <stdlib.h>
#include <stdio.h>

#include "Graph.h"

struct GraphRep{
	int nV;
	int nE;
	AdjList *NodeList; // List of nodes in graph
};

static AdjList newAdjListnode(Vertex, int);

Graph newGraph(int noNodes) {
	if (noNodes == 0) return NULL;

	Graph g = malloc(sizeof(g));
	if (g == NULL) return NULL;

	g->nV = noNodes;
	g->nE = 0;
	g->NodeList[noNodes] = malloc(noNodes * sizeof(AdjList));
	for (int i = 0; i < noNodes; i++){
		g->NodeList[i] = newAdjListnode(i, 0);
	} 
	return g;
}

int numVerticies(Graph g) {
	if (g == NULL) {
		return 0;
	}
	return g->nV;
}

void  insertEdge(Graph g, Vertex src, Vertex dest, int weight) {
	if (g == NULL || weight <= 0) return;
	if (g->NodeList[src]->next == NULL) {
		AdjList newnode = newAdjListnode(dest, weight);
		g->NodeList[src]->next = newnode;
		return;
	}
	AdjList curr = g->NodeList[src]->next;
	while(curr->next != NULL) curr = curr->next;
	AdjList newnode = newAdjListnode(dest, weight);
	curr->next = newnode;
	g->nE++;
}

void  removeEdge(Graph g, Vertex src, Vertex dest) {
	if (g == NULL) return;
	if (!adjacent(g, src, dest)) return;

	AdjList delete,	 curr = g->NodeList[src]->next;
	if (curr->w == dest) {
		delete = curr;
		g->NodeList[src]->next = delete->next;
		free(delete);
		g->nE--;
		return;
	}
	while(curr->next != NULL) {
		if (curr->next->w == dest) {
			delete = curr->next;
			if (delete->next != NULL) curr->next = delete->next;
			else curr->next = NULL;
			free(delete);
			g->nE--;
			return;
		}
		curr = curr->next;
	}
}

bool adjacent(Graph g, Vertex src, Vertex dest) {
	if (g == NULL) return 0;
	AdjList curr = g->NodeList[src]->next;
	while(curr != NULL) {
		if (curr->w == dest) return true;
		curr = curr->next;
	}
	return false;
}

AdjList outIncident(Graph g, Vertex v) {
	return NULL;
}

AdjList inIncident(Graph g, Vertex v) {
	return NULL;
}

void  showGraph(Graph g) {

}

void  freeGraph(Graph g) {
	if (g == NULL) return;

	for(int i = 0; i < g->nV; i++) {
		AdjList curr = g->NodeList[i], old;
		while(curr != NULL) {
			old = curr;
			curr = curr->next;
			free(old);
		}
	}
	free(g->NodeList);
	free(g);
}

static AdjList newAdjListnode(Vertex w, int weight) {
	AdjList node = malloc(sizeof(node));
	node->weight = weight;
	node->w = w;
	node->next = NULL;
	return node;
}
