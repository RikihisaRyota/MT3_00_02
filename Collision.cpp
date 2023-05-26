#include "Collision.h"
#include "MyMath.h"
#include <math.h>

bool IsCollision(const Sphere& s1, const Sphere& s2)
{
	// 2つの球の中心間の距離を求める
	float distance = Length(Subtract(s1.center_,s2.center_));
	if (distance <= s1.radius_ + s2.radius_) {
		return true;
	}
	return false;
}
