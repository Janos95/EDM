#include <stdio.h>
#include <algorithm>
#include <limits>
#include <assert.h>
#include "heap.h"

#define INFTY std::numeric_limits<long>::max() / 2

long inline Parent(long i) { return i >> 2;}
long inline First_Child(long i) { return (i << 2) + 1;}

Heap::Heap(resGraph& g_f)
    : g(g_f)
    , heap(g.n)
    , size(0)
{
    perm.reserve(g.n);
}

void Heap::MoveUp(node_iter node)
{
    node_iter nodeParent;
    long iCurrent = node->heapPos;
    for (long iParent = Parent(node->heapPos);
         iCurrent > 0;
         iCurrent = iParent, iParent = Parent(iParent)) {
        nodeParent = heap[iParent];
        if (node->dist >= nodeParent->dist) 
            break;
        heap[iCurrent] = nodeParent;
        heap[iCurrent]->heapPos = iCurrent;
    }
    heap[iCurrent] = node; /* put the node in the hole */
    heap[iCurrent]->heapPos = iCurrent;
}

void Heap::MoveDown(node_iter pNode)
{
    long iCurrent, iChild, iGoodChild, iFirstChild, iLastChild;
    long minValue;

    for (iCurrent = pNode->heapPos;
         /* break when value <= min */;
         iCurrent = iGoodChild) {
        iFirstChild = First_Child(iCurrent);
        iLastChild = std::min(iFirstChild + 4, size - 1);
        if (iFirstChild > size) 
            break;
        minValue = heap[iFirstChild]->dist;
        iGoodChild = iFirstChild; 
        for (iChild = iFirstChild + 1; iChild <= iLastChild; iChild++)
            if (heap[iChild]->dist < minValue) 
            {
                minValue = heap[iChild]->dist;
                iGoodChild = iChild;
            }
        if (pNode->dist <= minValue) 
            break;
        heap[iCurrent] = heap[iGoodChild];
        heap[iCurrent]->heapPos = iCurrent;
    }
    heap[iCurrent] = pNode; /* put node into hole */
    heap[iCurrent]->heapPos = iCurrent;
}

/*does not preserve heap order */
void Heap::Insert(node_iter v)
{
    heap[size] = v;
    v->heapPos = size;
    v->inHeap = true;
    size++;
}

node_iter Heap::RemoveMin()
{
    node_iter retval;

    retval = heap[0]; 
    retval->inHeap = false; 
    size--;

    if (size > 0) {
        heap[0] = heap[size];
        heap[0]->heapPos = 0;
        MoveDown(heap[0]); 
    }
    return retval;
}

node_iter Heap::Dijkstra(node_iter v)
{
    node_iter curNode, newNode;
    edge_iter last; 

    /* preparing heap */
    for (auto w = g.nodes.begin(); w != g.nodes.end(); w++)
        w->dist = INFTY;
    v->dist = 0;

    Empty();
    Insert(v);

    while (not IsEmpty()) {
        curNode = RemoveMin();
        perm.push_back(curNode);
        if (curNode->b < 0) {
            long distB = curNode -> dist;
            for(int i = 0; i < size; i++)
                heap[i] -> inHeap = false;
            for(auto &w : perm)
                w -> pot += (distB - w -> dist);
            return curNode;
        }

        last = (curNode + 1)->first;
        for (auto e = curNode->first; e != last; e++) {
            newNode = e->head;
            if (e->resCap > 0 and curNode->dist + (e->c + e -> head -> pot - curNode -> pot) < newNode->dist) {
                /* this way is shorter. Hence we update the sp tree */
                assert(e->c + e -> head -> pot - curNode -> pot >= 0);
                newNode->dist = curNode->dist + e->c + e -> head -> pot - curNode -> pot;
                newNode->parent = curNode;
                newNode->current = e;
                if (not InHeap(newNode))
                    Insert(newNode);
                MoveUp(newNode); /* update anyways */
            }
        }
    }
    return g.nodes.end();
}
