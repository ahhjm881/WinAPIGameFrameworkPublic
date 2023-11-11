#include "QuadTree.h"
#include <Windows.h>
#include <thread>
#include <functional>
#include "Actor.h"

QuadTree::QuadTree() : root(nullptr), m_maxDepth(0), m_defaultDivide(0) {}

void QuadTree::Start(const Vector& pos, const Vector& size, bool nodeIncludingCollider, std::vector<AABBCollider*> colliders, Depth depth, Depth defaultDivide)
{
	if (root != nullptr)
		delete root;

	//timer
	ULONGLONG ticks = GetTickCount64();

	m_threading = false;

	while (!m_graph.empty())
	{
		delete m_graph.back();
		m_graph.pop_back();
	}

	m_colliders = colliders;

	root = new QuadNode(pos, size, 0, depth);
	m_maxDepth = depth;
	m_defaultDivide = defaultDivide;

	for (auto i : colliders)
	{
		root->AddCollider(i);
	}

	Debug::Log("QuadTree dividing");
	Divide(root, 0);

	std::vector<QuadNode*> leafNode;
	root->GetAllLeafNode(leafNode);

	Debug::Log("QuadTree node connecting");
	for (auto i = leafNode.begin(); i != leafNode.end(); i++)
	{
		m_graph.push_back(new PathNode(*i));
	}

	ConnectPath();
	//BindCollider(nodeIncludingCollider);


	Debug::Log("QuadTree node count : ");
	Debug::Log((int)leafNode.size());
	Debug::Log("QuadTree Divide Time : ");
	Debug::Log((GetTickCount64() - ticks) * 0.001f);
}

void QuadTree::DebugDraw(const RenderInfo& info, bool emptyOnly)
{
	if (root == nullptr) return;
	std::vector<QuadNode*> nodes;
	root->GetAllLeafNode(nodes);

	for (auto node : nodes)
	{
		if(node->Empty())
			Debug::DrawRect(node->Position(), node->Size(), RGB(0, 0, 255));
		else
			Debug::DrawRect(node->Position(), node->Size(), RGB(255, 0, 0));
	}
}

void QuadTree::Divide(QuadNode* node, Depth depth)
{
	auto& colliders = node->GetColliders();
	bool col = false;
	bool div = false;
	bool isFully = false;

	if ((int)depth > ((int)m_maxDepth) - 1)
	{
		return;
	}


	for (auto i = colliders.begin(); i != colliders.end(); i++)
	{
		AABBCollider* target = *i;

		if (!div && ((int)depth <= ((int)m_defaultDivide) - 1 || (isFully=AABB::Collision(target->GetAABB(), node->GetAABB()))))
		{
			div = true;
			node->AllocChildNode();
		}

		for (int i = 0; div && i < 4; i++)
		{
			QuadNode* childNode = (*node)[i];
			if (col = AABB::Collision(target->GetAABB(), childNode->GetAABB()))
			{
				childNode->AddCollider(target);
				childNode->SetEmpty(false);
			}

		}

	}

	if (colliders.size() == 0 && (int)depth <= ((int)m_defaultDivide) - 1)
	{
		node->AllocChildNode();
		div = true;
	}

	node->SetEmpty(!isFully);

	if (div)
	{
		Divide((*node)[0], depth + 1);
		Divide((*node)[1], depth + 1);
		Divide((*node)[2], depth + 1);
		Divide((*node)[3], depth + 1);
	}
}

