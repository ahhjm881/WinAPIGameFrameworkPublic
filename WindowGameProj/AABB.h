#pragma once

#include "type.h"

namespace
{
    using namespace CKMath;
    using Point = Vector;
    using Value_type = Vector::Type;

    typedef struct Line {
        Point p1;
        Point p2;
    }Line;

    Value_type ccw(const Point& p1, const Point& p2, const Point& p3) {
        Value_type cross_product = (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);

        if (cross_product > 0) {
            return (Value_type)1;
        }
        else if (cross_product < 0) {
            return (Value_type)-1;
        }
        else {
            return (Value_type)0;
        }
    }
    bool comparator(Point left, Point right) {
        int ret;
        if (left.x == right.x) {
            ret = (left.y <= right.y);
        }
        else {
            ret = (left.x <= right.x);
        }
        return ret;
    }

    void swap(Point* p1, Point* p2) {
        Point temp;
        temp = *p1;
        *p1 = *p2;
        *p2 = temp;
    }

    int _LineIntersection(Line l1, Line l2) {
        int ret;
        Value_type l1_l2 = ccw(l1.p1, l1.p2, l2.p1) * ccw(l1.p1, l1.p2, l2.p2);
        Value_type l2_l1 = ccw(l2.p1, l2.p2, l1.p1) * ccw(l2.p1, l2.p2, l1.p2);


        if (l1_l2 == 0 && l2_l1 == 0) {
            if (comparator(l1.p2, l1.p1)) swap(&l1.p1, &l1.p2);
            if (comparator(l2.p2, l2.p1)) swap(&l2.p1, &l2.p2);

            ret = (comparator(l2.p1, l1.p2)) && (comparator(l1.p1, l2.p2));
        }
        else {
            ret = (l1_l2 <= 0) && (l2_l1 <= 0);
        }
        return ret;
    }

    bool LineIntersection(const Point& p1, const Point& p2, const Point& p3, const Point& p4)
    {
        return _LineIntersection(Line{ p1, p2 }, Line{ p3, p4 });
    }

}

class AABB
{
private:
	Vector m_pos;
	Vector m_size;

public:
	AABB() {}
	AABB(Vector pos, Vector size) : m_pos(pos), m_size(size) {}

	static bool Collision(Vector ap, Vector as, Vector bp, Vector bs)
	{
		Vector ah = as * 0.5f;
		Vector bh = bs * 0.5f;

		if (ap.x + ah.x < bp.x - bh.x || ap.x - ah.x > bp.x + bh.x) return 0;
		if (ap.y + ah.y < bp.y - bh.y || ap.y - ah.y > bp.y + bh.y) return 0;

		return 1;
	}

	static bool Collision(AABB a, AABB b)
	{
		return Collision(a.m_pos, a.m_size, b.m_pos, b.m_size);
	}

	static bool CollisionRay(Vector ap, Vector as, Vector origin, Vector dir)
	{
        as *= 0.5f;
		Vector p1 = ap + Vector(-as.x, as.y);
		Vector p2 = ap + Vector(as.x, as.y) ;
		Vector p3 = ap + Vector(-as.x, -as.y);
		Vector p4 = ap + Vector(as.x, -as.y);

		return 
            LineIntersection(p1, p2, origin, origin + dir) ||
            LineIntersection(p2, p4, origin, origin + dir) ||
            LineIntersection(p4, p3, origin, origin + dir) ||
            LineIntersection(p3, p1, origin, origin + dir)
			;
	}
	static bool CollisionRay(AABB a, const Vector& origin, const Vector& dir)
	{
		return CollisionRay(a.GetPos(), a.GetSize(), origin, dir);
	}

public:
	Vector GetPos() const { return m_pos; }
	Vector GetSize() const { return m_size; }
	void SetPos(Vector pos) { m_pos = pos; }
	void SetSize(Vector size) { m_size = size; }
};

