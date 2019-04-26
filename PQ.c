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
	assert(pq != NULL);
	pq->len = 0;
	pq->head = NULL;
	return pq;
}

int PQEmpty(PQ p) {
	assert(p != NULL);
	return p->len == 0;
}

void addPQ(PQ pq, ItemPQ element) {
	assert(pq != NULL);
	assert(element.value >= 0);

	PQnode new = newPQnode(element), curr = pq->head;
	if(pq->len == 0) pq->head = new;
	else{
		while(curr != NULL){ // Iterate the whole list to check if it exists
			if (curr->item.key == element.key){
				updatePQ(pq, element);
				free(new); // Delete the new node
				return;
			}
			curr = curr->next;
		}
		// If the key is not in PQ
		curr = pq->head;	
		while(curr->next != NULL) curr = curr->next;
		curr->next = new;
	}
	pq->len++;
}

ItemPQ dequeuePQ(PQ pq) {
	assert(pq != NULL);
	assert(!PQEmpty(pq));

	ItemPQ throwAway = {0};
	if (pq->len == 1){
		throwAway = pq->head->item;
		free(pq->head);
		pq->head = NULL;
	}
	else{
		PQnode curr = pq->head, mark = pq->head;
		throwAway = pq->head->item;
		while(curr != NULL){
			if (curr->item.value < throwAway.value){
				mark = curr;
				throwAway = curr->item;
			}
			curr = curr->next;
		}
		curr = pq->head;
		if (curr == mark) pq->head = mark->next;
		else {
			while (curr->next != mark) curr = curr->next;
			curr->next = mark->next;
		}
		free(mark);
	}
	pq->len--;
	return throwAway;
}

void updatePQ(PQ pq, ItemPQ element) {
	assert(pq != NULL);
	assert(element.value >= 0);

	PQnode curr = pq->head, mark = NULL;
	while(curr != NULL){ // Find the same key
		if (curr->item.key == element.key){
			mark = curr;
			break;
		}
		curr = curr->next;
	}
	if (mark != NULL) { // If exist
		if (pq->head == mark){ // Check the head
			if (pq->len == 1){
				pq->head->item.value = element.value;
				return;
			}
			pq->head = mark->next;
		}
		else{
			curr = pq->head;
			while (curr->next != mark) curr = curr->next;
			curr->next = mark->next;
		}
		free(mark);
		curr = pq->head;
		while(curr->next != NULL) curr = curr->next; // Add to the end
		PQnode new = newPQnode(element);
		curr->next = new;
	}
}

void showPQ(PQ pq) {
	assert(pq != NULL);
	PQnode curr = pq->head;
	while (curr != NULL){
		printf("Key: %d, Value: %d\n", curr->item.key, curr->item.value);
		curr = curr->next;
	}
}

void freePQ(PQ pq) {
	assert(pq != NULL);
	PQnode curr = pq->head, old;
	while (curr != NULL){
		old = curr;
		curr = curr->next;
		free(old);
	}
	free(pq);
}

// Helper functions

static PQnode newPQnode(ItemPQ item){
	PQnode node = malloc(sizeof(node));
	if (node == NULL) return NULL;
	node->item = item;
	node->next = NULL;
	return node;
}