PathNode* QuadTree::QueryPath(AABB aabb)
{
	if (root == nullptr)
		return nullptr;

	std::vector<QuadNode*> currentNodes;
	std::vector<QuadNode*> nextNodes;
	std::vector<QuadNode*> results;
	currentNodes.push_back(root);

	while (1)
	{
		for (auto cNode : currentNodes)
		{
			if (AABB::Collision(aabb, cNode->GetAABB()))
			{
				if (cNode->Empty() && cNode->Leaf())
				{
					results.push_back(cNode);
					continue;
				}

				for (int i = 0; i < 4; i++)
				{
					QuadNode* temp = (*cNode)[i];
					if (temp == nullptr) continue;

					nextNodes.push_back(temp);
				}
			}
		}

		if (nextNodes.empty())
		{
			break;
		}

		currentNodes.clear();
		for (auto node : nextNodes)
		{
			currentNodes.push_back(node);
		}
		nextNodes.clear();
	}


	if (results.size() == 0)return nullptr;

	QuadNode* minNode = nullptr;
	float dis = 999999999999.f;
	for (auto node : results)
	{
		if (minNode == nullptr)
		{
			minNode = node;
			continue;
		}

		float d = (node->Position() - aabb.GetPos()).sqrMagnitude();

		if (d < dis)
		{
			dis = d;
			minNode = node;
		}
	}

	if (minNode == nullptr)return nullptr;
	return minNode->Path();
}
#include <deque>
#include <algorithm>
void QuadTree::QueryCollider(AABB colliderData, std::vector<AABBCollider*>& results)
{
	results.clear();
	if (root == nullptr)return;

	std::vector<QuadNode*> currentList;
	std::vector<QuadNode*> nextList;
	currentList.push_back(root);

	while (1)
	{
		int count = 0;
		for (QuadNode* node : currentList)
		{
			for (int i = 0; i < 4; i++)
			{
				QuadNode* child = (*node)[i];
				if (child == nullptr) continue;

				if (AABB::Collision(colliderData, child->GetAABB()))
				{
					nextList.push_back(child);
				}
			}
			count++;
		}


		bool isAllLeaf = true;
		for (QuadNode* node : nextList)
		{
			if (!node->Leaf())
			{
				isAllLeaf = false;
			}
		}
		
		if (isAllLeaf)
		{
			for (auto node : nextList)
			{
				auto v = node->GetColliders();
				for (auto col : v)
					results.push_back(col);
			}


			std::sort(results.begin(), results.end());
			std::unique(results.begin(), results.end());

			return;
		}

		currentList.clear();

		currentList.swap(nextList);
	}
}

#include <unordered_set>
void QuadTree::QueryColliderWithRay(Vector origin, Vector ray, std::vector<AABBCollider*>& results, bool once=false)
{
	results.clear();
	std::vector<PathNode*> currentList;
	std::vector<PathNode*> nextList;
	std::unordered_set<PathNode*> backtrack;
	PathNode* path = QueryPath(AABB(origin, Vector::zero));
	if (path == nullptr)return;
	QuadNode* startNode = path->GetQuadNode();
	if (startNode == nullptr)return;
	currentList.push_back(startNode->Path());
	nextList.push_back(startNode->Path());

	while (1)
	{
		for (PathNode* node : currentList)
		{
			const std::vector<PathInfo>& paths = node->Paths();

			for (auto& path : paths)
			{
				if (backtrack.find(path.node) != backtrack.end())
					continue;

				AABB aabb = path.node->GetQuadNode()->GetAABB();

				if (AABB::CollisionRay(aabb, origin, ray))
				{
					nextList.push_back(path.node);
					backtrack.insert(path.node);
					for (auto col : path.node->GetQuadNode()->GetColliders())
					{
						results.push_back(col);

						if (once)
						{
							return;
						}
					}
				}
			}
		}

		if (nextList.size() == 0)
		{
			std::sort(results.begin(), results.end());
			std::unique(results.begin(), results.end());
			return;
		}

		currentList.clear();
		currentList.swap(nextList);
	}
}

const std::vector<PathNode*>& QuadTree::GetGraph() const
{
	return m_graph;
}

void QuadTree::ConnectPath()
{
	PathNode* n1 = nullptr, * n2 = nullptr;

	for (auto i = m_graph.begin(); i != m_graph.end(); i++)
	{
		for (auto j = m_graph.begin(); j != m_graph.end(); j++)
		{
			n1 = *i;
			n2 = *j;

			if (n1 == n2) continue;

			if (AABB::Collision(n1->Position(), n1->Size() * 1.01f, n2->Position(), n2->Size()))
			{
				n1->AddNeighibors(n2);
			}
		}
	}

}

#include <thread>
void QuadTree::BindCollider(bool nodeIncludingCollider)
{
	std::vector<QuadNode*> leafs;
	leafs.reserve(1000);
	root->GetAllLeafNode(leafs);

	for (auto node : leafs)
	{
		for (auto col : m_colliders)
		{
			if (AABB::Collision(col->GetAABB(), node->GetAABB()))
			{
				if (nodeIncludingCollider)
				{
					node->AddCollider(col);
				}
			}
		}
	}
}
