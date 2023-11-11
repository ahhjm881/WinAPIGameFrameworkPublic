#include "QuadNode.h"
#include "Debug.h"

QuadNode::QuadNode(const Vector& pos, const Vector& scale, Depth depth, Depth maxDepth)
	: m_position(pos), m_scale(scale), m_node{ nullptr, nullptr, nullptr, nullptr }, m_depth(depth), m_maxDepth(maxDepth), m_empty(true), m_path(nullptr)
	, m_colliders{}
{}

QuadNode::~QuadNode()
{
	for (int i = 0; i < 4; i++)
	{
		if (m_node[i] != nullptr)
			delete m_node[i];
	}
}

#include "AABBCollider.h"
const std::vector<class AABBCollider*>& QuadNode::GetColliders()
{
	return m_colliders;
}

bool QuadNode::Leaf() const
{
	bool on = false;

	for (int i = 0; i < 4; i++)
	{
		if (m_node[i] == nullptr)
		{
			on = true;
			break;
		}
	}

	return on;
}

void QuadNode::AllocChildNode()
{
	Vector halfSize = HalfSize();
	Vector divideSize = DivideSize();
	Vector pos = m_position;

	m_node[0] = new QuadNode(pos + divideSize, halfSize, m_depth + 1, m_maxDepth);
	m_node[1] = new QuadNode(pos + Vector(-divideSize.x, divideSize.y), halfSize, m_depth + 1, m_maxDepth);
	m_node[2] = new QuadNode(pos + Vector(-divideSize.x, -divideSize.y), halfSize, m_depth + 1, m_maxDepth);
	m_node[3] = new QuadNode(pos + Vector(divideSize.x, -divideSize.y), halfSize, m_depth + 1, m_maxDepth);
}

void QuadNode::GetAllLeafNode(std::vector<QuadNode*>& v)
{
	if (Leaf())
	{
		v.push_back(this);
		return;
	}

	m_node[0]->GetAllLeafNode(v);
	m_node[1]->GetAllLeafNode(v);
	m_node[2]->GetAllLeafNode(v);
	m_node[3]->GetAllLeafNode(v);
}

void QuadNode::DebugDraw(const RenderInfo& info, bool emptyOnly)
{

	if (Leaf())
	{
		AABB aabb = GetAABB();

		if (Empty())
			Debug::DrawRect(aabb.GetPos(), aabb.GetSize(), RGB(0, 0, 255));
		else if (!emptyOnly)
		{
			if (m_colliders.size() > 0)
				Debug::DrawRect(aabb.GetPos(), aabb.GetSize(), RGB(0, 255, 0));
			else
				Debug::DrawRect(aabb.GetPos(), aabb.GetSize(), RGB(255, 0, 0));
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (m_node[i] != nullptr)
			m_node[i]->DebugDraw(info, emptyOnly);
	}
}

QuadNode* QuadNode::operator[](int index)
{
	return m_node[index];
}