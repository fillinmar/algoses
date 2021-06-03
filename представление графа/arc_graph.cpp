#include "arc_graph.hpp"

ArcGraph::ArcGraph(size_t vertices_count)
    : verticesCount(vertices_count) {}

ArcGraph::ArcGraph(IGraph* graph) {
    int vertices_count = graph->VerticesCount();

    verticesCount = vertices_count;

    for (int i = 0; i < vertices_count; i++) {
        std::vector<int> next_vertices = graph->GetNextVertices(i);
        for (int next : next_vertices) {
            AddEdge(i, next);
        }
    }
}

void ArcGraph::AddEdge(int from, int to) {
    array.push_back(std::make_pair(from, to));
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    std::vector<int> next;
    for (auto element : array) {
        if (element.first == vertex) {
            next.push_back(element.second);
        }
    }
    return next;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prev;
    for (auto element : array) {
        if (element.second == vertex) {
            prev.push_back(element.first);
        }
    }
    return prev;
}