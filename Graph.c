// Graph ADT interface for Ass2 (COMP2521)
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
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
	int j = 0;
	while((g->NodeList[j] != NULL) && (j < g->nV)) {
		if(g->NodeList[j]->w == v) {
			break;          
		}
		j++;
	}
	AdjList vnode = g->NodeList[j];//find the node whose Vertex is equal to v
	int i = 0;
	return vnode->next;
}

AdjList inIncident(Graph g, Vertex v) {
	assert (g != NULL);
	AdjList incoming_node; // create a list which is uesd to store outIncident nodes
	AdjList head = NULL;
	int i = 0;
		while((g->NodeList[i] != NULL) && (i < g->nV)) {
			AdjList temp = g->NodeList[i];
			if(temp->next->w == v) {
				incoming_node == temp->next;
				incoming_node = incoming_node->next;
				if(head == NULL) {
					head = incoming_node;
				}
			}
			temp = temp->next;
			i++;
		}
	return incoming_node;
}

void  showGraph(Graph g) {
	assert (g != NULL);
	printf ("The number of V=%d, The number of E=%d\n", g->nV, g->nE);
	int i = 0;
	while((g->NodeList[i] != NULL) && (i < g->nV)) {
		AdjList temp = g->NodeList[i];
		while(temp->next != NULL) {
			printf("From Vertex [%d] to Vertex [%d], the weight is %d\n", 
			temp->w, temp->next->w, temp->next->weight);
			temp = temp->next;
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

