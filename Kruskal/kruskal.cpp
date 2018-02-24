#include "graph.h"
#include <numeric>
#include <ctime>


class DisjointSet {
public: 
	DisjointSet(int n) : rank(n,0), parent(n) {
		std::iota(parent.begin(), parent.end(), 0);
	}

	void Union(int x,int y){
		Link(FindSet(x),FindSet(y));
	}
	void Link(int x, int y){
		if(rank[x] > rank[y]){
			parent[y]=x;
		}
		else{
			parent[x]=y;
			if(rank[x] == rank[y]){
				rank[y]++;
			}
		}
	}
	int FindSet(int x){
		if(parent[x] != x){
			parent[x] = FindSet(parent[x]);
		}
		return parent[x];
	}
private:
	std::vector<int> parent;
	std::vector<int> rank;

};

struct Edge{
	Edge(Graph::NodeId start ,Graph::NodeId end, double weight_) : startNode(start), endNode(end), weight(weight_) {}
	Graph::NodeId startNode;
	Graph::NodeId endNode;
	double weight;
};

Graph kruskal(const Graph & g,double &sum,int &num_edges){
	Graph tree(g.num_nodes(), Graph::undirected);
	DisjointSet branching(g.num_nodes());
	
	std::vector<Edge> edges;
	edges.reserve(g.nun_nodes());
	
	sum = 0;
	num_edges = 0;
	
	for(auto i = 0; i<g.num_nodes(); i++){
		for(auto neighbor: g.get_node(i).adjacent_nodes()){
			edges.emplace_back(i,neighbor.id(),neighbor.edge_weight());
		}
	}
	
	std::sort(edges.begin(), edges.end(),[](const Edge& a, const Edge& b){return a.weight < b.weight;});
	
	for(int i=0; i<edges.size();i++){
		int root_start = branching.FindSet(edges[i].startNode);
		int root_end = branching.FindSet(edges[i].endNode);
		if(root_start != root_end ){
			branching.Link(root_start,root_end);
			tree.add_edge1(edges[i].startNode,edges[i].endNode,edges[i].weight);
			sum+=edges[i].weight;
			++num_edges;
		}
	}
	return tree;

}


int main(int argc, char* argv[])
{
    clock_t begin = std::clock();
    if (argc > 1) {
    	Graph g(argv[1], Graph::undirected);
    	double sum;
    	int num_edges;
    	Graph mst = kruskal(g,sum,num_edges);
    	if(num_edges < g.num_nodes() -1){
    		std::cout << "The graph is unconnected." << std::endl;
    	}
    	else{
    		mst.print();	
    	}

    }
    clock_t end = std::clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << elapsed_secs << std::endl;


}
