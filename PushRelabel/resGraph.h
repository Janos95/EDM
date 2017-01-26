//
//  resGraph.hpp
//  push relabel
//
//  Created by Janos Meny on 26.12.16.
//  Copyright © 2016 Janos Meny. All rights reserved.
//

#ifndef RESGRAHP_H
#define RESGRAHP_H

#include <vector>

struct Edge;
typedef std::vector<Edge>::iterator edge_iter;

struct Node;
typedef std::vector<Node>::iterator node_iter;

struct Edge{
    Edge(node_iter head, int resCap): resCap(resCap), head(head){}
    int resCap;
    edge_iter rev;
    node_iter head;
};


struct Node{
    Node(): distance(0), exc(0) {}
    node_iter bNext; /* next active node with same distance label */
    edge_iter current;
    edge_iter first;
    int distance;
    int exc;
};

class resGraph {
public:
    resGraph(char const* filename);
    void print();
    
    node_iter source;
    node_iter sink;
    int n; /* number of nodes */
    int m; /* number of edges */
    std::vector<Edge> edges; /* array of edges, sorted by tail */
    std::vector<Node> nodes; /* pretty self explanatory */
    std::vector<int> flow; /* i th entry stores pointer to edge with index i */
};

#endif 
