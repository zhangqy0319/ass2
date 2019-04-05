
CC  = 	gcc

.PHONY:	all

all:	Graph PQ Dijkstra CentralityMeasures LanceWilliamsHAC

Graph:		Graph.o
Graph.o:	Graph.h	Graph.c

# PQ:			PQ.o
# PQ.o:		PQ.h	PQ.c

# Dijkstra:	Dijkstra.o
# Dijkstra.o:	Dijkstra.h	Dijkstra.c

# CentralityMeasures:	CentralityMeasures.o
# CentralityMeasures.o:	CentralityMeasures.h	CentralityMeasures.c

# LanceWilliamsHAC:	LanceWilliamsHAC.o
# LanceWilliamsHAC:	LanceWilliamsHAC.h	LanceWilliamsHAC.c

.PHONY:	clean

clean:
	-rm -f Graph Graph.o
	-rm -f PQ PQ.o
	-rm -f Dijkstra Dijkstra.o
	-rm -f CentralityMeasures CentralityMeasures.o
	-rm -f LanceWilliamsHAC LanceWilliamsHAC.o