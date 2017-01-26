//  push relabel
//
//  Created by Felix Zieger and Janos Meny
//  This is free software.

#include <ctime>
#include <algorithm>
#include <vector>
#include <iostream>
#include "pr.h"

    
/* helper predicates */
inline bool PushRelabel::Admissible(node_iter v, edge_iter e){
    return e -> head -> distance + 1 == v -> distance;
}

inline bool PushRelabel::Allowed(node_iter v){
    return v != g.sink and v != g.source;
}

/* v must be the first element in the bucket */
void PushRelabel::Remove(int b, node_iter v)
{
    buckets[b] = v->bNext;
}

void PushRelabel::Add(int b, node_iter v)
{
    v->bNext = buckets[b];
    buckets[b] = v;
    /* resetting aMax and nMax if necessary*/
    int v_dist = v -> distance;
    if(v_dist < g.n and v_dist > nMax){
            nMax = v_dist;
    }
    if(v_dist > aMax )
    {
        aMax = v-> distance;

    }
    
}

void PushRelabel::Push(node_iter v, edge_iter e)
{
    int gamma = std::min(v -> exc, e -> resCap);
    e -> resCap -= gamma;
    e -> rev -> resCap += gamma;
    if ( e -> head -> exc == 0 and Allowed(e -> head)) {
        Add(e -> head -> distance, e -> head);
    }
    e -> head -> exc += gamma;
    v -> exc -= gamma;
}

void PushRelabel::Relabel(node_iter v)
{
    int min = 2 * g.n;
    for (auto e = v -> first; e != (v+1) -> first; e++) {
        if (e -> resCap > 0) {
            if(e -> head -> distance < min){
                min = e -> head -> distance;
                v -> current = e;
            }
        }
    }
    min++;
    v -> distance = min;
}

void PushRelabel::Discharge(node_iter v)
{
    while(v -> exc > 0){
        for (auto e = v -> current; e != (v+1) -> first; e++) {
            if (e -> resCap > 0 and Admissible(v,e)) {
                Push(v,e);
                if (v -> exc == 0){
                    v -> current = v -> first;
                    break;
                }
            }
        }
        if (v -> exc > 0) 
            Relabel(v);
    } 
}

void PushRelabel::Run()
{
    node_iter v,marker = g.nodes.end();
    while (aMax >= 0) {
        v = buckets[aMax];
        if ( v == marker) {
            if(aMax == g.n){
                aMax = nMax;
            }
            else if(aMax < g.n){
                aMax--;
                nMax--;
            }
            else{
                aMax--;
            }
        }
        else {
            Remove(aMax, v);
            Discharge(v);
        }
    }
}

PushRelabel::PushRelabel(resGraph &g_f): g(g_f)
{
    /* using nodes.end() as a marker for the end of the lists. */
    buckets.assign(2*g.n,g.nodes.end());
    
    /* setting initial preflow */
    for (auto e = g.source -> first; e != (g.source + 1) -> first; e++) {
        if (e -> resCap > 0) {
            int gamma = e -> resCap;
            e -> head -> exc += gamma;
            g.source -> exc -= gamma;
            e -> rev -> resCap += gamma;
            e -> resCap -= gamma;
        }
    }
    
    /* setting distance labels */
    aMax = nMax = 0;
    for (auto v = g.nodes.begin(); v != g.nodes.end() - 1; v++) {
        v -> distance = 1;
        if (v == g.source) {
            v -> distance = g.n;
        }
        else if (v == g.sink) {
            v -> distance = 0;
        }
        else if (v -> exc > 0) {
            Add(1, v);
        }
    }
}



