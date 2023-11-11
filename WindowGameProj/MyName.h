#pragma once
#include "Actor.h"
#include "Text.h"

class MyName :
    public Actor
{
public:
    MyName(Vector pos) :Actor(pos)
    {
        AddComponent(new Text(this, "202113220_¼ÕÇüÁØ"));
    }

    virtual void Update(const UpdateInfo&, const RenderInfo& ri) override
    {
        GetTransform()->SetPosition(
            Camera::ScreenToWorld(Vector(0.7f, 30), ri));
    }
};

