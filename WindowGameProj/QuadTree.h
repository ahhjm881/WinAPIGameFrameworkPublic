#pragma once
#include <vector>
#include "AABBCollider.h"
#include "QuadNode.h"
#include "Debug.h"
#include "PathNode.h"

class QuadTree
{
private:
	std::vector<AABBCollider*> m_colliders;
	std::vector<PathNode*> m_graph;

	QuadNode* root;
	Depth m_maxDepth;
	Depth m_defaultDivide;

	bool m_threading;
public:
	QuadTree();

	void Start(const Vector& pos, const Vector& size, bool nodeIncludingCollider, std::vector<AABBCollider*> colliders, Depth depth = 2, Depth defaultDivide = 0);
	PathNode* QueryPath(AABB aabb);
	void QueryCollider(AABB colliderData, std::vector<AABBCollider*>& results);
	void QueryColliderWithRay(Vector origin, Vector ray, std::vector<AABBCollider*>& results, bool once);
	const std::vector<PathNode*>& GetGraph() const;

	void DebugDraw(const RenderInfo& info, bool emptyOnly = true);
	QuadNode* GetRoot() const { return root; }

private:
	void Divide(QuadNode* node, Depth depth);
	void ConnectPath();
	void BindCollider(bool nodeIncludingCollider);
	

};

