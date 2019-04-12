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
	g->outNodeList = malloc(noNodes * sizeof(AdjList)); //initialize outNodeList
	for (int i = 0; i < noNodes; i++){
		g->outNodeList[i] = newAdjListnode(i, 0);
	} 
	g->inNodeList = malloc(noNodes * sizeof(AdjList)); //initialize intNodeList
	for (int i = 0; i < noNodes; i++){
		g->inNodeList[i] = newAdjListnode(i, 0);
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
	if (g->outNodeList[src]->next == NULL) { //initialize outNodeList
		AdjList newnode = newAdjListnode(dest, weight);
		g->outNodeList[src]->next = newnode;
		g->nE++;
	}
	else {
		AdjList curr = g->outNodeList[src]->next;
		while(curr->next != NULL) curr = curr->next;
		AdjList newnode = newAdjListnode(dest, weight);
		curr->next = newnode;
		g->nE++;
	}

	if (g->inNodeList[dest]->next == NULL) { //initialize inNodeList
		AdjList newnode = newAdjListnode(src, weight);
		g->inNodeList[dest]->next = newnode;
	}
	else {
		AdjList curr = g->inNodeList[dest]->next;
		while(curr->next != NULL) curr = curr->next;
		AdjList newnode = newAdjListnode(src, weight);
		curr->next = newnode;
	}
}

void  removeEdge(Graph g, Vertex src, Vertex dest) {
	if (g == NULL) return;
	if (!adjacent(g, src, dest)) return;
	//initialize outNodeList
	AdjList delete,	 curr = g->outNodeList[src]->next;
	if (curr->w == dest) {
		delete = curr;
		g->outNodeList[src]->next = delete->next;
		free(delete);
		g->nE--;
	}
	else {
		while(curr->next != NULL) {
			if (curr->next->w == dest) {
				delete = curr->next;
				if (delete->next != NULL) curr->next = delete->next;
				else curr->next = NULL;
				free(delete);
				g->nE--;
				break;
			}
			curr = curr->next;
		}
	}
	// //initialize inNodeList
	AdjList delete1,	 curr1 = g->inNodeList[dest]->next;
	if(curr1->w == src) {
		delete1 = curr1;
		g->inNodeList[dest]->next = delete1->next;
		free(delete1);
	}
	else {
		while(curr1->next != NULL) {
			if (curr1->next->w == src) {
				delete1 = curr1->next;
				if (delete1->next != NULL) curr1->next = delete1->next;
				else curr1->next = NULL;
				free(delete1);
				break;
			}
			curr1 = curr1->next;
		}
	}


}

bool adjacent(Graph g, Vertex src, Vertex dest) {
	if (g == NULL) return 0;
	AdjList curr = g->outNodeList[src]->next;
	while(curr != NULL) {
		if (curr->w == dest) return true;
		curr = curr->next;
	}
	return false;
}

AdjList outIncident(Graph g, Vertex v) {
	if (g == NULL) return NULL;
	int j = 0;
	while((g->outNodeList[j] != NULL) && (j < g->nV)) {
		if(g->outNodeList[j]->w == v) {
			break;          
		}
		j++;
	}
	AdjList vnode = g->outNodeList[j];//find the node whose Vertex is equal to v
	return vnode->next;
}

AdjList inIncident(Graph g, Vertex v) {
	if (g == NULL) return NULL;
	int j = 0;
	while((g->inNodeList[j] != NULL) && (j < g->nV)) {
		if(g->inNodeList[j]->w == v) {
			break;          
		}
		j++;
	}
	AdjList vnode = g->inNodeList[j];//find the node whose Vertex is equal to v
	return vnode->next;
// 	AdjList head = NULL, curr ,subcurr;
// 	int i = 0;
// 	while (g->outNodeList[i] != NULL)
// 	{
// 		curr = g->outNodeList[i]->next;
// 		while (curr != NULL)
// 		{
// 			if (curr->w == v)
// 			{
// 				AdjList new = newAdjListnode(i,curr->weight);
// 				if (head == NULL) 
// 				{
// 					head = new;
// 					subcurr = head;
// 				}
// 				else
// 				{
// 					subcurr->next = new;
// 					subcurr = subcurr->next;
// 				}
				
// 			}
// 			curr = curr->next;
// 		}
// 		i++;
// 	}
// 	return head;
// }

// void  showGraph(Graph g) {
// 	if (g == NULL) return;
// 	printf ("The number of V=%d, The number of E=%d\n", g->nV, g->nE);
// 	int i = 0;
// 	while((g->outNodeList[i] != NULL) && (i < g->nV)) {
// 		AdjList temp = g->outNodeList[i];
// 		while(temp->next != NULL) {
// 			printf("From Vertex [%d] to Vertex [%d], the weight is %d\n", 
// 			temp->w, temp->next->w, temp->next->weight);
// 			temp = temp->next;
// 		}
// 		i++;
// 	}
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
	}
	for(int i = 0; i < g->nV; i++) {
		AdjList curr = g->inNodeList[i], old;
		while(curr != NULL) {
			old = curr;
			curr = curr->next;
			free(old);
		}
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
