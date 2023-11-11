#pragma once
#include <Windows.h>
#include "Transform.h"
#include <string>
#include "Component.h"
#include <vector>
#include "Info.h"
#include <cassert>


class Scene;

class Actor
{
private:
	Transform* m_transform;
	std::string name;

	Scene* m_scene;
	std::vector<Component*> m_components;

	bool enabled;
	bool destroyed;

	int order;

private:
	void UpdateComponent(const UpdateInfo& info)
	{
		if (GetEnabled() == false)return;

		for (auto i = m_components.begin(); i != m_components.end(); i++)
		{
			if((*i)->GetEnabled())
				(*i)->Update(info);
		}
	}
	void RenderComponent(const RenderInfo& info)
	{
		if (GetEnabled() == false)return;

		for (auto i = m_components.begin(); i != m_components.end(); i++)
		{
			if ((*i)->GetEnabled())
				(*i)->Render(info);
		}
	}

	friend class Scene;

public:

	Actor(CKMath::Vector pos)
		: m_transform(new Transform(pos)), name("Undefined name"), destroyed(false), enabled(true), order(0), m_components({}) {}

	virtual ~Actor() 
	{
		for (auto i = m_components.begin(); i != m_components.end(); i++)
			delete (*i);

		delete m_transform;
	}

	void AddComponent(Component* component) { m_components.push_back(component); }

	template<class T>
	T* GetComponent()
	{
		if (m_components.size() == 0) return nullptr;

		for (auto i = m_components.begin(); i != m_components.end(); i++)
		{
			if (typeid(**i) == typeid(T))
				return dynamic_cast<T*>(*i);
		}

		return nullptr;
	}

	virtual void Update(const UpdateInfo&, const RenderInfo&) = 0;
	virtual void Collision(const CollisionInfo&) {}

public:
	Transform* GetTransform() const { return m_transform; }

	bool GetEnabled() const { return enabled; }
	void SetEnabled(bool value)
	{
		enabled = value;
		for (auto com : m_components)
		{
			com->SetEnabled(value);
		}
	}

	int GetOrder() const { return order; }
	void SetOrder(int value) { order = value; }
	bool IsDestroyed() const { return destroyed; }

protected:
	Scene* GetCurrentScene() const { return m_scene; }

public:
	static void Destory(Actor* actor) { actor->destroyed = true; }
};

