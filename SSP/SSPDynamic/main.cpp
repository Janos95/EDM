#include "resGraph.h"
#include "ssp.h"
#include <iostream>

int main()
{
    clock_t begin = std::clock();

    std::ifstream infile;
    std::cout << "enter filename of instance" << std::endl;
    std::string filename;
    std::cin >> filename;
    infile.open(filename);
    resGraph g_f(infile);
    infile.close();
    std::cout << "enter filename of flow" << std::endl;
    filename.clear();
    std::cin >> filename;
    infile.open(filename);
    g_f.readFlow(infile);
    infile.close();
    Ssp ssp(g_f);
    // bool exist = ssp.Run();
    // if(exist)
    ssp.bPrint();
    // else
    //     std::cout << "There is no b-flow for this instance." << std::endl;
    clock_t end = std::clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << elapsed_secs << std::endl;
}
