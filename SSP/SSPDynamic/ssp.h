#include <vector>

#ifndef SSP_H
#define SSP_H

#include "resGraph.h"
#include "Plist.h"

class Ssp {
 public:
            std::vector<node_iter> positive;
            resGraph &g;
            Plist *pqueue;
            bool Process(node_iter v);
            void Augment(node_iter v,node_iter w);
 
            Ssp(resGraph &g_f);
            bool Run();
            void bPrint();
            bool isBFlow();
            node_iter GetTail(edge_iter edge);
            void MBF();
            node_iter negCycle();
};

#endif
