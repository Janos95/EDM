#include "ssp.h"
#include <iostream>
#include <list>
#include <assert.h>

#define INFTY std::numeric_limits<long>::max() / 2

/* for a node with positive b value find a sp to a node w with negative b value. 
Augment the v -> w path. If the b value of b got positive insert it. 
If the b value of v got negative extract it.*/
bool Ssp::Process(node_iter v) {
  node_iter w = pqueue.Dijkstra(v);
  if (w == g.nodes.end())
    return false;
  Augment(v, w);

  if (v->b <= 0)
    positive.pop_back();
  if (w->b > 0)
    positive.push_back(w);
  return true;
}

void Ssp::Augment(node_iter v, node_iter w) {
  node_iter a = w;
  edge_iter e = a->current;

  /* finding the minimum */
  long min = -(w->b);
  while (a != v){
    if (min > e->resCap)
      min = e->resCap;
    a = a->parent;
    e = a->current;
  } 
  if (v->b < min)
    min = v->b;

  /* augmenting path v ~> w by min */
  a = w;
  e = a->current;

  while (a != v) {
    e->resCap -= min;
    e->rev->resCap += min;

    a = a->parent;
    e = a->current;
  }

  v->b -= min;
  w->b += min;
}

Ssp::Ssp(std::ifstream &file): g(resGraph(file)), pqueue(Pqueue(g)){
  for (auto v = g.nodes.begin(); v != g.nodes.end() - 1; v++) {
    if (v->b > 0)
      positive.push_back(v);
  }
}

bool Ssp::Run() {
  while (not positive.empty()) {
    bool cc = Process(positive.back());
    if (not cc)
      return cc;
  }
  return true;
}

void Ssp::bPrint() {
  long cost = 0;
  for (auto i : g.flow)
    cost += (g.edges[i].c * g.edges[i].rev->resCap);

  g.print();
  std::cout << cost << std::endl;
}

