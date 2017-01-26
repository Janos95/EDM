#include "ssp.h"
#include <iostream>
#include <list>
#include <assert.h>

#define INFTY std::numeric_limits<long>::max() / 2

/* for a node with positive b value find a sp to a node w with negative b value. 
Augment the v -> w path. If the b value of b got positive insert it. 
If the b value of v got negative extract it.*/
bool Ssp::Process(node_iter v) {
  node_iter w = pqueue->Dijkstra(v);
  if (w == g.nodes.end())
    return false;
  Augment(v, w);
  if (w->b > 0)
    positive.push_front(w);

  if (v->b <= 0)
    positive.pop_back();
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

Ssp::Ssp(resGraph &g_f) : g(g_f) {
  for (auto v = g.nodes.begin(); v != g.nodes.end() - 1; v++) {
    if (v->b > 0)
      positive.push_back(v);
  }
  pqueue = new Plist(g);
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

  // assert(isBFlow());
  // MBF();
  // node_iter v = negCycle();
  // assert(v == g.nodes.end());
  g.print();
  std::cout << cost << std::endl;
}

// This can be done way faster.
node_iter Ssp::GetTail(edge_iter edge) {
  for (auto v = g.nodes.begin(); v != g.nodes.end() - 1; v++)
    for (auto e = v->first; e != (v + 1)->first; e++)
      if (e == edge)
        return v;
  return g.nodes.end();
}

bool Ssp::isBFlow() {
  node_iter v;
  edge_iter e;
  for (auto i : g.flow) {
    e = g.edges.begin() + i;
    v = GetTail(e);
    g.b_values[std::distance(g.nodes.begin(), v)] -= e->rev->resCap;
    g.b_values[std::distance(g.nodes.begin(), e->head)] += e->rev->resCap;
  }
  for (auto b : g.b_values)
    if (b != 0)
      return false;
  return true;
}

/* checking minimality by searching for negative cycles in the residual graph */
void Ssp::MBF() {
  for (auto &v : g.nodes)
    v.dist = INFTY;
  g.nodes[0].dist = 0;

  for (int i = 0; i < g.n - 1; i++) {
    for (auto v = g.nodes.begin(); v != g.nodes.end() - 1; v++) {
      for (auto e = v->first; e != (v + 1)->first; e++) {
        if (e->resCap > 0 and v->dist + e->c < e->head->dist) {
          e->head->dist = v->dist + e->c;
          e->head->parent = v;
          e->head->current = e;
        }
      }
    }
  }
}

node_iter Ssp::negCycle() {
  for (auto v = g.nodes.begin(); v != g.nodes.end() - 1; v++) {
    for (auto e = v->first; e != (v + 1)->first; e++) {
      if (e->resCap > 0 and v->dist + e->c < e->head->dist) {
        std::vector<bool> visited(g.n, false);
        int iNode = std::distance(g.nodes.begin(), e->head);
        visited[iNode] = true;
        node_iter w = v;
        iNode = std::distance(g.nodes.begin(), v);
        while (not visited[iNode]) {
          visited[iNode] = true;
          v = v->parent;
          iNode = std::distance(g.nodes.begin(), v);
        }
        if (v == e->head) {
          v->parent = w;
          v->current = e;
        }
        return v;
      }
    }
  }
  return g.nodes.end();
}
