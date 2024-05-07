// 
// 

#include "Graph.hpp"
#include "Algorithms.hpp"
using ariel::Algorithms;

#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

int main()
{
    ariel::Graph g;
    cout << "////////// GRAPH #1 //////////" << endl;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph); // Load the graph to the object.
    g.printGraph();                                    // Should print: "Graph with 3 vertices and 2 edges."  
    cout << "*********** Algorithms: **********" << endl;
    cout << Algorithms::isConnected(g) << endl;                         // Should print: "1" (true).
    cout << Algorithms::shortestPath(g, 0, 2) << endl; // Should print: 0->1->2.
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "0" (false).
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "The graph is bipartite: A={1, 3}, B={2}."
    cout << "//////////////////////////////" << endl;

    cout << "////////// GRAPH #2 //////////" << endl;
    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2); // Load the graph to the object.
    g.printGraph();                                    // Should print: "Graph with 5 vertices and 4 edges."
    cout << "Algorithms:*" << endl;
    cout << Algorithms::isConnected(g) << endl;                        // Should print: "0" (false).
    cout << Algorithms::shortestPath(g, 0, 4) << endl; // Should print: "-1" (there is no path between 0 and 4).
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "The cycle is: 0->1->2->0".
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "0" (false).
    cout << "//////////////////////////////" << endl;

    cout << "////////// GRAPH #3 //////////" << endl;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph3);                               // Load the graph to the object.
    g.printGraph();                                    // Should print: "Graph with 5 vertices and 10 edges."
    cout << "Algorithms:*" << endl;
    cout << Algorithms::isConnected(g) << endl;                         // Should print: "1" (true).
    cout << Algorithms::shortestPath(g, 0, 3) << endl; // Should print: 0->2->3.
    cout << Algorithms::shortestPath(g, 2, 0) << endl; // Should print: 2->0 \ 2->1->0
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "1" (true). //no negative
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "The graph isnt bipartite."
    cout << "//////////////////////////////" << endl;

    cout << "////////// GRAPH #4 //////////" << endl;
    vector<vector<int>> graph4 = {
        {0, 0, 0, 0},
        {7, 0, 2, 0},
        {0, 0, 0, 2},
        {1, 0, 0, 0}};
    g.loadGraph(graph4); // Load the graph to the object.
    g.printGraph();                                    // Should print: "Graph with 4 vertices and 4 edges."
    cout << "Algorithms:*" << endl;
    cout << Algorithms::isConnected(g) << endl;                        // Should print: false                      
    cout << Algorithms::shortestPath(g, 3, 1) << endl; // Should print: no path
    cout << Algorithms::shortestPath(g, 1, 0) << endl; // Should print: 1->2->3->0.
    // cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "0" (false).
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "The graph is bipartite: A={2, 4}, B={1, 3}."
    cout << "//////////////////////////////" << endl;

    cout << "////////// GRAPH #5 //////////" << endl;
    vector<vector<int>> graph5 = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    try
    {
        g.loadGraph(graph5); // Load the graph to the object.
    }
    catch (const std::invalid_argument &e)
    {
        cout << e.what() << endl; // Should print: "Invalid graph: The graph is not a square matrix."
    }
    cout << "//////////////////////////////" << endl;

    cout << "////////// GRAPH #6 //////////" << endl;
    vector<vector<int>> graph6 = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, -8},
        {0, 0, -6, 0, 0},
        {0, 0, 0, 1, 0}};
    g.loadGraph(graph6); // Load the graph to the object.
    g.printGraph();                                     // Should print: "Graph with 5 vertices and 3 edges."
    cout << "Algorithms:*" << endl;
    cout << Algorithms::isConnected(g) << endl;                         // Should print: false
    cout << Algorithms::shortestPath(g, 4, 2) << endl; // Should print: "has a negative cycle"
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "1" (true). negative...
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "The graph isnt bipartite."
    cout << "//////////////////////////////" << endl;

cout << "////////// GRAPH #7 //////////" << endl;
    vector<vector<int>> graph7 = {
        {0, 0, 1, 0, -4},
        {0, 0, 0, 0, 0},
        {1, 0, 0, 0, -3},
        {0, 0, 0, 0, 0},
        {-4, 0, -3, 0, 0}};
    g.loadGraph(graph7); // Load the graph to the object.
    g.printGraph();                                     // Should print: "Graph with 5 vertices and 3 edges."
    cout << "Algorithms:*" << endl;
    cout << Algorithms::isConnected(g) << endl;                         //Should print: false    
    cout << Algorithms::shortestPath(g, 0, 2) << endl; // Should print: "has a negative cycle"
    cout << Algorithms::shortestPath(g, 0, 1) << endl; // Should print: "no path"
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "1" true
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "The graph isnt bipartite."
    cout << "//////////////////////////////" << endl;

    cout << "////////// GRAPH #8 //////////" << endl;
    vector<vector<int>> graph8 = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph8); // Load the graph to the object.
    g.printGraph();                                     // Should print: "Graph with 5 vertices and 0 edges." 
    cout << "Algorithms:*" << endl;
    cout << Algorithms::isConnected(g) << endl;                         //Should print: false    
    cout << Algorithms::shortestPath(g, 0, 2) << endl; // Should print: no path
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "0" false
    // cout << Algorithms::isBipartite(g) << endl;        // Should print: "The graph is bipartite."
    cout << "//////////////////////////////" << endl;
}