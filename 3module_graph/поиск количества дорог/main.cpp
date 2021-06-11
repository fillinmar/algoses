#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

class Graph {
public:
    Graph(size_t _v, size_t _n): v(_v), n(_n){
        data = std::vector < std::vector < int >> (v);
    }
    void addEdge(){
        int from, to;
        for (size_t i = 0; i < n; ++i) {
            std::cin >> from >> to;
            data[from].push_back(to);
            data[to].push_back(from);
        }
    }
    size_t bfs(size_t u, size_t w){
        std::vector<bool> visited;
        std::queue<int> queue;
        std::vector<int> distance(data.size(), INT_MAX);
        std::vector<int> routeNumber(data.size(), 0);

        for (size_t i = 0; i < data.size(); ++i) {
            visited.push_back(false);
        }
        for (size_t i = 0; i < data[u].size(); ++i) {
            routeNumber[data[u][i]] = 1;
        }
        routeNumber[u] = 1;
        queue.push(u);
        distance[u] = 0;

        while (!queue.empty()) {
            int elem = queue.front();
            queue.pop();
            visited[elem] = true;
            for (size_t i = 0; i < data[elem].size(); ++i) {
                if ((distance[elem] + 1) == distance[data[elem][i]]) {
                    routeNumber[data[elem][i]] += routeNumber[elem];
                } else if (distance[elem] + 1 < distance[data[elem][i]]) {
                    distance[data[elem][i]] = distance[elem] + 1;
                    routeNumber[data[elem][i]] = routeNumber[elem];
                }
                if (!visited[data[elem][i]]) {
                    queue.push(data[elem][i]);
                    visited[data[elem][i]] = true;
                }
            }
        }
        return routeNumber[w];
    }

private:
    size_t v;
    size_t n;
    std::vector<std::vector<int>> data;
};

int main() {
    size_t elem, n;
    std::cin >> elem >> n;
    Graph graph(elem, n);
    graph.addEdge();

    size_t u, w;
    std::cin >> u >> w;
    std::cout << graph.bfs(u, w) << std::endl;
}

