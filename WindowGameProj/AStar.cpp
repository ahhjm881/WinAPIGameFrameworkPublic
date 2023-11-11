#include "AStar.h"

AStar::AStar()
	: m_results()
{
}

AStar::~AStar()
{
}

void AStar::Search(PathNode* start, PathNode* end, HeuristicDelegate heuristic, float timeout)
{
	Calculate(end, start, heuristic, timeout);
}

ResultContainer AStar::GetPath()
{
	return m_results;
}

void AStar::Calculate(PathNode* start, PathNode* end, HeuristicDelegate heuristic, float timeout)
{
	Open open;
	Close close;

	PathNode* minNode = nullptr;

	start->parent = nullptr;
	start->w = 0.f;
	open.push(start);

	while (!open.empty())
	{
		minNode = GetMin(open);

		if (minNode == end)
		{
			ConstructPath(minNode, end);
			return;
		}

		if (minNode != nullptr)
			close.insert(minNode);
		else
			return;

		auto& paths = minNode->Paths();
		for (auto i = paths.begin(); i != paths.end(); i++)
		{
			PathNode* temp = (*i).node;
			if (!temp->Empty()) continue;
			if (close.find(temp) != close.end())continue;
			// size 처리 안함

			if (ContainOpen(open, temp))
			{
				if (temp->w > minNode->w + (*i).w)
				{
					temp->parent = minNode;
					temp->w = minNode->w + (*i).w;
				}
			}
			else
			{
				temp->parent = minNode;
				temp->w = (*i).w + minNode->w;

				temp->f = temp->w + heuristic(temp, end);
				//temp->f = temp->w + temp->Heuristics(end);

				open.push(temp);
			}
		}
	}

}

void AStar::ConstructPath(PathNode* node, PathNode* endNode)
{
	m_results.clear();

	do
	{
		m_results.push_back(node);
		node = node->parent;
	} while (node != nullptr);
}


