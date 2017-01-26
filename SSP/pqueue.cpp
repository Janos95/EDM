#include "pqueue.h"
#include <limits>
#include <assert.h>
#define INFTY std::numeric_limits<long>::max()

Pqueue::Pqueue(resGraph &g_f) : g(g_f), size(0) { perm.reserve(g.n); }

void Pqueue::Insert(node_iter v) {
  v->inHeap = true;
  size++;
}

/* only to be applied to a nonempty plist */
node_iter Pqueue::RemoveMin() {
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
node_iter Pqueue::Dijkstra(node_iter v) {
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
      /* current Node works, so we clean up the priority queue,
      update the node potentials and return the current Node*/
      for (auto w = g.nodes.begin(); w != g.nodes.end() - 1; w++)
        w->inHeap = false;
      /*note that v_pi = v_pi - v -> dist if v got labeled permanently and 
      v_pi = v_pi - currrentNode -> dist for all other nodes is a feasable 
      node potential for the residual graph AFTER augmentation. Adding
      currrentNode -> dist to this node potential we see that the node potential below
      also is a feasable node potential for the updatet residual graph  */ 
      long distC = currentNode->dist;
      for (auto &w : perm)
        w->pot += (distC - w->dist);
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
