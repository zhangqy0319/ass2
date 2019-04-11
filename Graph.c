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
	g->NodeList = malloc(noNodes * sizeof(AdjList));
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
		g->nE++;
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
	if (g == NULL) return NULL;
	int j = 0;
	while((g->NodeList[j] != NULL) && (j < g->nV)) {
		if(g->NodeList[j]->w == v) {
			break;          
		}
		j++;
	}
	AdjList vnode = g->NodeList[j];//find the node whose Vertex is equal to v
	return vnode->next;
}

AdjList inIncident(Graph g, Vertex v) {
	if (g == NULL) return NULL;
	AdjList head = NULL, curr ,subcurr;
	int i = 0;
	while (g->NodeList[i] != NULL)
	{
		curr = g->NodeList[i]->next;
		while (curr != NULL)
		{
			if (curr->w == v)
			{
				AdjList new = newAdjListnode(i,curr->weight);
				if (head == NULL) 
				{
					head = new;
					subcurr = head;
				}
				else
				{
					subcurr->next = new;
					subcurr = subcurr->next;
				}
				
			}
			curr = curr->next;
		}
		i++;
	}
	return head;
}

void  showGraph(Graph g) {
	if (g == NULL) return;
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
