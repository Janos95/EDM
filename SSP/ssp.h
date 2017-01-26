#include <vector>

#ifndef SSP_H
#define SSP_H

#include "resGraph.h"
#include "Pqueue.h"

class Ssp {
 public:
            std::vector<node_iter> positive;
            resGraph g;
            Pqueue pqueue;
            bool Process(node_iter v);
            void Augment(node_iter v,node_iter w);
 
            Ssp(std::ifstream&);
            bool Run();
            void bPrint();
};

#endif
