#pragma once
#include "Line.h"
#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"
#include "AABB.h"
// 球と球
bool IsCollision(const Sphere& s1, const Sphere& s2);
// 球と平面
bool IsCollision(const Sphere& sphere, const Plane& plane);
// 線分と平面
bool IsCollision(const Plane& plane, const Segment& segment);
// 半直線と平面
bool IsCollision(const Plane& plane, const Ray& ray);
// 直線と平面
bool IsCollision(const Plane& plane, const Line& line);
// 三角形と線分
bool IsCollision(const Triangle& triangle, const Segment& segment);
// AABBとAABB
bool IsCollision(const AABB& a, const AABB& b);