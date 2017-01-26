#include "resGraph.h"
#include "ssp.h"
#include <iostream>

int main()
{
    clock_t begin = std::clock();

    std::ifstream infile;
    std::cout << "enter filename" << std::endl;
    std::string filename;
    std::cin >> filename;
    infile.open(filename);
    Ssp ssp(infile);
    infile.close();
    bool exist = ssp.Run();
    if(exist)
        ssp.bPrint();
    else
        std::cout << "There is no b-flow for this instance." << std::endl;
    
    clock_t end = std::clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << elapsed_secs << std::endl;
}
