#pragma once
#include "type.h"
#include "QuadNode.h"
#include <vector>
#include "Debug.h"

namespace
{
	using namespace CKMath;
}

struct PathInfo
{
	float w;

	PathNode* node;

	PathInfo() :w(0.f), node(nullptr) {}
	PathInfo(PathNode* node, float weight) :w(weight), node(node) {}
};

class PathNode
{
private:
	Vector m_position;
	Vector m_size;
	std::vector<PathInfo> m_paths;

	bool m_empty;
	QuadNode* m_quadNode;

public:
	float f;
	float w;

	PathNode* parent;

public:
	PathNode(QuadNode* node) : m_empty(node->Empty()), f(0.f), w(0.f), parent(nullptr), m_quadNode(node)
	{
		m_position = node->Position();
		m_size = node->Size();

		node->m_path = this;
	}

	Vector Position() const { return m_position; }
	Vector Size() const { return m_size; }
	bool Empty() const { return m_empty; }
	const std::vector<PathInfo>& Paths() { return m_paths; }
	float Heuristics(const PathNode* node) const { return (node->m_position - m_position).sqrMagnitude(); }
	QuadNode* GetQuadNode() const { return m_quadNode; }
	void AddNeighibors(PathNode* node)
	{
		//for (auto i = m_paths.begin(); i != m_paths.end(); i++)
		//{
		//	if ((*i).node == node)
		//		return;
		//}

		for (int i = 0; i < m_paths.size(); i++)
		{
				if (m_paths[i].node == node)
					return;
		}

		m_paths.push_back(PathInfo(node, (node->m_position - m_position).sqrMagnitude()));
	}

	void DebugDraw(const RenderInfo& info, bool drawLine=false)
	{
		if(m_empty)
			Debug::DrawRect(m_position, m_size, RGB(0, 0, 255));
		else
			Debug::DrawRect(m_position, m_size, RGB(255, 0, 0));

		if (!drawLine)return;

		for (auto i = m_paths.begin(); i != m_paths.end(); i++)
		{
			Debug::DrawLine(m_position, (*i).node->Position(), RGB(0, 255, 255));
		}
	}
};

