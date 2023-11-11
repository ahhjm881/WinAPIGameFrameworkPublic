#pragma once
#include "Component.h"
#include <string>
#include "Actor.h"

class Text :
    public Component
{
private:
    std::string m_str;
    Vector m_offset;

public:
    Text(Actor* actor);
    Text(Actor* actor, std::string);
    virtual ~Text();

    virtual void Update(const UpdateInfo&);
    virtual void Render(const RenderInfo&);

    void SetText(std::string str);
    void SetOffset(const Vector& offset);
};

