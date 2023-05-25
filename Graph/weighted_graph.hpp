#ifndef WEIGHTED_GRAPH_HPP
#define WEIGHTED_GRAPH_HPP
#include <iostream>
#include <vector>

class WeightedGraph
{
public:
   virtual ~WeightedGraph() {}
   virtual size_t VetextCount() const = 0;
   virtual size_t EdgeCount() const = 0;
   virtual void BFS(size_t vertex, std::vector<size_t>& order) const = 0;
   virtual void DFS(size_t vertex, std::vector<size_t>& order) const = 0;
   virtual bool AddEdge(size_t vertex1, size_t vertex2, int weight) = 0;
   virtual bool RemoveEdge(size_t vertex1, size_t vertex2) = 0;
   virtual bool HasEdge(size_t vertex1, size_t vertex2) const = 0;
   virtual int  Weight(size_t vertex1, size_t vertex2) const = 0;
};

#endif