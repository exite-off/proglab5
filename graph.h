#pragma once

#include <string>
#include <vector> // TODO: change for more suitable container

class Graph {
private:
    std::vector<std::pair<std::string, std::string>> adjList;

public:
    Graph(std::string filepath);
    std::vector<std::string> getComponent(std::string vertex);
    int findMaxComponent(const std::vector<std::vector<std::string>>& components);
};