#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <limits>

#define INFTY std::numeric_limits<int>::max()/2

struct Edge{
    int index;
    int tail;
    int head;
    int cost;
    Edge(int a, int b, int c, int i): tail(a), head(b), cost(c), index(i){}
};

bool compareEdge(const Edge e1, const Edge e2)
{
    return e1.index < e2.index;
}

int main(int argc, char* argv[])
{
    if (argc > 1) {
        std::ifstream file(argv[1]);
        if (not file) {
            throw std::runtime_error("Cannot open file.");
        }
        
        //allocating memory.
        std::vector<std::vector<int> > edges(10,std::vector<int> (10,INFTY));
        std::vector<Edge> pisten;
        std::vector<std::vector<Edge> > optimal;
        
        int count = 0;
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            int head, tail;
            ss >> tail >> head;
            bool isPiste;
            ss >> isPiste;
            int c;
            ss >> c;
            edges[tail][head] = c;
            if(isPiste){
                pisten.push_back(Edge(tail,head,c,count));
                count++;
            }
        }
        int min = INFTY;
        int n = edges.size();

        std::vector<std::vector<int> > dist = edges;
        for(int i = 0; i < n; i++)
            dist[i][i] = 0;
        for(int k = 0; k < n; k++){
            for(int j = 0; j < n; j++){
                for(int i = 0; i < n; i++){
                    dist[i][j] = std::min(dist[i][j],dist[i][k]+dist[k][j]);
                }
            }
        }
        do{
            int tmp = dist[0][pisten.begin() -> tail];
            for(auto e = pisten.begin(); e != pisten.end(); e++){
                tmp += e -> cost + dist[e -> head][(e+1) -> tail];
                if(tmp >= min)
                    break;
            }
            tmp += pisten.back().cost + dist[pisten.back().tail][0];
            if(tmp <= min ){
                if(tmp < min)
                    optimal.clear();
                min = tmp;
                optimal.push_back(pisten);
            }
            /* here is still a lot of room for improving performance by pruning */
        }while(std::next_permutation(pisten.begin(),pisten.end(),compareEdge));

        std::ofstream myfile;
        myfile.open ("output.txt");
        myfile << "cost of cheapest tour: " << min << std::endl;
        myfile << "the number of optimal tours is: " << optimal.size() << std::endl;
        for(auto sol : optimal){
            myfile << "0 -> sp: " << dist[0][sol[0].tail] << " -> ";
            for(auto e = sol.begin(); e != sol.end() - 1; e++)
                myfile << "(" << e -> tail << "," << e -> head << ")" << " -> sp: " << dist[e -> head][(e+1) -> tail] << " -> ";
            myfile << "(" << sol.back().tail << "," << sol.back().head << ")" << "\\" << "\\" << std::endl << std::endl;
        } 
        myfile.close();     
    }
}

