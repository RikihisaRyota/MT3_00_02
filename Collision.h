#pragma once
#include "Line.h"
#include "Plane.h"
#include "Sphere.h"

bool IsCollision(const Sphere& s1, const Sphere& s2);

bool IsCollision(const Sphere& sphere, const Plane& plane);

// 線分
bool IsCollision(const Plane& plane, const Segment& segment);
// 半直線
bool IsCollision(const Plane& plane, const Ray& ray);
// 直線
bool IsCollision(const Plane& plane, const Line& line);