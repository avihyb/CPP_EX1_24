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

/*
Code Explainations:

    (I)  visited.find(x) searches for x element, returns a pointer to that element if found.
         If not, returns an iterator pointing to the end of the set (aka visited.end()).
         Thus, "visited.find(x) == visited.end()" is equalivant of checking if the element isn't in the set.

*/
namespace ariel
{

    /*
        FloydWarshall: All-Pairs Shortest Paths algorithm.
    */
void Algorithms::FloydWarshall(Graph& g){
    
    int numVertices = static_cast<int>(g.adjMat.size());
            g.shortestPaths = g.adjMat; 

            for (size_t k = 0; k < numVertices; ++k) {
                for (size_t i = 0; i < numVertices; ++i) {
                    for (size_t j = 0; j < numVertices; ++j) {
                        if (g.shortestPaths[i][k] != std::numeric_limits<int>::max() &&
                            g.shortestPaths[k][j] != std::numeric_limits<int>::max() &&
                            g.shortestPaths[i][k] + g.shortestPaths[k][j] < g.shortestPaths[i][j]) {
                            g.shortestPaths[i][j] = g.shortestPaths[i][k] + g.shortestPaths[k][j];
                        }
                    }
                }
            }

             for (size_t i = 0; i < g.shortestPaths.size(); ++i) {
                if (g.shortestPaths[i][i] < 0) {
                g.hasCycle = true;// Detected a negative cycle
        }
    }
    
}

    /*
        DFS: depth-first search, starting from a given vertex in the graph.
        Visits all reachable vertices recursively, marking each visited vertex in the visited set.
        @return void
    */
void Algorithms::DFS(Graph& g, int v, std::vector<bool>& visited) {
    visited[static_cast<size_t>(v)] = true;
    for (int i = 0; i < g.adjMat.size(); ++i) {
        if (g.adjMat[static_cast<size_t>(v)][static_cast<size_t>(i)] != 0 && !visited[static_cast<size_t>(i)]) {
            DFS(g, i, visited);
        }
    }
}

int Algorithms::isConnected(Graph& g) {
    if (g.isDirected) {
        // Implement logic to check if a directed graph is connected
        std::vector<bool> visited(g.adjMat.size(), false);

        // Perform DFS starting from each node
        for (int i = 0; i < g.adjMat.size(); ++i) {
            std::vector<bool> tempVisited(g.adjMat.size(), false);
            DFS(g, i, tempVisited);
            // Merge tempVisited into visited
            for (int j = 0; j < visited.size(); ++j) {
                visited[static_cast<size_t>(j)] = visited[static_cast<size_t>(j)] || tempVisited[static_cast<size_t>(j)];
            }
        }

        // Check if all nodes are visited
        for (bool v : visited) {
            if (!v) return 0; // Not connected
        }
        return 1; // Connected
    } else {
        // Implement logic to check if an undirected graph is connected
        std::vector<bool> visited(g.adjMat.size(), false);

        // Perform DFS starting from node 0
        DFS(g, 0, visited);

        // Check if all nodes are visited
        for (bool v : visited) {
            if (!v) return 0; // Not connected
        }
        return 1; // Connected
    }
}



    /*
        shortestPath: Using the Dijkstra's Alogrithm to compute the shortest path from start to end.
        @return string representing the Shortest Path, or -1 in case there's no path.
    */
std::string Algorithms::shortestPath(Graph& g, int start, int end) {
    if (start < 0 || start >= g.adjMat.size() || end >= g.adjMat.size() || end < 0) {
        std::cerr << "Error: START/END point out of bounds." << std::endl;
        return "-1";
    }

    if (start == end) {
        return std::to_string(start);
    }

    if (!g.hasNegativeEdges && !g.isDirected) {
        size_t n = g.adjMat.size();
        std::vector<int> dist(n, INT_MAX); // Initialize distances with infinity
        std::vector<int> prev(n, -1); // Previous node in the shortest path
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq; // Min-heap

        dist[static_cast<size_t>(start)] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (int v = 0; v < n; ++v) {
                if (g.adjMat[static_cast<size_t>(u)][static_cast<size_t>(v)] != 0 && dist[static_cast<size_t>(u)] + g.adjMat[static_cast<size_t>(u)][static_cast<size_t>(v)] < dist[static_cast<size_t>(v)]) {
                    dist[static_cast<size_t>(v)] = dist[static_cast<size_t>(u)] + g.adjMat[static_cast<size_t>(u)][static_cast<size_t>(v)];
                    prev[static_cast<size_t>(v)] = u;
                    pq.push({dist[static_cast<size_t>(v)], v});
                }
            }
        }

        // Reconstruct the shortest path
        if (dist[static_cast<size_t>(end)] == INT_MAX)
            return "-1"; // No path exists

        std::string path = std::to_string(end);
        while (prev[static_cast<size_t>(end)] != -1) {
            path = std::to_string(prev[static_cast<size_t>(end)]) + "->" + path;
            end = prev[static_cast<size_t>(end)];
        }
        return path;
    } else if (g.isDirected) {
        // Bellman-Ford algorithm for directed graphs
        size_t n = g.adjMat.size();
        std::vector<int> dist(n, INT_MAX); // Initialize distances with infinity
        std::vector<int> prev(n, -1); // Previous node in the shortest path

        dist[static_cast<size_t>(start)] = 0;

        // Relax edges repeatedly
        for (size_t i = 0; i < n - 1; ++i) {
            for (size_t u = 0; u < n; ++u) {
                for (size_t v = 0; v < n; ++v) {
                    if (g.adjMat[u][v] != 0 && dist[u] != INT_MAX && dist[u] + g.adjMat[u][v] < dist[v]) {
                        dist[v] = dist[u] + g.adjMat[u][v];
                        prev[v] = u;
                    }
                }
            }
        }

        // Check for negative cycles
        for (size_t u = 0; u < n; ++u) {
            for (size_t v = 0; v < n; ++v) {
                if (g.adjMat[u][v] != 0 && dist[u] != INT_MAX && dist[u] + g.adjMat[u][v] < dist[v]) {
                    return "Negative cycle detected"; // Negative cycle found
                }
            }
        }

        // Reconstruct the shortest path
        if (dist[static_cast<size_t>(end)] == INT_MAX)
            return "-1"; // No path exists

        std::string path = std::to_string(end);
        while (prev[static_cast<size_t>(end)] != -1) {
            path = std::to_string(prev[static_cast<size_t>(end)]) + "->" + path;
            end = prev[static_cast<size_t>(end)];
        }
        return path;
    } else {
        return "Not implemented for undirected graphs";
    }
}


    /*
        isContainsCycle: Using the ShortestPaths of a graph, this function scans for a 
        cycle. If a cycle is found it returns a string representing the cycle. If none found it returns "0";
        @return any cycle from the graph, -1 if there's none.
    */
