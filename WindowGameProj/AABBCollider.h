#pragma once
#include "AABB.h"
#include "Component.h"
#include "Actor.h"

class AABBCollider :
    public Component
{
private:
    Transform* m_transform;
    Vector m_offset;
    Vector m_size;
public:
    AABBCollider(Actor* actor, Vector offset, Vector size)
        : Component(actor), m_transform(actor->GetTransform()), m_offset(offset), m_size(size)
    {
    }

    bool Collision(const AABBCollider* collider) const
    {
        return AABB::Collision(
            m_transform->GetPosition(), m_transform->ScaledSize(),
            collider->m_transform->GetPosition(), collider->m_transform->ScaledSize()
        );
    }

    AABB GetAABB() const
    {
        Transform* transform = GetActor()->GetTransform();
        return AABB(transform->GetPosition() + m_offset, transform->GetSize() + m_size);
    }
};

