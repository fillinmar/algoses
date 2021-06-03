#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <set>
#include <algorithm>

class PriorityQueueWithErase : public std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
        std::greater<std::pair<int, int>>> {
public:
    void erase(const std::pair<int, int> &value) {
        auto it = std::find(this->c.begin(), this->c.end(), value);
        if (it != this->c.end()) {
            this->c.erase(it);
            std::make_heap(this->c.begin(), this->c.end(), this->comp);
        }
    }
    bool find(const std::pair<int, int> &value) {
        if (std::find(this->c.begin(), this->c.end(), value) != this->c.end()) {
            return true;
        }
        return false;
    }
};

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

    std::vector<int> dijkstraPriorityQueue(size_t u){
        std::vector<int> distance(N, INT_MAX);
        PriorityQueueWithErase queue;
        distance[u] = 0;
        queue.emplace(std::make_pair(distance[u], u));//add elem at the end
        while (!queue.empty()) {
            auto minDistance = queue.top();
            queue.pop();
            for (size_t i = 0; i < data[minDistance.second].size(); ++i) {
                if (distance[minDistance.second] + data[minDistance.second][i].second
                    < distance[data[minDistance.second][i].first]) {
                    if (queue.find(std::make_pair(distance[data[minDistance.second][i].first], data[minDistance.second][i].first))) {
                        queue.erase(std::make_pair(distance[data[minDistance.second][i].first], data[minDistance.second][i].first));
                    }
                    queue.erase(std::make_pair(distance[data[minDistance.second][i].first], data[minDistance.second][i].first));
                    distance[data[minDistance.second][i].first] = distance[minDistance.second] + data[minDistance.second][i].second;
                    queue.emplace(std::make_pair(distance[data[minDistance.second][i].first], data[minDistance.second][i].first));

                }
            }
        }
        return distance;
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
    std::cout << graph.dijkstraPriorityQueue(u)[w] << std::endl;

}



