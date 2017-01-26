#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include "resGraph.h"

/* assumes input format is as in the second programming exercise.
 returns the residual graph corresponding to the zero flow */
resGraph::resGraph(char const* filename)
{
    /* internal arrays: */
    std::vector<int> edge_tail;
    std::vector<int> first;
    std::vector<int> index;
    
    /* ----------------------------- reading input file ----------------------------- */
    
    std::ifstream file(filename);
    if (not file) {
        throw std::runtime_error("Cannot open file.");
    }
    
    //reading first line which is the number of nodes.
    int num = 0;
    std::string line;
    std::getline(file, line);
    std::stringstream ss(line);
    ss >> num;
    n = num;
    
    //allocating memory.
    nodes.assign(n+1,Node());
    first.resize(n+1);
    
    source = nodes.begin();
    sink = nodes.begin()+1;
    
    int i = 0;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        int head, tail;
        ss >> tail >> head;
        int u;
        ss >> u;
        
        edges.push_back(Edge(nodes.begin()+head, u));
        edges.push_back(Edge(nodes.begin()+tail, 0));
        
        index.push_back(i);
        index.push_back(-1);
        
        edge_tail.push_back(tail);
        edge_tail.push_back(head);
        first[tail+1]++;
        first[head+1]++;
        
        i++;
    }
    m = edges.size();
    
    for(int i = 0; i < m; i+=2){
        edges[i].rev = edges.begin() + i + 1;
        edges[i+1].rev = edges.begin() + i;
    }
    
    /* --------------- linear time algorithm for sorting edges --------------- */
    
    /* at this moment the i+1'th enty of first contains the out degree of the i'th node
     after the next loop the i'th entry contains the index of the first edge leaving the i'th node */
    nodes[0].first = nodes[0].current = edges.begin();
    for(int i = 1; i < n+1; ++i){
        first[i] += first[i-1];
        nodes[i].first = nodes[i].current = edges.begin() + first[i];
    }
    
    /* temprorary variables */
    int tail,last,edge_num,edge_new_num;
    edge_iter edge_current,edge_new;
    
    /* When I wrote this, only God and I understood what I was doing.
    Now, God only knows */
    for ( int i = 0; i < n-1; i++) /* scanning all the nodes
                                    exept the last*/
    {
        
        last =  std::distance(edges.begin(),nodes[i + 1].first);
        /* edges outgoing from v must be cited
         from position first[v] to the position
         equal to initial value of first[v+1]-1  */
        
        for ( edge_num = first[i]; edge_num < last; edge_num ++ )
        {
            tail = edge_tail[edge_num];
            
            while ( tail != i )
            /* the edge no  edge_num  is not in place because edge cited here
             must go out from i;
             we'll put it to its place and continue this process
             until an edge in this position would go out from i */
                
            {
                edge_new_num  = first[tail];
                edge_current  = edges.begin() + edge_num;
                edge_new      = edges.begin() + edge_new_num;
                
                /* keeping track of original index for output */
                std::swap(index[edge_num],index[edge_new_num]);
                
                /* edge_current must be cited in the position edge_new
                 swapping these edge:                                 */
                std::swap(edge_current -> head,edge_new -> head);
                std::swap(edge_current -> resCap, edge_new -> resCap);
                
                if ( edge_new != edge_current -> rev )
                {
                    std::swap(edge_current -> rev, edge_new -> rev);
                    ( edge_current -> rev ) -> rev = edge_current;
                    ( edge_new     -> rev ) -> rev = edge_new;
                }
                
                edge_tail[edge_num] = edge_tail[edge_new_num];
                edge_tail[edge_new_num] = tail;
                
                /* we increase first[tail]  */
                first[tail] ++ ;
                
                tail = edge_tail[edge_num];
            }
        }
        /* all edges outgoing from  i  are in place */
    }
    
    /* gathering indices of original edges of the graph in flow */
    for(int i = 0; i < m; i++){
        if(index[i] >= 0)
            flow.push_back(i);
        
    }
    /* after the sort procedure the i'th entry of flow is the index
     of the edge with original index i */
    std::sort(flow.begin(),flow.end(), [&](const int a ,const int b) -> bool
              {
                  return index[a] < index[b];
              });
    
    /* finally done */
}


void resGraph::print(){
    for(int i = 0; i < m/2; ++i)
        std::cout << i << " " << edges[flow[i]].rev -> resCap << std::endl;
    std::cout << nodes[1].exc <<  std::endl;
}
