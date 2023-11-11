#pragma once

#include <queue>
#include <unordered_set>
#include <vector>
#include <functional>
#include <limits>

#include "PathNode.h"


struct __cmp__
{
	bool operator()(PathNode* n1, PathNode* n2)
	{
		if (n1->f > n2->f)
			return true;
		else
			return false;
	}
};



typedef std::priority_queue<PathNode*, std::vector<PathNode*>, __cmp__ > Open;
typedef std::unordered_set<PathNode*> Close;
typedef std::vector<PathNode*> ResultContainer;


template <class T, class S, class C>
S& Container(std::priority_queue<T, S, C>& q) {
	struct HackedQueue : private std::priority_queue<T, S, C> {
		static S& Container(std::priority_queue<T, S, C>& q) {
			return q.* & HackedQueue::c;
		}
	};
	return HackedQueue::Container(q);
}

class AStar
{
private:
	ResultContainer m_results;


public:
	AStar();
	~AStar();
	using HeuristicDelegate = std::function<float(PathNode*, PathNode*)>;

	void Search(PathNode* start, PathNode* end, HeuristicDelegate heuristic, float timeout = 2.f);
	ResultContainer GetPath();
	static float DefaultHeuristic(PathNode* current, PathNode* endPoint)
	{
		return (current->Position() - endPoint->Position()).sqrMagnitude();
	}
private:
	void Calculate(PathNode* start, PathNode* end, HeuristicDelegate heuristic, float timeout);
	void ConstructPath(PathNode* node, PathNode* endNode);

	PathNode* GetMin(Open& open)
	{
		if (open.size() == 0)return nullptr;

		auto top = open.top();
		open.pop();
		return top;
	}

	bool ContainOpen(Open& open, const PathNode* node)
	{
		auto& r = Container<PathNode*, std::vector<PathNode*>, __cmp__>(open);
		for (auto i = r.begin(); i != r.end(); i++)
		{
			if ((*i) == node)return true;
		}

		return false;

	}
};

