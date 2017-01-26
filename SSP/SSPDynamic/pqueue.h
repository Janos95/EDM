#ifndef PQUEUE_H
#define PQUEUE_H

class Pqueue {
public:
    virtual node_iter Dijkstra(node_iter) = 0;
};

#endif