/*
ID: 206769986
E-Mail: avihyb@gmail.com
*/
#include "Graph.hpp"
#include "Algorithms.hpp"
#include <unordered_set> 
#include <vector>
#include <queue>
#include <climits>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <stack>



/*
Code Explainations:

    (I)  visited.find(x) searches for x element, returns a pointer to that element if found.
         If not, returns an iterator pointing to the end of the set (aka visited.end()).
         Thus, "visited.find(x) == visited.end()" is equalivant of checking if the element isn't in the set.

*/
namespace ariel
{

 const int INF = std::numeric_limits<int>::max();

void Algorithms::BFS(Graph& g, int v, std::vector<bool>& visited) {
    std::queue<int> q;
    q.push(v);
    visited[static_cast<size_t>(v)] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (size_t i = 0; i < g.adjMat[static_cast<size_t>(current)].size(); ++i) {
            if (g.adjMat[static_cast<size_t>(current)][i] != 0 && !visited[i]) {
                q.push(i);
                visited[i] = true;
            }
        }
    }
}

int Algorithms::isConnected(Graph& g) {
    if (g.isDirected) {
        std::vector<bool> visited(g.adjMat.size(), false);

        // Perform BFS starting from each node
        for (int i = 0; i < g.adjMat.size(); ++i) {
            std::vector<bool> tempVisited(g.adjMat.size(), false);
            BFS(g, i, tempVisited);
            // Merge tempVisited into visited
            for (int j = 0; j < visited.size(); ++j) {
                visited[static_cast<size_t>(j)] = visited[static_cast<size_t>(j)] && tempVisited[static_cast<size_t>(j)];
            }
        }

        // Check if all nodes are visited
        for (bool v : visited) {
            if (!v) return 0; // Not connected
        }
        return 1; // Connected
    } else {
        // Implement logic to check if an undirected graph is connected using BFS
        std::vector<bool> visited(g.adjMat.size(), false);

        // Perform BFS starting from node 0
        BFS(g, 0, visited);

        // Check if all nodes are visited
        for (bool v : visited) {
            if (!v) return 0; // Not connected
        }
        return 1; // Connected
    }
}


std::string Algorithms::shortestPath(Graph& g, size_t start, size_t end) {
    size_t n = g.getNumVertices();
    std::vector<int> prev(n, -1);
    std::vector<int> dist(n, INF);
    BellmanFord(g, start, prev, dist);
    if (dist[end] != INF) {
        return printPath(prev, dist, start, end);
        
    } else {
        return "-1"; // No shortestPath
    }
}

void Algorithms::BellmanFord(Graph& g, size_t start, std::vector<int>& prev, std::vector<int>& dist) {
    size_t V = g.getNumVertices();
    dist[start] = 0;
    // Relax edges repeatedly
    for (size_t i = 0; i < V - 1; ++i) {
        for (size_t u = 0; u < V; ++u) {
            for (size_t v = 0; v < V; ++v) {
                if (g.adjMat[u][v] != 0) {
                    Relax(u, v, g.adjMat[u][v], prev, dist);
                }
            }
        }
    }

}

void Algorithms::Relax(size_t u, size_t v, int w, std::vector<int>& prev, std::vector<int>& dist) {
    if (dist[u] != INF && (dist[v] > dist[u] + w)) {
        dist[v] = dist[u] + w;
        prev[v] = u;
    }
}

std::string Algorithms::printPath(std::vector<int>& prev, std::vector<int>& dist, size_t start, size_t end) {
    std::string path;
    if (prev[end] == -1) {
        return "-1"; // No path found
    }
    // for(size_t i = 0; i < prev.size(); ++i){
    //     std::cout << prev[i] << " ";
    // }
    std::vector<int> vec;
    size_t i = end;
    while(i != start){
        vec.push_back(i);
        i = static_cast<size_t>(prev[i]);
    }
    vec.push_back(i);

    
    for(size_t j = vec.size() - 1; j > 0; j--){
        path += std::to_string(vec[j]) + "->";
    }
    path += std::to_string(vec[0]); // Add the start vertex at the end

    return path;
}



 



