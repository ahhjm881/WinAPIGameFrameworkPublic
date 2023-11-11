#pragma once
#include "Scene.h"
#include "CameraObserver.h"
#include "AABB.h"
#include "Debug.h"
#include "QuadTree.h"
#include "AStar.h"
#include "FPSDraw.h"
#include "MyName.h"


//#define DEBUG_DRAW_RECT

using namespace CKMath;

class TestScene :
    public Scene
{
private:
    QuadTree tree;
    std::vector<AABBCollider*> vv;

public:
    TestScene() : Scene(0, IVector(0, 0)), tree()
    {
        AddActor(new FPSDraw({ 800, 470 }));
        AddActor(new MyName({ 800, 450 }));

        Matrix4x4 a = Matrix4x4
        {
            1, 0, 0, 12,
            0, 1, 0, 32,
            0, 0, 1, 0,
            0, 0, 0, 1
        };

        //Matrix3x1 v = Matrix3x1{ 0, 0, 1};
        Matrix4x1 v = Matrix4x1{ 0, 0, 0, 1};

        auto r = a * v;

        Debug::Log(r);
    }

    virtual ~TestScene()
    {
    }


    virtual void Update(const UpdateInfo& info, const RenderInfo& ri)
    {
#ifdef DEBUG_DRAW_RECT
        auto v = tree.GetGraph();
        for (auto i = v.begin(); i != v.end(); i++)
        {
            (*i)->DebugDraw(ri);
        }
#endif
    }
};

