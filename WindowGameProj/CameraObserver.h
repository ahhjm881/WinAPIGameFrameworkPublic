#pragma once
#include "Actor.h"
#include "Camera.h"
#include "Input.h"

class CameraObserver :
    public Actor
{
private:
    Transform* m_camera;
    Transform* m_target;
    float m_speed;

public:
    CameraObserver(Transform* target, Vector pos, float speed = 10) : Actor(pos), m_target(target), m_camera(nullptr), m_speed(speed)
    {
        m_camera = Camera::GetTransform();
    }

    virtual ~CameraObserver()
    {

    }

    virtual void Update(const UpdateInfo& ui, const RenderInfo&)
    {
        Vector v = Vector::zero;

        if (Input::GetKey('D') || Input::GetKey('d'))
            v.x += m_speed;
        if (Input::GetKey('A') || Input::GetKey('a'))
            v.x -= m_speed;
        if (Input::GetKey('S') || Input::GetKey('s'))
            v.y -= m_speed;
        if (Input::GetKey('W') || Input::GetKey('w'))
            v.y += m_speed;

        auto r = v * ui.deltaTime;
        m_camera->Move(r);

        if (Input::GetKeyDown('F') || Input::GetKeyDown('f'))
        {
            m_camera->SetPosition(Vector::zero);
        }

        if (m_target == nullptr) return;


    }
};

