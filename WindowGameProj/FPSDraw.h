#pragma once
#include "Actor.h"
#include "Text.h"

class FPSDraw :
    public Actor
{
private:
    Text* m_text;

public:
    FPSDraw(Vector pos) : Actor(pos), m_text(nullptr)
    {
        m_text = new Text(this);

        AddComponent(m_text);
    }

    virtual void Update(const UpdateInfo& info, const RenderInfo& ri)
    {
        std::stringstream ss;

        ss << "FPS : " << 1.f / info.deltaTime;
        m_text->SetText(ss.str());

        GetTransform()->SetPosition(
            Camera::ScreenToWorld(Vector(0.7f, 0.2f), ri));
    }
};

