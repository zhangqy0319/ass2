// PQ ADT interface for Ass2 (COMP2521)
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct PQnodeRep *PQnode;

struct PQnodeRep{
	ItemPQ item;
	PQnode next;
};

struct PQRep {
	PQnode head;
	int len;
};

static PQnode newPQnode(ItemPQ item);


PQ newPQ() {
	PQ pq = malloc(sizeof(PQ));
	if (pq == NULL) return NULL;
	pq->len = 0;
	pq->head = NULL;
	return pq;
}

int PQEmpty(PQ p) {
	return p->len == 0;
}

void addPQ(PQ pq, ItemPQ element) {
	PQnode new = newPQnode(element), curr;
	if(pq->len == 0) pq->head = new;
	else{
		curr = pq->head;
		while (curr->next != NULL) curr = curr->next;
		curr->next = new;
	}
	pq->len++;
}

ItemPQ dequeuePQ(PQ pq) {
	assert(pq != NULL);
	ItemPQ throwAway = {0};
	if (pq->len == 1){
		throwAway = pq->head->item;
		free(pq->head);
		pq->head = NULL;
	}
	else{
		PQnode curr = pq->head, mark;
		throwAway = pq->head->item;
		while(curr != NULL){
			if (curr->item.value < throwAway.value){
				mark = curr;
				throwAway = curr->item;
			}
			curr = curr->next;
		}
		curr = pq->head;
		while (curr->next != mark) curr = curr->next;
		curr->next = mark->next;
		free(mark);
	}
	pq->len--;
	return throwAway;
}

void updatePQ(PQ pq, ItemPQ element) {
	assert(pq != NULL);
	PQnode curr = pq->head;
	while (curr != NULL){
		if (curr->item.key == element.key){
			curr->item =element;
			break;
		}
		curr = curr->next;
	}
}

void  showPQ(PQ pq) {
	assert(pq != NULL);
	PQnode curr = pq->head;
	while (curr != NULL){
		printf("Key: %d, Value: %d\n",curr->item.key,curr->item.value);
		curr = curr->next;
	}
	
}

void  freePQ(PQ pq) {
	assert(pq != NULL);
	PQnode curr = pq->head, old;
	while (curr != NULL){
		old = curr;
		curr = curr->next;
		free(old);
	}
	free(pq);
}

static PQnode newPQnode(ItemPQ item){
	PQnode node = malloc(sizeof(node));
	if (node == NULL) return NULL;
	node->item = item;
	node->next = NULL;
	return node;
}