bool Algorithms::isContainsCycle(Graph& g) {
    
    negativeCycle(g);
    if(g.hasCycle){
        return true; }

        return false;
        
}

std::string Algorithms::printCycle(Graph& g){
        std::string cycle;
    // Backtrack the cycle and construct the string representation
        cycle = "Cycle found: ";
        int cycleStartVertex;
        for (size_t i = 0; i < g.shortestPaths.size(); ++i) {
            if (g.shortestPaths[i][i] < 0) {
                cycleStartVertex = static_cast<int>(i);
                break;
            }
        }
        int currentVertex = cycleStartVertex;
        std::unordered_set<int> visited;
        while (visited.find(currentVertex) == visited.end()) {
            visited.insert(currentVertex);
            cycle += std::to_string(currentVertex) + " -> ";
            // Move to the next vertex in the cycle
            for (size_t vertex = 0; vertex < g.adjMat.size(); ++vertex) {
                if (g.shortestPaths[static_cast<size_t>(currentVertex)][vertex] != std::numeric_limits<int>::max() &&
                    g.shortestPaths[vertex][static_cast<size_t>(cycleStartVertex)] != std::numeric_limits<int>::max() &&
                    g.shortestPaths[static_cast<size_t>(currentVertex)][vertex] + g.shortestPaths[vertex][static_cast<size_t>(cycleStartVertex)] == g.shortestPaths[static_cast<size_t>(currentVertex)][static_cast<size_t>(cycleStartVertex)]) {
                    currentVertex = static_cast<int>(vertex);
                    break;
                }
            }
        }
        // Remove the last "->" from the cycle string
        cycle.pop_back();
        cycle.pop_back();

        return cycle;
    }

    


    /*
        isBipartite: 
        @return string representing the 2 disticnt vertices sets. 0 if not bipartite. 
    */
    std::string Algorithms::isBipartite(Graph& g) {
        std::vector<int> colors(g.adjMat.size(), -1); // Initialize colors for each vertex (-1 represents uncolored)
        std::queue<size_t> q;

        // Start BFS traversal from every uncolored vertex
        for (size_t i = 0; i < g.adjMat.size(); ++i) {
            if (colors[i] == -1) {
                q.push(i);
                colors[i] = 0; // Color the vertex with 0
            }

            while (!q.empty()) {
                size_t v = q.front();
                q.pop();

                for (int neighbor : g.adjMat[v]) {
                    if (colors[static_cast<size_t>(neighbor)] == -1) {
                        colors[static_cast<size_t>(neighbor)] = 1 - colors[v]; // Assign opposite color to the neighbor
                        q.push(static_cast<size_t>(neighbor));
                    } else if (colors[static_cast<size_t>(neighbor)] == colors[v]) {
                        return "0";
                    }
                }
            }
        }

        // Construct sets of vertices based on colors
        std::vector<int> setA, setB;
        for (size_t i = 0; i < g.adjMat.size(); ++i) {
            if (colors[i] == 0) {
                setA.push_back(i);
            } else {
                setB.push_back(i);
            }
        }

        // Construct the string representation of bipartite sets
        std::string bipartiteSets = "The graph is bipartite: ";
        bipartiteSets += "A={";
        for (size_t i = 0; i < setA.size(); ++i) {
            bipartiteSets += std::to_string(setA[i]);
            if (i < setA.size() - 1) {
                bipartiteSets += ", ";
            }
        }
        bipartiteSets += "}, B={";
        for (size_t i = 0; i < setB.size(); ++i) {
            bipartiteSets += std::to_string(setB[i]);
            if (i < setB.size() - 1) {
                bipartiteSets += ", ";
            }
        }
        bipartiteSets += "}.";

        return bipartiteSets;
    }


    /*
        negativeCycle:
        @return 1 if there's a negative cycle, 0 if there isn't. (Will also print "No negative cycle in this graph").
    */
    int Algorithms::negativeCycle(Graph& g) {
        size_t vertices = g.shortestPaths.size();
        for(size_t i = 0; i < vertices; ++i){
            if(g.shortestPaths[i][i] < 0){
                return 1;
                g.hasCycle = true;
            }
        }
        //std::cout << "No negative cycle in this graph";
        return 0;
    }
    

} // namespace ariel
