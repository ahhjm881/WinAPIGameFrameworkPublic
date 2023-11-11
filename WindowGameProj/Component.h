#pragma once

#include "Info.h"

class Component
{
public:
	Component(class Actor* actor)
		: m_actor(actor), m_enabled(true)
	{}

	class Actor* GetActor() const { return m_actor; }

	virtual void Update(const UpdateInfo& info) {}
	virtual void Render(const RenderInfo& info) {}


	bool GetEnabled() const { return m_enabled; }
	void SetEnabled(bool value) { m_enabled = value; }

private:
	class Actor* m_actor;
	bool m_enabled;
};