// Made by Vitalii Fedin, variant 1

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <stdexcept>
#include <stack>

struct Graph {
    std::map<std::string, std::vector<std::string>> edges;
    std::set<std::string> vertices;
};

void read_graph(const std::string& filepath, Graph& graph) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }
    std::string vert1, vert2;
    while (file >> vert1 >> vert2) {
        graph.edges[vert1].push_back(vert2);
        graph.edges[vert2].push_back(vert1);
        graph.vertices.insert(vert1);
        graph.vertices.insert(vert2);
    }
}

void dfs(const std::string& vertex, std::map<std::string, bool>& visited,
         const Graph& graph, std::vector<std::string>& component_vertices) {
    if (visited[vertex]) {
        return;
    }
    std::stack<std::string> stack;
    stack.push(vertex);
    visited[vertex] = true;
    component_vertices.clear();
    while (!stack.empty()) {
        std::string current_vertex = stack.top();
        stack.pop();
        component_vertices.push_back(current_vertex);
        for (const auto& neighbor : graph.edges.at(current_vertex)) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                stack.push(neighbor);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filepath>" << std::endl;
        return 0;
    }


    return 0;

}