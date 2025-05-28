#include <iostream>
#include <string>
#include "graph.h"

int main(const int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "\nUsage: " << argv[0] << " <input_file>" << std::endl;
        return 0;
    }

    Graph graph(argv[1]);


    return 0;
}