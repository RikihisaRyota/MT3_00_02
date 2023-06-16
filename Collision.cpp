#include "Collision.h"
#include "MyMath.h"
#include <math.h>

bool IsCollision(const Sphere& s1, const Sphere& s2) {
	// 2つの球の中心間の距離を求める
	float distance = Length(Subtract(s1.center_, s2.center_));
	if (distance <= s1.radius_ + s2.radius_) {
		return true;
	}
	return false;
}

bool IsCollision(const Sphere& sphere, const Plane& plane) {
	float k = Dot(plane.normal_, sphere.center_) - plane.distanse_;
	if (std::abs(k) <= sphere.radius_) {
		return true;
	}
	return false;
}

bool IsCollision(const Plane& plane, const Segment& segment) {
	// 垂直判定
	float d = Dot(plane.normal_, segment.diff);
	// 平行だったら
	if (d == 0.0f) {
		return false;
	}
	// 線分と平面の当たり判定
	float t = (plane.distanse_ - Dot(segment.origin, plane.normal_)) / d;
	if (t >= 0.0f && t <= 1.0f) {
		return true;
	}
	return false;
}

bool IsCollision(const Plane& plane, const Ray& ray) {
	// 垂直判定
	float d = Dot(plane.normal_, ray.diff);
	// 平行だったら
	if (d == 0.0f) {
		return false;
	}
	// 半直線と平面の当たり判定
	float t = (plane.distanse_ - Dot(ray.origin, plane.normal_)) / d;
	if (t >= 0.0f) {
		return true;
	}
	return false;
}

bool IsCollision(const Plane& plane, const Line& line) {
	// 垂直判定
	float d = Dot(plane.normal_, line.diff);
	// 直線
	if (d == 0.0f) {
		return false;
	}
	return true;
}
