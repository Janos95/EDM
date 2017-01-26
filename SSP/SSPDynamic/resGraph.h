#include <vector> 
#include <fstream>


#ifndef resGraph_h
#define resGraph_h

struct Edge;
typedef std::vector<Edge>::iterator edge_iter;

struct Node;
typedef std::vector<Node>::iterator node_iter;

struct Edge{
    Edge(node_iter head, long resCap, long c): head(head), resCap(resCap), c(c){}
    node_iter head;
    long resCap;
    long c;
    edge_iter rev;
};

struct Node{
    node_iter parent; /* next active node with same distance label */
    edge_iter current;
    edge_iter first;
    bool inHeap;
    long b;
    long dist;
    long pot;
    long heapPos;
};

class resGraph {
public:
    resGraph(std::ifstream&);
    void print();
    void readFlow(std::ifstream&);
    
    node_iter source;
    node_iter sink;
    long n; /* number of nodes */
    long m; /* number of edges */
    std::vector<Edge> edges; /* array of edges, sorted by tail */
    std::vector<Node> nodes; /* pretty self explanatory */
    std::vector<long> flow; /* stores indices in the original order */
    std::vector<long> b_values; /* b values */
};

#endif /* resGraph_h */
