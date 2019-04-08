// Graph ADT interface for Ass2 (COMP2521)
#include <stdlib.h>
#include <stdio.h>

#include "Graph.h"

struct GraphRep{
	int nV;
	int nE;
	AdjList *NodeList; // List of nodes in graph
};



Graph newGraph(int noNodes) {
	if (noNodes == 0) return NULL;

	Graph g = malloc( sizeof *g);
	if (g == NULL) return NULL;

	g->nV = noNodes;
	g->nE = 0;
	g->NodeList[noNodes]; 
	return g;
}

int numVerticies(Graph g) {
	if (g == NULL) {
		return 0;
	}
	return g->nV;
}

void  insertEdge(Graph g, Vertex src, Vertex dest, int weight) {
	
}

void  removeEdge(Graph g, Vertex src, Vertex dest) {

}

bool adjacent(Graph g, Vertex src, Vertex dest) {
	return false;
}

AdjList outIncident(Graph g, Vertex v) {
	assert g != NULL;
	AdjList *list_of_outgoing_nodes; // create a list which is uesd to store outIncident nodes
	int j = 0;
	while(g->NodeList[j] != NULL) {
		if(g->NodeList[j]->w == v) {
			AdjList vnode = g->NodeList[j];//find the node whose Vertex is equal to v
			break;          
		}
		j++;
	}
	int i = 0;
	int j = 0;
	while(g->NodeList[j] != NULL) {
		if(vnode->next->w == g->NodeList[j]->w) {
			list_of_outgoing_nodes[i] = g->NodeList[j];
			i++;
		}
		j++;
	}
	return *list_of_outgoing_nodes;
}

AdjList inIncident(Graph g, Vertex v) {
	return NULL;
}

void  showGraph(Graph g) {

}

void  freeGraph(Graph g) {
	if (g == NULL) return;

	for(int i = 0; i < g->nV; i++){
		AdjList curr = g->NodeList[i], old;
		while(curr != NULL){
			old = curr;
			curr = curr->next;
			free(old);
		}
	}
	free(g->NodeList);
	free(g);
}

