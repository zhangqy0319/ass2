# include <stdio.h>
# include "CentralityMeasures.h"

NodeValues outDegreeCentrality(Graph);
NodeValues inDegreeCentrality(Graph);
NodeValues degreeCentrality(Graph); // for undirected graph

NodeValues closenessCentrality(Graph);

NodeValues betweennessCentrality(Graph);
NodeValues betweennessCentralityNormalised(Graph);


void  showNodeValues(NodeValues);
void  freeNodeValues(NodeValues);
