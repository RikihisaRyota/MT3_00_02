#pragma once
#include "Vector3.h"
class mat4x4
{
public:
	float m[4][4];
public:

	mat4x4();
	mat4x4(
		float _11, float _12, float _13, float _14,
		float _21, float _22, float _23, float _24,
		float _31, float _32, float _33, float _34,
		float _41, float _42, float _43, float _44
	) {
		m[0][0] = _11, m[0][1] = _12, m[0][2] = _13, m[0][3] = _14;
		m[1][0] = _21, m[1][1] = _22, m[1][2] = _23, m[1][3] = _24;
		m[2][0] = _31, m[2][1] = _32, m[2][2] = _33, m[2][3] = _34;
		m[3][0] = _41, m[3][1] = _42, m[3][2] = _43, m[3][3] = _44;
	}
};

//1,�s��̉��@
mat4x4 Add(const mat4x4& m1, const mat4x4& m2);
//2,�s��̌��Z
mat4x4 Sub(const mat4x4& m1, const mat4x4& m2);
//3,�s��̐�
mat4x4 Mul(const mat4x4& m1, const mat4x4& m2);
//3,�s��̐�(�X�J���[�{)
mat4x4 Mul(const float scaler, const mat4x4& m2);
//4,�t�s��
mat4x4 Inverse(const mat4x4& m);
//5,�]�u�s��
mat4x4 Transpose(const mat4x4& m);
//6,�P�ʍs��
mat4x4 MakeIdentity4x4();

//1,���s�ړ��s��
mat4x4 MakeTranslateMatrix(const Vector3& translate);
//2,�g��k���s��
mat4x4 MakeScaleMatrix(const Vector3& scale);
//3,���W�ϊ�
Vector3 Transform(const Vector3& vector, const mat4x4& matrix);