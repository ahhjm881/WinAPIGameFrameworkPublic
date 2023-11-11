#pragma once
#include "Info.h"
#include "AABB.h"
#include <vector>

namespace
{
	using namespace CKMath;
}

typedef unsigned int Depth;

class PathNode;

class QuadNode
{
private:
	QuadNode* m_node[4];
	std::vector<class AABBCollider*> m_colliders;

	Vector m_position;
	Vector m_scale;

	Depth m_depth;
	Depth m_maxDepth;

	bool m_empty;

	class PathNode* m_path;

public:
	QuadNode(const Vector& pos, const Vector& scale, Depth depth, Depth maxDepth);

	~QuadNode();

	bool Empty() const { return m_empty; }
	void SetEmpty(bool value) { m_empty = value; }
	void AddCollider(class AABBCollider* collider) { m_colliders.push_back(collider); }
	const std::vector<class AABBCollider*>& GetColliders();
	Vector Size() const { return m_scale; }
	Depth GetDepth() const { return m_depth; }
	Vector Position() const { return m_position; }
	Vector HalfSize() const { return m_scale * 0.5f; }
	Vector DivideSize() const { return m_scale * 0.25f; }
	class PathNode* Path() const { return m_path; }
	AABB GetAABB() const { return AABB(m_position, m_scale); }

	bool Leaf() const;

	void AllocChildNode();
	void GetAllLeafNode(std::vector<QuadNode*>& v);

	void DebugDraw(const RenderInfo& info, bool emptyOnly = true);

	QuadNode* operator[](int index);
	friend class PathNode;
};
