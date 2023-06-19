#include "Collision.h"

#include <algorithm>
#include <math.h>

#include "MyMath.h"

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

bool IsCollision(const Triangle& triangle, const Segment& segment) {
	// 各辺を結んだベクトルと、頂点と衝突点pを結んだベクトルのクロス積をとる
	Vector3 v01 = triangle.vertices[1] - triangle.vertices[0];
	Vector3 v12 = triangle.vertices[2] - triangle.vertices[1];
	Vector3 v20 = triangle.vertices[0] - triangle.vertices[2];
	Vector3 normal = Cross(v01, v12);
	normal = Normalize(normal);

	// 垂直判定
	float d = Dot(normal, segment.diff);
	// 平行なら当たらない
	if (d == 0.0f) {
		return false;
	}
	float distance = Dot(triangle.vertices[0], normal);
	// 半直線と平面の当たり判定
	float t = (distance - Dot(segment.origin, normal)) / d;
	Vector3 intersectionPoint = segment.origin + (t * segment.diff);
	Vector3 v0p = intersectionPoint - triangle.vertices[0];
	Vector3 v1p = intersectionPoint - triangle.vertices[1];
	Vector3 v2p = intersectionPoint - triangle.vertices[2];

	Vector3 cross01 = Cross(v01, v1p);
	Vector3 cross12 = Cross(v12, v2p);
	Vector3 cross20 = Cross(v20, v0p);

	// 値確認
	float chackCross01 = Dot(cross01, normal);
	float chackCross12 = Dot(cross12, normal);
	float chackCross20 = Dot(cross20, normal);
	// 全ての小三角形のクロス積と法線が同じ方向を向いていたら衝突
	if (Dot(cross01, normal) >= 0.0f &&
		Dot(cross12, normal) >= 0.0f &&
		Dot(cross20, normal) >= 0.0f) {
		// 衝突
		return true;
	}
	return false;
}

bool IsCollision(const AABB& a, const AABB& b) {
	if (
		(a.min.x <= b.max.x && a.max.x >= b.min.x) && // x軸
		(a.min.y <= b.max.y && a.max.y >= b.min.y) && // y軸
		(a.min.z <= b.max.z && a.max.z >= b.min.z)    // z軸
		) {
		// 衝突
		return true;
	}
	return false;
}

bool IsCollision(const AABB& aabb, const Sphere& sphere) {
	// 最近接点を求める
	Vector3 clossPoint{
		std::clamp(sphere.center_.x,aabb.min.x,aabb.max.x),
		std::clamp(sphere.center_.y,aabb.min.y,aabb.max.y),
		std::clamp(sphere.center_.z,aabb.min.z,aabb.max.z),
	};
	// 最近接点と球の中心との距離を求める
	float distance = Length(clossPoint - sphere.center_);
	// 衝突が半径よりも小さければ衝突
	if (distance <= sphere.radius_) {
		// 衝突
		return true;
	}
	return false;
}
