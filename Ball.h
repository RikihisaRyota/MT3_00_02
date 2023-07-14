#pragma once

#include "Vector3.h"

struct Ball {
	Vector3 position_; //!< ボールの位置
	Vector3 velocity_; //!< ボールの速度
	Vector3 acceleration_; //<! ボールの加速度
	float mass_; //!< ボールの質量
	float radius_; //!< ボールの半径
	uint32_t color_; //!< ボールの色
};