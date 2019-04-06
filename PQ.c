# include <stdio.h>
# include "PQ.h"

PQ newPQ();

void  addPQ(PQ, ItemPQ);

ItemPQ  dequeuePQ(PQ);

void  updatePQ(PQ, ItemPQ);

int PQEmpty(PQ);

void  showPQ(PQ);
void  freePQ(PQ);
