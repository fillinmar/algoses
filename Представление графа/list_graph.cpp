#include "list_graph.hpp"

void ListGraph::AddEdge(int from, int to) {
    adjacencyLists[from].push_front(to);
}

int ListGraph::VerticesCount() const {
    return (int)adjacencyLists.size();
}

ListGraph::ListGraph(const IGraph &copy) {
    size_t c_size = copy.VerticesCount();
    adjacencyLists = std::vector<std::list<int>>(c_size);
    for (size_t i = 0; i < c_size; ++i) {
        std::vector<int> vertices = GetNextVertices(i);
        for (size_t j = 0; j < vertices.size(); ++j) {
            AddEdge(i, vertices[j]);
        }
    }
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    std::vector<int> vertices;
    for (auto i : adjacencyLists[vertex]) {
        vertices.push_back(i);
    }
    return vertices;
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    std::vector<int> vertices;
    for (size_t i = 0; i < adjacencyLists.size(); ++i) {
        for (auto j : adjacencyLists[i]) {
            if (j == vertex) {
                vertices.push_back(i);
            }
        }
    }
    return vertices;
}