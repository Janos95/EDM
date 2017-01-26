#ifndef PLIST_H
#define PLIST_H

#include "resGraph.h"

class Plist{
private:
   resGraph &g;
   long size;             // how many nodes are currently in the heap
    std::vector<node_iter> perm;
   
public:
   Plist(resGraph &g_f);
   node_iter Dijkstra(node_iter v);// run dijkstra's algo
   void Insert(node_iter v);            // adds--TO END--of heap
   node_iter RemoveMin();                  // returns top element and sifts
   bool IsEmpty()     
         { return size == 0; }         // nothing in our heap
   void Empty()  { size = 0; perm.clear();}         // empty our heap
   bool InList(node_iter v)
         { return v -> inHeap; }
};

#endif
