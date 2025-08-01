#pragma once
#include <vector>
#include "Queue.hpp"
#include "Vector4.hpp"

namespace CommonUtilities
{
	static const int MapWidth = 20;
	static const int MapHeight = 20;
	static const int TileCount = MapWidth * MapHeight;

	enum class Tile
	{
		Impassable,
		Passable
	};

	struct Node
	{
		std::vector<Node *> myAdjacentNodes;
		Tile myTile;
		bool visited = false;
		int distance = 999;
		Node *myPredecessor = nullptr;
		int myIndex = 0;
	};
	//std::vector<int> Dijkstra(const std::vector<Tile>& aMap, int aStartIndex, int anEndIndex);

	inline Node *FindPath(std::vector<Node> &aNodes, int aStartIndex, int anEndIndex)
	{
		Queue<Node *> queue;

		for (Node &node : aNodes)
		{
			node.distance = 999;
		}
		aNodes[aStartIndex].distance = 0;

		queue.Enqueue(&aNodes[aStartIndex]);

		while (!queue.IsEmpty())
		{
			Node *v = queue.Dequeue();
			int temp = v->myIndex;
			for (Node *node : v->myAdjacentNodes)
			{
				if (node->distance == 999)
				{
					node->distance = v->distance + 1;
					node->myPredecessor = v;
					queue.Enqueue(node);
					if (node == &aNodes[anEndIndex])
					{
						return node;
					}
				}
			}
		}
		return nullptr;
	}

	inline std::vector<int> Dijkstra(const std::vector<Tile> &aMap, int aStartIndex, int anEndIndex)
	{
		if (aStartIndex == anEndIndex)
		{
			return {aStartIndex};
		}
		std::vector<Node> nodes;
		for (size_t i = 0; i < aMap.size(); i++)
		{
			Node node;
			node.myTile = aMap[i];
			nodes.push_back(node);
			nodes[i].myIndex = i;
		}

		for (size_t i = 0; i < nodes.size(); i++)
		{
			int ef = i;
			if (i % MapHeight != 0 && i != 0) // left
			{
				if (nodes[i - 1].myTile == Tile::Passable)
				{
					nodes[i].myAdjacentNodes.push_back(&nodes[i - 1]);
				}
			}
			if ((i + 1) % (MapHeight) != 0 && i != nodes.size() - 1) // right
			{
				if (nodes[i + 1].myTile == Tile::Passable)
				{
					nodes[i].myAdjacentNodes.push_back(&nodes[i + 1]);
				}
			}
			if (i > (MapWidth - 1) && nodes[i - MapWidth].myTile == Tile::Passable) // up
			{
				nodes[i].myAdjacentNodes.push_back(&nodes[i - MapWidth]);
			}
			if (i < nodes.size() - MapWidth - 1 && nodes[i + MapWidth].myTile == Tile::Passable) // down
			{
				nodes[i].myAdjacentNodes.push_back(&nodes[i + MapWidth]);
			}
		}
		Node *node = FindPath(nodes, aStartIndex, anEndIndex);
		if (node == nullptr)
		{
			return {};
		}
		std::vector<Node *> path;
		while (node->myPredecessor != nullptr)
		{
			path.push_back(node);
			node = node->myPredecessor;
		}
		std::reverse(path.begin(), path.end());
		std::vector<int> result;
		result.push_back(aStartIndex);
		for (size_t i = 0; i < path.size(); i++)
		{
			result.push_back(path[i]->myIndex);
		}

		return result;
	}

}