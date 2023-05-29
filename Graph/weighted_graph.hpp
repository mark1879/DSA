#ifndef WEIGHTED_GRAPH_HPP
#define WEIGHTED_GRAPH_HPP
#include <iostream>
#include <vector>

class WeightedGraph
{
public:
   virtual ~WeightedGraph() {}
   virtual size_t VertexCount() const = 0;
   virtual size_t EdgeCount() const = 0;
   virtual bool BFS(size_t start, std::vector<size_t>& order) const = 0;
   virtual bool DFS(size_t start, std::vector<size_t>& order) const = 0;
   virtual bool AddEdge(size_t src, size_t dst, int weight) = 0;
   virtual bool RemoveEdge(size_t src, size_t dst) = 0;
   virtual bool HasEdge(size_t src, size_t dst) const = 0;
   virtual int  Weight(size_t src, size_t dst) const = 0;

public:
   const static int kIllegalWeight;
   const static size_t kIllegalVertex;
};

const int WeightedGraph::kIllegalWeight = INT_MAX;
const size_t WeightedGraph::kIllegalVertex = INT_MAX;

#endif