#pragma once
#include "Sphere.h"
#include "Plane.h"

bool IsCollision(const Sphere& s1, const Sphere& s2);

bool IsCollision(const Sphere& sphere, const Plane& plane);