#pragma once
#include "Component.h"
#include "Actor.h"
#include "AStar.h"
#include <unordered_set>

class PathFinder :
    public Component
{
public:
    PathFinder(Actor* actor, class QuadTree* tree);

    Vector GetTarget() const;
    void SetTarget(Vector targetPos);
    void SetHeuristicFunction(AStar::HeuristicDelegate heuristic);
    void ResetHeuristicFunction();
    void SetSpeed(float speed) { m_speed = speed; }
    float GetSpeed() const { return m_speed; }

public:
    virtual void Update(const UpdateInfo& ui) override;

private:
    void UpdatePath();
    void DrawDebug();

private:
    QuadTree* m_tree;
    Vector m_currentTargetPos;

    bool m_targetDirty;
    ResultContainer m_paths;
    PathNode* m_currentPath;
    int m_currentPathIndex;
    float m_speed;
    AStar::HeuristicDelegate m_heuristic;

};

