#ifndef WEIGHTED_ADJACENT_LIST_HPP
#define WEIGHTED_ADJACENT_LIST_HPP

#include "weighted_graph.hpp"
#include "Logger.hpp"
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <gtest/gtest.h>

class WeightedAdjacentList : public WeightedGraph
{
private:
    size_t vertex_count_;
    size_t edge_count_;
    // pair<dst, weight>
    std::vector<std::vector<std::pair<size_t, size_t>>> adjacent_list_;
    
public:
    const static int kIllegalWeight;

public:
    WeightedAdjacentList(size_t vertex_count)
        : vertex_count_(vertex_count)
        , edge_count_(0)
    {
        adjacent_list_.resize(vertex_count);
    }

    ~WeightedAdjacentList()
    {}

    size_t VetextCount() const override
    {
        return vertex_count_;
    }

    size_t EdgeCount() const override
    {
        return edge_count_;
    }

    bool BFS(size_t start, std::vector<size_t>& order) const
    {
        if (start >= vertex_count_)
        {
            LOG_INFO("start is Out of Range");
            return false;
        }

        std::vector<bool> visited(vertex_count_, false);
        std::queue<size_t> queue;

        queue.push(start);
        visited[start] = true;

        while (!queue.empty())
        {
            size_t current = queue.front();
            queue.pop();
            order.push_back(current);

            for (const auto& it : adjacent_list_[current])
            {
                if (!visited[it.first])
                {
                    queue.push(it.first);
                    visited[it.first] = true;
                }
            }
        }

        return true;
    }

    bool DFS(size_t start, std::vector<size_t>& order) const
    {
        if (start >= vertex_count_)
        {
            LOG_INFO("start is Out of Range");
            return false;
        }

        std::vector<bool> visited(vertex_count_, false);
        std::stack<size_t> stack;

        stack.push(start);
        visited[start] = true;

        while (!stack.empty())
        {
            size_t current = stack.top();
            stack.pop();
            order.push_back(current);

            for (const auto& it : adjacent_list_[current])
            {
                if (!visited[it.first])
                {
                    stack.push(it.first);
                    visited[it.first] = true;
                }
            }
        }

        return true;
    }

    bool AddEdge(size_t src, size_t dst, int weight)
    {
        if (src >= vertex_count_ || dst >= vertex_count_)
        {
            LOG_INFO("src or dst is Out of Range");
            return false;
        }

        for (const auto& it :  adjacent_list_[src])
        {
            if (it.first == dst)
            {
                LOG_INFO("Edge already exists");
                return false;
            }
        }

        adjacent_list_[src].push_back(std::make_pair(dst, weight));
        ++edge_count_;

        return true;
    }

    bool RemoveEdge(size_t src, size_t dst)
    {
        if (src >= vertex_count_ || dst >= vertex_count_)
        {
            LOG_INFO("src or dst is Out of Range");
            return false;
        }

        for (auto it = adjacent_list_[src].begin(); it != adjacent_list_[src].end(); ++it)
        {
            if (it->first == dst)
            {
                adjacent_list_[src].erase(it);
                --edge_count_;
                return true;
            }
        }

        LOG_INFO("Edge does not exist");

        return false;
    }

    bool HasEdge(size_t src, size_t dst) const
    {
        if (src >= vertex_count_ || dst >= vertex_count_)
        {
            LOG_INFO("src or dst is Out of Range");
            return false;
        }

        for (const auto& it : adjacent_list_[src])
        {
            if (it.first == dst)
                return true;
        }

        return false;
    }

    int Weight(size_t src, size_t dst) const
    {
        if (src >= vertex_count_ || dst >= vertex_count_)
        {
            LOG_INFO("src or dst is Out of Range");
            return kIllegalWeight;
        }

        for (const auto& it : adjacent_list_[src])
        {
            if (it.first == dst)
                return it.second;
        }

        return kIllegalWeight;
    }

public:
    static void Test()
    {
        std::cout << "AdjacentList::Test()" << std::endl;

        WeightedGraph* graph = new WeightedAdjacentList(8);

         // Test AddEdge
        EXPECT_EQ(graph->AddEdge(0, 1, 1), true);
        EXPECT_EQ(graph->AddEdge(0, 6, 6), true);
        EXPECT_EQ(graph->AddEdge(1, 2, 1), true);
        EXPECT_EQ(graph->AddEdge(1, 3, 2), true);
        EXPECT_EQ(graph->AddEdge(2, 4, 2), true);
        EXPECT_EQ(graph->AddEdge(2, 5, 3), true);
        EXPECT_EQ(graph->AddEdge(3, 6, 3), true);
        EXPECT_EQ(graph->AddEdge(3, 7, 4), true);
        EXPECT_EQ(graph->AddEdge(4, 6, 2), true);
        EXPECT_EQ(graph->AddEdge(6, 7, 1), true);

        EXPECT_EQ(graph->AddEdge(2, 4, 2), false);
        EXPECT_EQ(graph->AddEdge(7, 8, 1), false);

        EXPECT_EQ(graph->VetextCount(), 8);
        EXPECT_EQ(graph->EdgeCount(), 10);

        // Test BFS
        std::vector<size_t> bfs_answer = {0, 1, 6, 2, 3, 7, 4, 5};
        std::vector<size_t> bfs_order;
        graph->BFS(0, bfs_order);

        EXPECT_EQ(bfs_answer.size(), bfs_order.size());
        for (size_t i = 0, size = bfs_order.size(); i < size; ++i)
        {
            EXPECT_EQ(bfs_answer[i], bfs_order[i]);
        }

        // Test DFS
        std::vector<size_t> dfs_answer = {0, 6, 7, 1, 3, 2, 5, 4};
        std::vector<size_t> dfs_order;
        graph->DFS(0, dfs_order);

        EXPECT_EQ(dfs_answer.size(), dfs_order.size());
        for (size_t i = 0, size = dfs_order.size(); i < size; ++i)
        {
            EXPECT_EQ(bfs_answer[i], bfs_order[i]);
        }

        // Test Weight
        EXPECT_EQ(graph->Weight(3, 7), 4);
        EXPECT_EQ(graph->Weight(8, 9), kIllegalWeight);
        EXPECT_EQ(graph->Weight(3, 4), kIllegalWeight);


        // Test RemoveEdge
        EXPECT_EQ(graph->RemoveEdge(0, 1), true);
        EXPECT_EQ(graph->EdgeCount(), 9);
        EXPECT_EQ(graph->HasEdge(0, 1), false);

        EXPECT_EQ(graph->RemoveEdge(0, 1), false);
        EXPECT_EQ(graph->RemoveEdge(8, 9), false);
    }
};

const int WeightedAdjacentList::kIllegalWeight = INT_MIN;

#endif