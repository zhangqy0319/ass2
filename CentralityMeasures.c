// Graph ADT interface for Ass2 (COMP2521)
#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>

NodeValues outDegreeCentrality(Graph g){
	int num = numVerticies(g);
	NodeValues throwAway = {
		.noNodes = num,
		.values = malloc(num * sizeof(double))
	};
	for(int i = 0; i < num; i++){
		double count = 0;
		AdjList node = outIncident(g, i);
		while(node != NULL){
			count++;
			node = node->next;
		}
		throwAway.values[i] = count;
	}
	return throwAway;
}

NodeValues inDegreeCentrality(Graph g){
	int num = numVerticies(g);
	NodeValues throwAway = {
		.noNodes = num,
		.values = malloc(num * sizeof(double))
	};
	for(int i = 0; i < num; i++){
		double count = 0;
		AdjList node = inIncident(g, i);
		while(node != NULL){
			count++;
			node = node->next;
		}
		throwAway.values[i] = count;
	}
	return throwAway;
}

NodeValues degreeCentrality(Graph g) {
	int num = numVerticies(g);

	NodeValues throwAway = {
		.noNodes = num,
		.values = malloc(num * sizeof(double))
	};
	for(int i = 0; i < num; i++){
		double count = 0;
		AdjList node = outIncident(g, i);
		while(node != NULL){ // Out degree
			count++;
			node = node->next;
		}
		node = inIncident(g, i);
		while(node != NULL){ // In degree
			count++;
			node = node->next;
		}
		throwAway.values[i] = count;
	}
	return throwAway;
}

NodeValues closenessCentrality(Graph g){
	int num = numVerticies(g);
	NodeValues throwAway = {
		.noNodes = num,
		.values = malloc(num * sizeof(double))
	};
	for(int src = 0; src < num; src++){
		double totaldist = 0, reachnode = 0;
		ShortestPaths paths = dijkstra(g, src);
		for(int dest = 0; dest < num; dest++){
			if (paths.dist[dest] != 0){
				totaldist += paths.dist[dest];
				reachnode++;
			}
		}
		if(totaldist != 0) 
			throwAway.values[src] = reachnode*reachnode/(num-1)/totaldist;
		else throwAway.values[src] = 0;
		
		freeShortestPaths(paths);
	}
	return throwAway;
}

NodeValues betweennessCentrality(Graph g){
	int num = numVerticies(g);
	NodeValues throwAway = {
		.noNodes = num,
		.values = malloc(num * sizeof(double))
	};
	for(int i = 0; i < num; i++) throwAway.values[i] = 0;

	for(Vertex src = 0; src < num; src++){
		// Initiation
		PQ todo = newPQ();
		ShortestPaths path = dijkstra(g, src);
		// Add destination to todo accroding to the distance
		for(Vertex dest = 0; dest < num; dest++){
			// Zero distance means it is src or unreachable
			if (path.dist[dest] == 0) continue;
			ItemPQ node = {.key = dest, .value = path.dist[dest] };
			addPQ(todo, node);
		}
		// Contain the total shortest path of each dest 
		double *totalshortpath = malloc(num * sizeof(double));
		// Contain the number of passed vertices of the path from src to each dest
		double **countpasslist = malloc(num * sizeof(double*));
		for(int i = 0; i < num; i++) {
			totalshortpath[i] = 0;
			countpasslist[i] = malloc(num * sizeof(double));
			for(int j = 0; j < num; j++) countpasslist[i][j] = 0;
		}
		
		// Main process
		while(!PQEmpty(todo)){
			Vertex dest = dequeuePQ(todo).key;
			// Focus on the number of predecessors to dest
			PredNode *predcurr = path.pred[dest]; 
			while(predcurr != NULL){ // Analyse all predecessors
				// Focus on predecessors on the path
				Vertex pathcurr = predcurr->v;
				// If dest is connected to src
				if (pathcurr == src) totalshortpath[dest]++;
				while(pathcurr != src){
					// If curr vertex has been analysed, use it data
					if (totalshortpath[pathcurr] != 0){
						totalshortpath[dest] += totalshortpath[pathcurr];
						// Copy and add the vertices that the path to curr will pass
						for(int i = 0; i < num; i++){
							if (countpasslist[pathcurr][i] != 0)
								countpasslist[dest][i] += countpasslist[pathcurr][i];
						}
						countpasslist[dest][pathcurr] += totalshortpath[pathcurr];
						break;
					}
					pathcurr = path.pred[pathcurr]->v;
				}
				predcurr = predcurr->next;
			}
			// Calculate and add Betweenness to throwAway
			for(int i = 0; i < num; i++){
				if (i == src || i == dest) continue;
				double Betweenness = (countpasslist[dest][i] / totalshortpath[dest]);
				throwAway.values[i] += Betweenness;
			}
		}

		// Free
		for(int i = 0; i < num; i++) free(countpasslist[i]);
		free(countpasslist);
		free(totalshortpath);
		freePQ(todo);
		freeShortestPaths(path);
	}
	return throwAway;
}

NodeValues betweennessCentralityNormalised(Graph g){
	int num = numVerticies(g);
	NodeValues throwAway = {0};
	if (num > 2){
		throwAway = betweennessCentrality(g);
		for(int i = 0; i < num; i++)
			throwAway.values[i] /= ((num-1)*(num-2));
	}
	return throwAway;
}

void showNodeValues(NodeValues values){
	for(int i = 0; i < values.noNodes; i++)
		printf("%d: %f\n", i, values.values[i]);
}

void freeNodeValues(NodeValues values){
	free(values.values);
}
