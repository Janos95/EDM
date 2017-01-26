#include "plist.h"
#include <limits>
#include <assert.h>
#define INFTY std::numeric_limits<long>::max()

Plist::Plist(resGraph &g_f) : g(g_f), size(0) { perm.reserve(g.n); }

void Plist::Insert(node_iter v) {
  v->inHeap = true;
  size++;
}

/* only to be applied to a nonempty plist */
node_iter Plist::RemoveMin() {
  node_iter minNode = g.nodes.begin();
  for (; not minNode->inHeap; minNode++)
    ;
  for (auto v = minNode + 1; v != g.nodes.end() - 1; v++) {
    if (v->dist < minNode->dist and v->inHeap)
      minNode = v;
  }
  minNode->inHeap = false;
  size--;
  return minNode;
}

/* performs dijkstra from v and return first node that has negative b value if existent
otherwise returns end of node vector */
node_iter Plist::Dijkstra(node_iter v) {
  node_iter currentNode, newNode; 
  edge_iter last;                

  /* setting distance labels to infinity */
  for (auto w = g.nodes.begin(); w != g.nodes.end(); w++) {
    w->dist = INFTY;
  }
  v->dist = 0;

  Empty();
  Insert(v);

  while (not IsEmpty()) {
    currentNode = RemoveMin();
    perm.push_back(currentNode);
    if (currentNode->b < 0) {
      /* current Node works, so we clean up the Plist,
      update the node potentials and return the current Node*/
      long distB = currentNode->dist;
      for (auto w = g.nodes.begin(); w != g.nodes.end() - 1; w++)
        w->inHeap = false;
      for (auto &w : perm)
        w->pot += (distB - w->dist);
      return currentNode;
    }
    last = (currentNode + 1)->first;
    for (auto e = currentNode->first; e != last; e++) {
      newNode = e->head;
      if (e->resCap > 0 and
          currentNode->dist + (e->c + e->head->pot - currentNode->pot) <
              newNode->dist) {
        /* this way is shorter. Hence we update the sp tree */
        // assert((e->c + e -> head -> pot - currentNode -> pot) >= 0);
        newNode->dist =
            currentNode->dist + (e->c + e->head->pot - currentNode->pot);
        newNode->parent = currentNode;
        newNode->current = e;
        if (not InList(newNode))
          Insert(newNode);
      }
    }
  }
  /* there is no node with negative b reachabel from v.
  This means that there is no b-flow. */
  return g.nodes.end();
}
