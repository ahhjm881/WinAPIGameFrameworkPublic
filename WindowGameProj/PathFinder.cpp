#include "PathFinder.h"
#include "QuadTree.h"
#include "AStar.h"
#include "Input.h"
#include <vector>

PathFinder::PathFinder(Actor* actor, QuadTree* tree)
	:Component(actor), m_tree(tree), m_targetDirty(true), m_paths{},
	m_speed(100), m_currentPathIndex(-1), m_currentPath(nullptr)
{
	SetHeuristicFunction(&AStar::DefaultHeuristic);
}

Vector PathFinder::GetTarget() const
{
	return m_currentTargetPos;
}

void PathFinder::SetTarget(Vector targetPos)
{
	m_currentTargetPos = targetPos;
	m_targetDirty = true;
}

void PathFinder::SetHeuristicFunction(AStar::HeuristicDelegate heuristic)
{
	m_heuristic = heuristic;
}

void PathFinder::ResetHeuristicFunction()
{
	SetHeuristicFunction(&AStar::DefaultHeuristic);
}

void PathFinder::Update(const UpdateInfo& ui)
{
	if (m_targetDirty) UpdatePath();
	if (m_currentPathIndex >= m_paths.size()) return;
	
	Transform* transform = GetActor()->GetTransform();
	Vector targetPos = m_paths[m_currentPathIndex]->Position();
	Vector myPos = transform->GetPosition();
	
	Vector newPos = Vector::MoveToWord(myPos, targetPos, ui.deltaTime * m_speed);
	transform->SetPosition(newPos);
	
	if ((newPos - targetPos).sqrMagnitude() <= 0.1f)
	{
		if (m_paths.size() - 1 > m_currentPathIndex)
		{
			m_currentPath = m_paths[++m_currentPathIndex];
		}
	}


}

void PathFinder::UpdatePath()
{
	if (!m_targetDirty) return;
	m_targetDirty = false;

	auto collider = GetActor()->GetComponent<AABBCollider>();

	if (collider == nullptr)
		return;

	PathNode* currentPath = m_tree->QueryPath(collider->GetAABB());
	PathNode* targetPath = m_tree->QueryPath(AABB(m_currentTargetPos, collider->GetAABB().GetSize()));

	if (currentPath == nullptr || targetPath == nullptr)
	{
		Debug::Log("path not found.");
		return;
	}

	AStar astar;
	astar.Search(currentPath, targetPath, m_heuristic);

	auto getPaths = astar.GetPath();
	m_paths.swap(getPaths);
	if (m_currentPathIndex == -1 && m_paths.size() > 0)
	{
		m_currentPathIndex = 0;
		m_currentPath = m_paths[0];
		return;
	}

	bool fail = true;
	for(int i=0;i<m_paths.size();i++)
	{
		PathNode* path = m_paths[i];
		if (path == m_currentPath)
		{
			fail = false;
			m_currentPathIndex = i;
			break;
		}
	}

	if (fail)
		m_currentPathIndex = 0;

}

void PathFinder::DrawDebug()
{
	if (m_currentPathIndex == -1) return;
	if (m_paths.size() == 0) return;

	for (size_t i = 0; i < m_paths.size() - 1; i++)
	{
		Debug::DrawLine(m_paths[i]->Position(), m_paths[i + 1]->Position(), RGB(255, 0, 0));
		Debug::DrawRect(m_paths[i]->Position(), m_paths[i]->Size(), RGB(0, 0, 255));
		Debug::DrawRect(m_paths[i + 1]->Position(), m_paths[i + 1]->Size(), RGB(0, 0, 255));
	}
}
