#include <iostream>		
#include "resGraph.h"
#include "pr.h"

int main(int argc, char* argv[])
{
    clock_t begin = std::clock();
    if (argc > 1) {
        resGraph g_f(argv[1]);
        PushRelabel pr(g_f);
        pr.Run();
        g_f.print();
    }
    clock_t end = std::clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << elapsed_secs << std::endl;
}