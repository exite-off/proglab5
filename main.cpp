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

int count_edges_in_component(const std::vector<std::string>& component, const Graph& graph) {
    int edge_count = 0;
    for (const auto& vertex : component) {
        edge_count += graph.edges.at(vertex).size();
    }
    return edge_count / 2;
}

int calculate_result(Graph& graph) {
    std::map<std::string, bool> visited;
    int max_component = 0;
    int max_edges = 0;
    for (const auto& vertex : graph.vertices) {
        if (!visited[vertex]) {
            std::vector<std::string> component;
            dfs(vertex, visited, graph, component);
            int component_size = component.size();
            int edge_count = count_edges_in_component(component, graph);
            if (component_size > max_component || (component_size == max_component && edge_count > max_edges)) {
                max_component = component_size;
                max_edges = edge_count;
            }
        }
    }
    return max_edges;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "\nUsage: " << argv[0] << " <filepath>" << std::endl;
        return 0;
    }
    Graph graph;
    try {
        read_graph(argv[1], graph);
    } catch (std::runtime_error& e) {
        std::cerr << "\nError: " << e.what() << std::endl;
        return 0;
    }
    std::cout << '\n' << calculate_result(graph);

    return 0;

}