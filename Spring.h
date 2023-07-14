#pragma once

#include "Vector3.h"

struct Spring {
	// アンカー。固定された端の位置
	Vector3 anchor_;
	float natureLength_; //!< 自然長
	float stiffness_; //!< 剛性。ばね定数k
	float dampingCoefficient_; //!< 減衰係数
};