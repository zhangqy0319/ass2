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
	assert (g != NULL);
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
	while(vnode != NULL) {
		list_of_outgoing_nodes[i] = vnode->next;
		vnode = vnode->next;
	}
	return list_of_outgoing_nodes;
}

AdjList inIncident(Graph g, Vertex v) {
	assert (g != NULL);
	AdjList *list_of_incoming_nodes; // create a list which is uesd to store outIncident nodes
	int i = 0;
	int j = 0;
	for (i = 0; i < g->nV; i++) {
		while(g->NodeList[i] != NULL) {
			if(g->NodeList[i]->next->w == v) {
				list_of_incoming_nodes[j] == g->NodeList[i]->next;
				j++;
			}
			g->NodeList[i] = g->NodeList[i]->next;
		}
	}
	return list_of_incoming_nodes;
}

void  showGraph(Graph g) {
	assert (g != NULL);
	printf ("The number of V=%d, The number of E=%d\n", g->nV, g->nE);
	int i = 0;
	while(g->NodeList[i] != NULL) {
		while(g->NodeList[i]->next != NULL) {
			printf("From Vertex [%d] to Vertex [%d], the weight is %d\n", 
			g->NodeList[i]->w, g->NodeList[i]->next->w, g->NodeList[i]->next->weight);
			g->NodeList[i] = g->NodeList[i]->next;
		}
		i++;
	}
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

