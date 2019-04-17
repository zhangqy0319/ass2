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
	if (method == 1) boundary = -1;
	else if (method == 2) boundary = INF;
	int **dist = malloc(num * sizeof(int*));
	Dendrogram *DDlist = malloc(num * sizeof(Dendrogram));
	for (Vertex i = 0; i < num; i++){
		dist[i] = malloc(num * sizeof(Vertex));
		DDlist[i] = newDNode(i);
		for (Vertex j = 0; j < num; j++) dist[i][j] = boundary;
	}

	// Set up dist table
	for (Vertex src = 0; src < num; src++){
		AdjList curr = outIncident(g, src);
		while (curr != NULL){
			Vertex dest = curr->w;
			dist[src][dest] = curr->weight;
			if (cmp(dist[src][dest], dist[dest][src], method))
				dist[dest][src] = dist[src][dest];
			else dist[src][dest] = dist[dest][src];
		curr = curr->next;			
		}
	}
	// for (int i = 0; i<num;i++){
	// 	for(int j = 0; j<=i;j++){
	// 		printf("%d, ",dist[i][j]);
	// 	}
	// 	printf("\n");
	// }
	// Merge
	int findsrc, finddest, findvalue;
	while(size > 1){
		findsrc = finddest = findvalue = boundary;
// printf("num: %d\n",size);
// for (int i = 0; i < num; i++) printf("%d, ",DDlist[i]->vertex);
// printf("\n");
		for (int i = num-1; i > 0; i--){
			for (int j = i-1; j >= 0; j--){
				if (cmp(dist[i][j], findvalue, method)){
					findsrc = i;
					finddest = j;
					findvalue = dist[i][j];
				}
			}
		}
		dist[findsrc][finddest] = boundary;
		Dendrogram left = DDlist[finddest], right = DDlist[findsrc];
		// while the node does not point itself or not point the joint
		// It means the node has merged to main tree, jump to main tree
		int mergeout = findsrc;
		while (right->vertex != findsrc && right->vertex != boundary){
			mergeout = right->vertex;
			right = DDlist[ right->vertex ];
		}
		int mergein = finddest; // Used to save the merge postition in DDlist
		while (left->vertex != finddest && left->vertex != boundary){
			mergein = left->vertex;
			left = DDlist[ mergein ];
		}
		// Two nodes/trees have merged
		if (left == right) continue;
		// Merge leftward always
		if (mergein > mergeout){
			int tmp = mergein;
			mergein = mergeout;
			mergeout = tmp;
		}
		Dendrogram joint = newDNode(boundary);
		joint->left = left;
// printf("left ver: %d\n", left->vertex);
		joint->right = right;
// printf("right ver: %d\n", right->vertex);
		DDlist[mergein] = joint; // Plant a tree
		// Contain the position where the node was merged
		DDlist[mergeout] = newDNode(mergein);
		size--;
	}
	// Final process
	Dendrogram root = DDlist[0];
	DDlist[0] = NULL;
	for (int i = 0; i < num; i++) free(dist[i]);
	for (int i = 1; i < num; i++) free(DDlist[i]);
	free(dist);
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
	if (method == 1) return (a > b);
	if (method == 2) return (a < b);
	return -1;
}

static Dendrogram newDNode(int vertex){
	Dendrogram new = malloc(sizeof(Dendrogram));
	new->left = new->right = NULL;
	new->vertex = vertex;
	return new;
}
