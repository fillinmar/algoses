#include <iostream>
#include <vector>
#include <climits>
#include <set>
#include <algorithm>

class Graph {
public:
    Graph(size_t n, size_t v): N(n), M(v) {
        data = std::vector < std::vector < std::pair < int, int > >> (N);
    }

    void addEdges(){
        int from, to, l;
        for (size_t i = 0; i < M; ++i) {
            std::cin >> from >> to >> l;
            data[from].push_back(std::make_pair(to, l));
            data[to].push_back(std::make_pair(from, l));
        }
    }

    int MinRoadLength(size_t from, size_t to) {

        std::vector<int> relatives(data.size(), 0), length(data.size(), INT_MAX);

        relatives[from] = -1;
        length[from] = 0;
        std::set<std::pair<int, int>> priorityQueue;

        priorityQueue.insert(std::make_pair(0, from));

        while (!priorityQueue.empty()) {
            auto queueElement =priorityQueue.begin();
            std::pair<int, int> vertex = *queueElement;
            priorityQueue.erase(queueElement);

            for (auto &iterator : data[vertex.second]) {
                if (length[iterator.first] == INT_MAX) {
                    length[iterator.first] = length[vertex.second] + iterator.second;
                    relatives[iterator.first] = vertex.second;

                    priorityQueue.insert(std::make_pair(length[iterator.first], iterator.first));

                } else if (length[iterator.first] > length[vertex.second] + iterator.second) {
                    auto element = priorityQueue.find(std::make_pair(length[iterator.first], iterator.first));
                    priorityQueue.erase(element);

                    length[iterator.first] = length[vertex.second] + iterator.second;
                    relatives[iterator.first] = vertex.second;

                    priorityQueue.insert(std::make_pair(length[iterator.first], iterator.first));

                }
            }
        }
        return length[to];
    }

private:
    size_t N;
    size_t M;
    std::vector<std::vector<std::pair < int, int>>>
            data;
};

int main() {
    size_t elem, n;
    std::cin >> elem >> n;
    Graph graph(elem, n);
    graph.addEdges();

    size_t u, w;
    std::cin >> u >> w;
    std::cout << graph.MinRoadLength(u, w);

}

