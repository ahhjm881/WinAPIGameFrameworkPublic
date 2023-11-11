#pragma once
#include "type.h"
#include "Info.h"
#include "Actor.h"
#include <list>
#include <queue>

class Scene
{
public:
	Scene(int index, IVector size)
		:m_index(index), m_size(size)
	{}

	virtual ~Scene()
	{
		for (auto item : m_actorList)
		{
			delete item;
		}
	}

	void AddActor(Actor* actor)
	{
		actor->m_scene = this;
		m_actorList.push_back(actor);
	}

	void Loop(const UpdateInfo& info, const RenderInfo& ri)
	{
		for (auto item : m_actorList)
		{
			if (item->destroyed)
			{
				m_pendingActorQueue.push(item);
				continue;
			}

			if (item->GetEnabled() == false)continue;

			item->UpdateComponent(info);
			item->Update(info, ri);

		}
		for (auto item : m_actorList)
		{
			if (item->GetEnabled() == false)continue;

			item->RenderComponent(ri);
		}

		while (!m_pendingActorQueue.empty())
		{
			auto actor = m_pendingActorQueue.front();
			m_pendingActorQueue.pop();

			m_actorList.remove(actor);
			delete actor;
		}

	}

private:
	std::list<Actor*> m_actorList;
	std::queue<Actor*> m_pendingActorQueue;

	int m_index;
	IVector m_size;
};