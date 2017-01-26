#ifndef PQUEUE_H
#define PQUEUE_H

#include "resGraph.h"

class Pqueue{
private:
   resGraph &g;
   long size;             // how many nodes are currently in the heap
   std::vector<node_iter> perm;  // stores the nodes that got marked permanently by dijsktra
   
public:
   Pqueue(resGraph &g_f);
   node_iter Dijkstra(node_iter v);
   void Insert(node_iter v);            
   node_iter RemoveMin();                  
   bool IsEmpty()     
         { return size == 0; }         
   void Empty()  { size = 0; perm.clear();}         
   bool InList(node_iter v)
         { return v -> inHeap; }
};

#endif
