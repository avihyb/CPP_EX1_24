#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;




TEST_CASE("Test isConnected")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == 1); // Should be "1".

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == 0); // Should be "0".

    vector<vector<int>> graph3 = {
        {0, 1, 0},
        {1, 0, 0},
        {0, 1, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isConnected(g) == 0); // Should be "0".

    vector<vector<int>> graph4 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 0, 2, 1, 0},
        {0, 0, 1, 9, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == 0); // Should be "0".

    vector<vector<int>> graph5 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph5);
    CHECK(ariel::Algorithms::isConnected(g) == 0); // Should be "0".

    vector<vector<int>> graph6 = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}};
    g.loadGraph(graph6);
    CHECK(ariel::Algorithms::isConnected(g) == 1); // Should be "0".
}

TEST_CASE("Test shortestPath")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "-1");

    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph3);
    
    CHECK(ariel::Algorithms::shortestPath(g, 0, 3) == "0->1->2->3");
    CHECK(ariel::Algorithms::shortestPath(g, 2, 0) == "2->0");

    vector<vector<int>> graph4 = {
        {1, 2, 3, 4},
        {0, 2, 1, 0}, 
        {1, 0, 1, 0}, 
        {9, 2, 3, 0}};
        g.loadGraph(graph4);
    CHECK(ariel::Algorithms::shortestPath(g, 2, 3) == "2->0->3");
    CHECK(ariel::Algorithms::shortestPath(g, 1, 3) == "1->2->0->3");
    // Negative cycle in graph while running shortestPath
    vector<vector<int>> graph5 = {
        {0, 0, 0, 0},
        {4, 0, -6, 0},
        {0, 0, 0, 5},
        {0, -2, 0, 0}};
        g.loadGraph(graph5);
    CHECK(ariel::Algorithms::shortestPath(g, 1, 3) == "-1");
    CHECK(ariel::Algorithms::negativeCycle(g) == 1);
}


TEST_CASE("Test isContainsCycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "0->1->0");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "0->1->0");

    vector<vector<int>> graph3 = {
        {0, 0, 0, 0},
        {4, 0, -6, 0},
        {0, 0, 0, 5},
        {0, -2, 0, 0}};
        g.loadGraph(graph3);
    CHECK(ariel::Algorithms::shortestPath(g,1,3) == "-1");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "1->2->3");

    std::vector<std::vector<int>> graph4 = {
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {1, 0, 0, 1},
        {0, 0, 0, 0}
    };
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "0->1->2->0");

    std::vector<std::vector<int>> graph5 = {
    {0, 1, 0, 0, 1},
    {0, 0, 1, 0, 0},
    {0, 0, 0, 1, 0},
    {0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0}};

// Cycle: 1->2->3->4->5->1
g.loadGraph(graph5);
CHECK(ariel::Algorithms::isContainsCycle(g) == "0->1->2->3->4->0");

}
TEST_CASE("Test isBipartite")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={2, 0}, B={1}");
    

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isBipartite(g) == "Not bipartite");

    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 0},
        {1, 0, 3, 0, 0},
        {0, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={4, 2, 0}, B={3, 1}");
}

TEST_CASE("Test negative cycles"){
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 0, 0, 0},
        {4, 0, -6, 0},
        {0, 0, 0, 5},
        {0, -2, 0, 0}};
        g.loadGraph(graph);
    CHECK(ariel::Algorithms::negativeCycle(g) == 1);
    

    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph1);
    CHECK(ariel::Algorithms::negativeCycle(g) == 0);

    vector<vector<int>> graph2 = {
        {0, 0, 0, 0},
        {4, 0, -3, 0},
        {0, 0, 0, -5},
        {0, -7, 0, 0}};
        g.loadGraph(graph2);
    CHECK(ariel::Algorithms::negativeCycle(g) == 1);
    




}
TEST_CASE("Test invalid graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));
}

TEST_CASE("Test single-node graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {{0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == 0);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "-1");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0}, B={}");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "No cycles");
}