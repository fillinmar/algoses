#include <iostream>
#include <sstream>
#include "list_graph.hpp"
#include "matrix_graph.hpp"
#include "arc_graph.hpp"
#include "set_graph.hpp"
#include <cassert>

bool testListGraph();
bool testMatrixGraph();
bool testArcGraph();
bool testSetGraph();

int main() {
    if (testListGraph()) {
        std::cout << std::endl << "ListGraph works correct" << std::endl;
    }

    if (testMatrixGraph()) {
        std::cout << std::endl << "MatrixGraph works correct" << std::endl;
    }

    if (testArcGraph()) {
        std::cout << std::endl << "ArcGraph works correct" << std::endl;
    }

    if (testSetGraph()) {
        std::cout << std::endl << "SetGraph works correct" << std::endl;
    }
    return 0;
}

bool testSetGraph() {
    std::stringstream outputNext;
    std::stringstream outputPrev;
    SetGraph graph(7);
    graph.AddEdge(0, 1);
    graph.AddEdge(0, 5);
    graph.AddEdge(1, 2);
    graph.AddEdge(1, 3);
    graph.AddEdge(1, 5);
    graph.AddEdge(1, 6);
    graph.AddEdge(3, 2);
    graph.AddEdge(3, 4);
    graph.AddEdge(3, 6);
    graph.AddEdge(5, 4);
    graph.AddEdge(5, 6);
    graph.AddEdge(6, 4);

    for (int i : graph.GetNextVertices(0)) {
        outputNext << i <<" ";
    }
    assert(outputNext.str() == "5 1 ");

    for (int i : graph.GetPrevVertices(4)) {
        outputPrev << i <<" ";
    }
    assert(outputPrev.str() == "6 5 3 ");
    return true;
}

bool testArcGraph() {
    std::stringstream outputNext;
    std::stringstream outputPrev;
    ArcGraph graph(7);
    graph.AddEdge(0, 1);
    graph.AddEdge(0, 5);
    graph.AddEdge(1, 2);
    graph.AddEdge(1, 3);
    graph.AddEdge(1, 5);
    graph.AddEdge(1, 6);
    graph.AddEdge(3, 2);
    graph.AddEdge(3, 4);
    graph.AddEdge(3, 6);
    graph.AddEdge(5, 4);
    graph.AddEdge(5, 6);
    graph.AddEdge(6, 4);

    for (int i : graph.GetNextVertices(0)) {
        outputNext << i <<" ";
    }
    assert(outputNext.str() == "1 5 ");

    for (int i : graph.GetPrevVertices(4)) {
        outputPrev << i <<" ";
    }
    assert(outputPrev.str() == "3 5 6 ");
    return true;
}

bool testMatrixGraph() {
    std::stringstream outputNext;
    std::stringstream outputPrev;
    MatrixGraph graph(7);
    graph.AddEdge(0, 1);
    graph.AddEdge(0, 5);
    graph.AddEdge(1, 2);
    graph.AddEdge(1, 3);
    graph.AddEdge(1, 5);
    graph.AddEdge(1, 6);
    graph.AddEdge(3, 2);
    graph.AddEdge(3, 4);
    graph.AddEdge(3, 6);
    graph.AddEdge(5, 4);
    graph.AddEdge(5, 6);
    graph.AddEdge(6, 4);

    for (int i : graph.GetNextVertices(0)) {
        outputNext << i <<" ";
    }
    assert(outputNext.str() == "1 5 ");

    for (int i : graph.GetPrevVertices(4)) {
        outputPrev << i <<" ";
    }
    assert(outputPrev.str() == "3 5 6 ");
    return true;
}

bool testListGraph() {
    std::stringstream outputNext;
    std::stringstream outputPrev;
    ListGraph graph(7);
    graph.AddEdge(0, 1);
    graph.AddEdge(0, 5);
    graph.AddEdge(1, 2);
    graph.AddEdge(1, 3);
    graph.AddEdge(1, 5);
    graph.AddEdge(1, 6);
    graph.AddEdge(3, 2);
    graph.AddEdge(3, 4);
    graph.AddEdge(3, 6);
    graph.AddEdge(5, 4);
    graph.AddEdge(5, 6);
    graph.AddEdge(6, 4);

    for (int i : graph.GetNextVertices(0)) {
        outputNext << i <<" ";
    }
    assert(outputNext.str() == "5 1 ");

    for (int i : graph.GetPrevVertices(4)) {
        outputPrev << i <<" ";
    }
    std::string str = outputPrev.str();
    assert(outputPrev.str() == "3 5 6 ");
    return true;
}