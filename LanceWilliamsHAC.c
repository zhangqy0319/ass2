/*Lance-Williams Algorithm for Agglomerative Clustering
  Written by 
  COMP2521 2019 T1
*/
#include <stdlib.h>
#include <stdio.h>
#include "LanceWilliamsHAC.h"
#include "Graph.h"
#define numVertices numVerticies
#define INF __INT_MAX__

static int cmp(int, int, int method);
static Dendrogram newDNode(int vertex);

/* 
 * Finds Dendrogram using Lance-Williams algorithm (as discussed in the specs) 
   for the given graph g and the specified method for agglomerative clustering.
   Method value 1 represents 'Single linkage', and 2 represents 'Complete linkage'.
   For this assignment, you only need to implement the above two methods. 

   The function returns 'Dendrogram' structure (binary tree) with the required information.
 * 
 */
Dendrogram LanceWilliamsHAC(Graph g, int method) {
	int num = numVerticies(g), boundary, size = num;
	if (method == 1) boundary = INF;
	else if (method == 2) boundary = -1;
	double **dist = malloc(num * sizeof(double*));
	Dendrogram *DDlist = malloc(num * sizeof(Dendrogram));
	for (Vertex i = 0; i < num; i++){
		dist[i] = malloc(num * sizeof(Vertex));
		DDlist[i] = newDNode(i);
		for (Vertex j = 0; j < num; j++) dist[i][j] = boundary;
	}

	int findval, findrow, findcol;
	while(size != 1){
		findval = findrow = findcol = boundary; 
		for (Vertex src = 0; src < num; src++){
			AdjList curr = outIncident(g, src);
			while (curr != NULL){
				Vertex dest = curr->w;
				dist[src][dest] = 1 / curr->weight;
				if (src > dest){
					int value = cmp(dist[src][dest], dist[dest][src], method);
					dist[src][dest] = dist[dest][src] = value;
					findval = cmp(findval, value, method);
					if (findval == value){
						findrow = src;
						findcol = dest;
					}
				}
				curr = curr->next;
			}
		}

		Dendrogram joint = newDNode(boundary);
		joint->left = findrow;
		joint->right = findcol;
		DDlist[findrow] = joint;
		size--;
	}
    return NULL;
}


void freeDendrogram(Dendrogram d) {
	if (d->left != NULL) freeDendrogram(d->left);
	if (d->right != NULL) freeDendrogram(d->right);
	free(d);
	return;
}

static int cmp(int a, int b, int method){
	if (method == 1) return (a < b ? a : b);
	if (method == 2) return (a > b ? a : b);
	return -1;
}

static Dendrogram newDNode(int vertex){
	Dendrogram new = malloc(sizeof(Dendrogram));
	new->left = new->right = NULL;
	new->vertex = vertex;
	return new;
}