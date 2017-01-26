#ifndef HEAP_H
#define HEAP_H

#include "resGraph.h"
#include "pqueue.h"

class Heap : public Pqueue {
private:
   resGraph &g;
   std::vector<node_iter> heap;           // array of pointers to nodes
   long size;             // how many nodes are currently in the heap
    std::vector<node_iter> perm;
   
public:
   Heap(resGraph &g_f);
   node_iter Dijkstra(node_iter source);// run dijkstra's algo
   void MoveUp(node_iter v);            // reassigns node w/ new value and sifts
   void MoveDown(node_iter v);          // reassigns node w/ new value and sifts
   void Insert(node_iter v);            // adds--TO END--of heap
   node_iter FindMin()                     // returns top element
        { return heap[0]; }
   node_iter RemoveMin();                  // returns top element and sifts
   bool IsEmpty()     
         { return size == 0; }         // nothing in our heap
    void Empty()  { size = 0; perm.clear();}         // empty our heap
   bool InHeap(node_iter v)
         { return v -> inHeap; }
};

#endif
