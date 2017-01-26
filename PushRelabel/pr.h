//
//  resGraph.hpp
//  push relabel
//
//  Created by Janos Meny on 26.12.16.
//  Copyright © 2016 Janos Meny. All rights reserved.
//

#ifndef PR_H
#define PR_H

#include "resGraph.h"

class PushRelabel {
private:
    resGraph &g;
    std::vector<node_iter> buckets; /* i'th entry stores a pointer to the first active node
                                     with distance label i  */
    long aMax; /* maximum active node label */
    long nMax; /* highest active label lower than n */

    inline bool Admissible(node_iter v, edge_iter e);
    inline bool Allowed(node_iter v);
    void Remove(int b, node_iter v);
    void Add(int b, node_iter v);
    void Push(node_iter v, edge_iter e);
    void Relabel(node_iter v);
    void Discharge(node_iter v);
public:
    void Run();
    PushRelabel(resGraph &g_f);

};

#endif