std::string Algorithms::isContainsCycle(Graph& g) {
        size_t numVertices = g.getNumVertices();
        std::vector<bool> visited(numVertices, false);
        std::vector<bool> stack(numVertices, false);
        std::string cycle;

        for (size_t i = 0; i < numVertices; ++i) {
            if (!visited[i] && detectCycleDFS(g, i, visited, stack, cycle)) {
                return cycle;
            }
        }

        return "0";
    }


   bool Algorithms::detectCycleDFS(const Graph& graph, size_t v, std::vector<bool>& visited, std::vector<bool>& stack, std::string& cycle) {
        visited[v] = true;
        stack[v] = true;

        for (size_t i = 0; i < graph.getNumVertices(); ++i) {
            if (graph.adjMat[v][i] != 0) {
                if (!visited[i]) {
                    if (detectCycleDFS(graph, i, visited, stack, cycle)) {
                        cycle = std::to_string(v) + " -> " + cycle;
                        return true;
                    }
                } else if (stack[i]) {
                    cycle = std::to_string(i) + " -> " + cycle;
                    cycle = std::to_string(v) + " -> " + cycle;
                    return true;
                }
            }
        }
        stack[v] = false;
        return false;
    }


bool Algorithms::isBipartite(Graph& g) {
    std::vector<std::vector<int>> edges(g.getNumVertices());
    for (size_t i = 0; i < g.adjMat.size(); ++i) {
        edges[(size_t)g.adjMat[i][0]].push_back((size_t)g.adjMat[i][1]);
        edges[(size_t)g.adjMat[i][1]].push_back((size_t)g.adjMat[i][0]);
    }

    std::vector<bool> visited(g.getNumVertices(), false);
    bool res = true;
    for (size_t i = 0; i < g.getNumVertices(); ++i) {
        if (!visited[i]) {
            if (!bipartite(g, edges, i, visited)) {
                res = false;
                break;
            }
        }
    }

    if (res) {
        std::cout << "Set A ={";
        for (auto elem : g.sets[0]) {
            std::cout << elem << " ";
        }
        std::cout << "} Set B ={";
        for (auto elem : g.sets[1]) {
            std::cout << elem << " ";
        }
        std::cout << "}";
    } else {
        std::cout << "Not bipartite";
    }
    return res;
}

bool Algorithms::bipartite(Graph& g, std::vector<std::vector<int>>& edges, int start, std::vector<bool>& visited) {
    std::vector<int> pending;
    g.sets[0].clear();
    g.sets[1].clear();

    g.sets[0].insert(start);
    pending.push_back(start);
    
    while (!pending.empty()) {
        size_t current = (size_t)pending.back();
        pending.pop_back();
        visited[current] = true;
        int currentSet = g.sets[0].count(current) > 0 ? 0 : 1;
        
        for (int neighbor : edges[current]) {
            if (g.sets[0].count(neighbor) == 0 && g.sets[1].count(neighbor) == 0) {
                g.sets[1 - currentSet].insert(neighbor);
                pending.push_back(neighbor);
            } else if (g.sets[currentSet].count(neighbor) > 0) {
                return false;
            }
        }
    }
    return true;
}









    int Algorithms::negativeCycle(Graph& g) {
        size_t n = g.adjMat.size();
        std::vector<int> dist(n, INT_MAX); // Initialize distances with infinity

        dist[0] = 0;

        // Relax edges repeatedly
        for (size_t i = 0; i < n - 1; ++i) {
            for (size_t u = 0; u < n; ++u) {
                for (size_t v = 0; v < n; ++v) {
                    if (g.adjMat[u][v] != 0 && dist[u] != INT_MAX && dist[u] + g.adjMat[u][v] < dist[v]) {
                        dist[v] = dist[u] + g.adjMat[u][v];
                    }
                }
            }
        }

        // Check for negative cycles
        for (size_t u = 0; u < n; ++u) {
            for (size_t v = 0; v < n; ++v) {
                if (g.adjMat[u][v] != 0 && dist[u] != INT_MAX && dist[u] + g.adjMat[u][v] < dist[v]) {
                    std::cout << "Negative cycle detected\n";
                    return 1; // Negative cycle found
                }
            }
        }

        std::cout << "No negative cycle in this graph\n";
        return 0; // No negative cycle
    }

} // namespace ariel
