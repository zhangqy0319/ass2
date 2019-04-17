/*Lance-Williams Algorithm for Agglomerative Clustering
  Written by 
  COMP2521 2019 T1
*/
#include <stdlib.h>
#include <stdio.h>
#include "LanceWilliamsHAC.h"
#include "Graph.h"
#include "PQ.h"
#define numVertices numVerticies
#define INF __INT_MAX__

static int cmp(int, int, int method);
static Dendrogram newDNode(int vertex);
static int index2key(int r, int c, int size);
static void key2index(int key, int size, int* index);

/* 
 * Finds Dendrogram using Lance-Williams algorithm (as discussed in the specs) 
   for the given graph g and the specified method for agglomerative clustering.
   Method value 1 represents 'Single linkage', and 2 represents 'Complete linkage'.
   For this assignment, you only need to implement the above two methods. 

   The function returns 'Dendrogram' structure (binary tree) with the required information.
 * 
 */
Dendrogram LanceWilliamsHAC(Graph g, int method) {
	int num = numVerticies(g), boundary;
	if (method == 1) boundary = -1;
	else if (method == 2) boundary = INF;
	int **dist = malloc(num * sizeof(int*));
	Dendrogram *DDlist = malloc(num * sizeof(Dendrogram));
	for (Vertex i = 0; i < num; i++){
		dist[i] = malloc(num * sizeof(Vertex));
		DDlist[i] = newDNode(i);
		for (Vertex j = 0; j < num; j++) dist[i][j] = boundary;
	}
	PQ todo = newPQ();

	// Set up dist table and add to PQ according to dist
	for (Vertex src = 0; src < num; src++){
		AdjList curr = outIncident(g, src);
		while (curr != NULL){
			Vertex dest = curr->w;
			dist[src][dest] = curr->weight;
			if (src > dest){
				int value = cmp(dist[src][dest], dist[dest][src], method);
				dist[src][dest] = dist[dest][src] = value;
				if (method == 1) value = INF - value;
				ItemPQ node = {.key = index2key(src, dest, num), .value = value};
				addPQ(todo, node);
			}
			curr = curr->next;
		}
	}

	// Merge leftward in the DDlist

	int index[2] = {boundary, boundary};
	while(!PQEmpty(todo)){
		int key = dequeuePQ(todo).key;
		key2index(key, num, index);
		int findsrc = index[0];
		int finddest = index[1];
		Dendrogram left = DDlist[finddest], right = DDlist[findsrc];

		// while the node does not point itself or not point the joint
		// It means the node has merged to main tree, jump to main tree
		while (right->vertex != findsrc && right->vertex != boundary)
			right = DDlist[ right->vertex ];
		int position = boundary; // Used to save the merge postition in DDlist
		while (left->vertex != finddest && left->vertex != boundary){
			position = left->vertex;
			left = DDlist[ position ];
		}
		// Two nodes/trees have merged
		if (left == right) continue;
		// The merge position is a node
		if (position == boundary) position = left->vertex;
		Dendrogram joint = newDNode(boundary);
		joint->left = left;
		joint->right = right;
		DDlist[position] = joint; // Plant a tree
		// Contain the position where the node was merged
		DDlist[right->vertex] = newDNode(left->vertex);
	}

	// Final process
	Dendrogram root = DDlist[0];
	DDlist[0] = NULL;
	for (int i = 0; i < num; i++) free(dist[i]);
	for (int i = 1; i < num; i++) free(DDlist[i]);
	free(DDlist);
	free(dist);
	free(todo);
	return root;
}


void freeDendrogram(Dendrogram d) {
	if (d->left != NULL) freeDendrogram(d->left);
	if (d->right != NULL) freeDendrogram(d->right);
	free(d);
	return;
}

// Helper Function //

static int cmp(int a, int b, int method){
	if (method == 1) return (a > b ? a : b);
	if (method == 2) return (a < b ? a : b);
	return -1;
}

static Dendrogram newDNode(int vertex){
	Dendrogram new = malloc(sizeof(Dendrogram));
	new->left = new->right = NULL;
	new->vertex = vertex;
	return new;
}

static int index2key(int r, int c, int size){
	return r *  size + c;
}

static void key2index(int key, int size, int* index){
	index[0] = key / size;
	index[1] = key % size;
}