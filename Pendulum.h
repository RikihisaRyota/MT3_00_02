#pragma once

#include "Vector3.h"

struct Pendulum {
	Vector3 anchor; // アンカーポイント
	float length; // 紐の長さ
	float angle; // 現在の角度
	float angularVelocity; // 各速度ω
	float angularAcceleration; // 角加速度
};