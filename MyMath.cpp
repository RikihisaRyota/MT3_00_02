#include "MyMath.h"

mat4x4 Add(const mat4x4& m1, const mat4x4& m2)
{
	mat4x4 mat;
	mat.m[0][0] = m1.m[0][0] + m2.m[0][0], mat.m[0][1] = m1.m[0][1] + m2.m[0][1], mat.m[0][2] = m1.m[0][2] + m2.m[0][2], mat.m[0][3] = m1.m[0][3] + m2.m[0][3];
	mat.m[1][0] = m1.m[1][0] + m2.m[1][0], mat.m[1][1] = m1.m[1][1] + m2.m[1][1], mat.m[1][2] = m1.m[1][2] + m2.m[1][2], mat.m[1][3] = m1.m[1][3] + m2.m[1][3];
	mat.m[2][0] = m1.m[2][0] + m2.m[2][0], mat.m[2][1] = m1.m[2][1] + m2.m[2][1], mat.m[2][2] = m1.m[2][2] + m2.m[2][2], mat.m[2][3] = m1.m[2][3] + m2.m[2][3];
	mat.m[3][0] = m1.m[3][0] + m2.m[3][0], mat.m[3][1] = m1.m[3][1] + m2.m[3][1], mat.m[3][2] = m1.m[3][2] + m2.m[3][2], mat.m[3][3] = m1.m[3][3] + m2.m[3][3];
	return mat;
}

mat4x4 Sub(const mat4x4& m1, const mat4x4& m2)
{
	mat4x4 mat;
	mat.m[0][0] = m1.m[0][0] - m2.m[0][0], mat.m[0][1] = m1.m[0][1] - m2.m[0][1], mat.m[0][2] = m1.m[0][2] - m2.m[0][2], mat.m[0][3] = m1.m[0][3] - m2.m[0][3];
	mat.m[1][0] = m1.m[1][0] - m2.m[1][0], mat.m[1][1] = m1.m[1][1] - m2.m[1][1], mat.m[1][2] = m1.m[1][2] - m2.m[1][2], mat.m[1][3] = m1.m[1][3] - m2.m[1][3];
	mat.m[2][0] = m1.m[2][0] - m2.m[2][0], mat.m[2][1] = m1.m[2][1] - m2.m[2][1], mat.m[2][2] = m1.m[2][2] - m2.m[2][2], mat.m[2][3] = m1.m[2][3] - m2.m[2][3];
	mat.m[3][0] = m1.m[3][0] - m2.m[3][0], mat.m[3][1] = m1.m[3][1] - m2.m[3][1], mat.m[3][2] = m1.m[3][2] - m2.m[3][2], mat.m[3][3] = m1.m[3][3] - m2.m[3][3];
	return mat;
}

mat4x4 Mul(const mat4x4& m1, const mat4x4& m2)
{
	mat4x4 mat;
	mat.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0],
		mat.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1],
		mat.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2],
		mat.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3],

		mat.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0],
		mat.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1],
		mat.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2],
		mat.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3],

		mat.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0],
		mat.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1],
		mat.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2],
		mat.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3],

		mat.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0],
		mat.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1],
		mat.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2],
		mat.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3];

	return mat;
}

mat4x4 Mul(const float scaler, const mat4x4& m2)
{
	mat4x4 mat;
	mat.m[0][0] = scaler * m2.m[0][0], mat.m[0][1] = scaler * m2.m[0][1], mat.m[0][2] = scaler * m2.m[0][2], mat.m[0][3] = scaler * m2.m[0][3];
	mat.m[1][0] = scaler * m2.m[1][0], mat.m[1][1] = scaler * m2.m[1][1], mat.m[1][2] = scaler * m2.m[1][2], mat.m[1][3] = scaler * m2.m[1][3];
	mat.m[2][0] = scaler * m2.m[2][0], mat.m[2][1] = scaler * m2.m[2][1], mat.m[2][2] = scaler * m2.m[2][2], mat.m[2][3] = scaler * m2.m[2][3];
	mat.m[3][0] = scaler * m2.m[3][0], mat.m[3][1] = scaler * m2.m[3][1], mat.m[3][2] = scaler * m2.m[3][2], mat.m[3][3] = scaler * m2.m[3][3];
	return mat;
}

mat4x4 Inverse(const mat4x4& m)
{
	float A;
	A = m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]
		- m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1] - m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]
		- m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]
		+ m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1] + m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]
		+ m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]
		- m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1] - m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]
		- m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]
		+ m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0] + m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0];

	mat4x4 tmp;
	tmp.m[0][0] = 1.0f / A * (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[1][3] * m.m[2][1] * m.m[3][2]
		- m.m[1][3] * m.m[2][2] * m.m[3][1] - m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2]);

	tmp.m[0][1] = 1.0f / A * (-m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[2][1] * m.m[3][2]
		+ m.m[0][3] * m.m[2][2] * m.m[3][1] + m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2]);

	tmp.m[0][2] = 1.0f / A * (m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[3][2]
		- m.m[0][3] * m.m[1][2] * m.m[3][1] - m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2]);

	tmp.m[0][3] = 1.0f / A * (-m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] - m.m[0][3] * m.m[1][1] * m.m[2][2]
		+ m.m[0][3] * m.m[1][2] * m.m[2][1] + m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2]);


	tmp.m[1][0] = 1.0f / A * (-m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[1][3] * m.m[2][0] * m.m[3][2]
		+ m.m[1][3] * m.m[2][2] * m.m[3][0] + m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2]);

	tmp.m[1][1] = 1.0f / A * (m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] + m.m[0][3] * m.m[2][0] * m.m[3][2]
		- m.m[0][3] * m.m[2][2] * m.m[3][0] - m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][2]);

	tmp.m[1][2] = 1.0f / A * (-m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] - m.m[0][3] * m.m[1][0] * m.m[3][2]
		+ m.m[0][3] * m.m[1][2] * m.m[3][0] + m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2]);

	tmp.m[1][3] = 1.0f / A * (m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] + m.m[0][3] * m.m[1][0] * m.m[2][2]
		- m.m[0][3] * m.m[1][2] * m.m[2][0] - m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][2]);


	tmp.m[2][0] = 1.0f / A * (m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[1][3] * m.m[2][0] * m.m[3][1]
		- m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1]);

	tmp.m[2][1] = 1.0f / A * (-m.m[0][0] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][0] - m.m[0][3] * m.m[2][0] * m.m[3][1]
		+ m.m[0][3] * m.m[2][1] * m.m[3][0] + m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1]);

	tmp.m[2][2] = 1.0f / A * (m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] + m.m[0][3] * m.m[1][0] * m.m[3][1]
		- m.m[0][3] * m.m[1][1] * m.m[3][0] - m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1]);

	tmp.m[2][3] = 1.0f / A * (-m.m[0][0] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] - m.m[0][3] * m.m[1][0] * m.m[2][1]
		+ m.m[0][3] * m.m[1][1] * m.m[2][0] + m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1]);


	tmp.m[3][0] = 1.0f / A * (-m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][2] * m.m[3][0] - m.m[1][2] * m.m[2][0] * m.m[3][1]
		+ m.m[1][2] * m.m[2][1] * m.m[3][0] + m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1]);

	tmp.m[3][1] = 1.0f / A * (m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] + m.m[0][2] * m.m[2][0] * m.m[3][1]
		- m.m[0][2] * m.m[2][1] * m.m[3][0] - m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1]);

	tmp.m[3][2] = 1.0f / A * (-m.m[0][0] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[3][0] - m.m[0][2] * m.m[1][0] * m.m[3][1]
		+ m.m[0][2] * m.m[1][1] * m.m[3][0] + m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][0] * m.m[1][2] * m.m[3][1]);

	tmp.m[3][3] = 1.0f / A * (m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] + m.m[0][2] * m.m[1][0] * m.m[2][1]
		- m.m[0][2] * m.m[1][1] * m.m[2][0] - m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1]);

	return tmp;
}

mat4x4 Transpose(const mat4x4& m)
{
	mat4x4 mat;
	mat.m[0][0] = m.m[0][0], mat.m[0][1] = m.m[1][0], mat.m[0][2] = m.m[2][0], mat.m[0][3] = m.m[3][0];
	mat.m[1][0] = m.m[0][1], mat.m[1][1] = m.m[1][1], mat.m[1][2] = m.m[2][1], mat.m[1][3] = m.m[3][1];
	mat.m[2][0] = m.m[0][2], mat.m[2][1] = m.m[1][2], mat.m[2][2] = m.m[2][2], mat.m[2][3] = m.m[3][2];
	mat.m[3][0] = m.m[0][3], mat.m[3][1] = m.m[1][3], mat.m[3][2] = m.m[2][3], mat.m[3][3] = m.m[3][3];
	return mat;
}

mat4x4 MakeIdentity4x4()
{
	mat4x4 mat;
	mat.m[0][0] = 1.0f, mat.m[0][1] = 0.0f, mat.m[0][2] = 0.0f, mat.m[0][3] = 0.0f;
	mat.m[1][0] = 0.0f, mat.m[1][1] = 1.0f, mat.m[1][2] = 0.0f, mat.m[1][3] = 0.0f;
	mat.m[2][0] = 0.0f, mat.m[2][1] = 0.0f, mat.m[2][2] = 1.0f, mat.m[2][3] = 0.0f;
	mat.m[3][0] = 0.0f, mat.m[3][1] = 0.0f, mat.m[3][2] = 0.0f, mat.m[3][3] = 1.0f;
	return mat;
}

mat4x4 MakeTranslateMatrix(const Vector3& translate)
{
	mat4x4 tmp;
	tmp.m[0][0] = 1.0f, tmp.m[0][1] = 0.0f, tmp.m[0][2] = 0.0f, tmp.m[0][3] = 0.0f;
	tmp.m[1][0] = 0.0f, tmp.m[1][1] = 1.0f, tmp.m[1][2] = 0.0f, tmp.m[1][3] = 0.0f;
	tmp.m[2][0] = 0.0f, tmp.m[2][1] = 0.0f, tmp.m[2][2] = 1.0f, tmp.m[2][3] = 0.0f;
	tmp.m[3][0] = translate.x, tmp.m[3][1] = translate.y, tmp.m[3][2] = translate.z, tmp.m[3][3] = 1.0f;
	return tmp;
}

mat4x4 MakeScaleMatrix(const Vector3& scale)
{
	mat4x4 tmp;
	tmp.m[0][0] = scale.x, tmp.m[0][1] = 0.0f, tmp.m[0][2] = 0.0f, tmp.m[0][3] = 0.0f;
	tmp.m[1][0] = 0.0f, tmp.m[1][1] = scale.y, tmp.m[1][2] = 0.0f, tmp.m[1][3] = 0.0f;
	tmp.m[2][0] = 0.0f, tmp.m[2][1] = 0.0f, tmp.m[2][2] = scale.z, tmp.m[2][3] = 0.0f;
	tmp.m[3][0] = 0.0f, tmp.m[3][1] = 0.0f, tmp.m[3][2] = 0.0f, tmp.m[3][3] = 1.0f;
	return tmp;
}

Vector3 Transform(const Vector3& vector, const mat4x4& matrix)
{
	Vector3 result{ 0.0f,0.0f,0.0f };
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];

	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;

}

mat4x4 MakeRotateXMatrix(float radian)
{
	mat4x4 mat;
	mat.m[0][0] = 1.0f, mat.m[0][1] = 0.0f, mat.m[0][2] = 0.0f, mat.m[0][3] = 0.0f;
	mat.m[1][0] = 0.0f, mat.m[1][1] = std::cos(radian), mat.m[1][2] = std::sin(radian), mat.m[1][3] = 0.0f;
	mat.m[2][0] = 0.0f, mat.m[2][1] = -std::sin(radian), mat.m[2][2] = std::cos(radian), mat.m[2][3] = 0.0f;
	mat.m[3][0] = 0.0f, mat.m[3][1] = 0.0f, mat.m[3][2] = 0.0f, mat.m[3][3] = 1.0f;
	return mat;
}

mat4x4 MakeRotateYMatrix(float radian)
{
	mat4x4 mat;
	mat.m[0][0] = std::cos(radian), mat.m[0][1] = 0.0f, mat.m[0][2] = -std::sin(radian), mat.m[0][3] = 0.0f;
	mat.m[1][0] = 0.0f, mat.m[1][1] = 1.0f, mat.m[1][2] = 0.0f, mat.m[1][3] = 0.0f;
	mat.m[2][0] = std::sin(radian), mat.m[2][1] = 0.0f, mat.m[2][2] = std::cos(radian), mat.m[2][3] = 0.0f;
	mat.m[3][0] = 0.0f, mat.m[3][1] = 0.0f, mat.m[3][2] = 0.0f, mat.m[3][3] = 1.0f;
	return mat;
}

mat4x4 MakeRotateZMatrix(float radian)
{
	mat4x4 mat;
	mat.m[0][0] = std::cos(radian), mat.m[0][1] = std::sin(radian), mat.m[0][2] = 0.0f, mat.m[0][3] = 0.0f;
	mat.m[1][0] = -std::sin(radian), mat.m[1][1] = std::cos(radian), mat.m[1][2] = 0.0f, mat.m[1][3] = 0.0f;
	mat.m[2][0] = 0.0f, mat.m[2][1] = 0.0f, mat.m[2][2] = 1.0f, mat.m[2][3] = 0.0f;
	mat.m[3][0] = 0.0f, mat.m[3][1] = 0.0f, mat.m[3][2] = 0.0f, mat.m[3][3] = 1.0f;
	return mat;
}

mat4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate)
{
	mat4x4 tmp = Mul(MakeRotateXMatrix(rotate.x), Mul(MakeRotateYMatrix(rotate.y), MakeRotateZMatrix(rotate.z)));

	mat4x4 mat;
	mat.m[0][0] = scale.x * tmp.m[0][0], mat.m[0][1] = scale.x * tmp.m[0][1], mat.m[0][2] = scale.x * tmp.m[0][2], mat.m[0][3] = 0.0f;
	mat.m[1][0] = scale.y * tmp.m[1][0], mat.m[1][1] = scale.y * tmp.m[1][1], mat.m[1][2] = scale.y * tmp.m[1][2], mat.m[1][3] = 0.0f;
	mat.m[2][0] = scale.z * tmp.m[2][0], mat.m[2][1] = scale.z * tmp.m[2][1], mat.m[2][2] = scale.z * tmp.m[2][2], mat.m[2][3] = 0.0f;
	mat.m[3][0] = translate.x, mat.m[3][1] = translate.y, mat.m[3][2] = translate.z, mat.m[3][3] = 1.0f;
	return mat;
}

mat4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip)
{
	mat4x4 mat;
	mat.m[0][0] = (1.0f / aspectRatio) * (1.0f / std::tan(fovY / 2.0f)), mat.m[0][1] = 0.0f, mat.m[0][2] = 0.0f, mat.m[0][3] = 0.0f;
	mat.m[1][0] = 0.0f, mat.m[1][1] = 1.0f / std::tan(fovY / 2.0f), mat.m[1][2] = 0.0f, mat.m[1][3] = 0.0f;
	mat.m[2][0] = 0.0f, mat.m[2][1] = 0.0f, mat.m[2][2] = farClip / (farClip - nearClip), mat.m[2][3] = 1.0f;
	mat.m[3][0] = 0.0f, mat.m[3][1] = 0.0f, mat.m[3][2] = (-nearClip * farClip) / (farClip - nearClip), mat.m[3][3] = 0.0f;
	return mat;
}

mat4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip)
{
	mat4x4 mat;
	mat.m[0][0] = 2.0f / (right - left), mat.m[0][1] = 0.0f, mat.m[0][2] = 0.0f, mat.m[0][3] = 0.0f;
	mat.m[1][0] = 0.0f, mat.m[1][1] = 2.0f / (top - bottom), mat.m[1][2] = 0.0f, mat.m[1][3] = 0.0f;
	mat.m[2][0] = 0.0f, mat.m[2][1] = 0.0f, mat.m[2][2] = 1.0f / (farClip - nearClip), mat.m[2][3] = 0.0f;
	mat.m[3][0] = (left + right) / (left - right), mat.m[3][1] = (top + bottom) / (bottom - top), mat.m[3][2] = nearClip / (nearClip - farClip), mat.m[3][3] = 1.0f;
	return mat;
}

mat4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth)
{
	mat4x4 mat;
	mat.m[0][0] = width / 2.0f, mat.m[0][1] = 0.0f, mat.m[0][2] = 0.0f, mat.m[0][3] = 0.0f;
	mat.m[1][0] = 0.0f, mat.m[1][1] = -height / 2.0f, mat.m[1][2] = 0.0f, mat.m[1][3] = 0.0f;
	mat.m[2][0] = 0.0f, mat.m[2][1] = 0.0f, mat.m[2][2] = maxDepth - minDepth, mat.m[2][3] = 0.0f;
	mat.m[3][0] = left + (width / 2.0f), mat.m[3][1] = top + (height / 2.0f), mat.m[3][2] = minDepth, mat.m[3][3] = 1.0f;
	return mat;
}

Vector3 operator*(const mat4x4& matrix, const Vector3& vector)
{
	Vector3 result{ 0.0f,0.0f,0.0f };
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];

	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
}

Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	return { (v1.x - v2.x), (v1.y - v2.y), (v1.z - v2.z) };
}

float Dot(const Vector3& a, const Vector3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

float Length(const Vector3& a)
{
	return sqrtf( (a.x * a.x)+ (a.y * a.y)+ (a.z * a.z) );
}


float Dot(const Vec2& a, const Vec2& b) { return a.x * b.x + a.y * b.y; }

float Length(const Vec2& a, const Vec2& b)
{
	return sqrtf(Dot(a,b));
}

Vector3 Cross(const Vector3& a, const Vector3& b) {
	return { a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x };
}

Vector3 operator-(const Vector3& v, const Vector3& v2) {
	Vector3 tmp(0.0f, 0.0f, 0.0f);
	tmp.x = v.x - v2.x;
	tmp.y = v.y - v2.y;
	tmp.z = v.z - v2.z;
	return tmp;
}

Vector3 operator*(const Vector3& v, const Vector3& v2) {
	Vector3 tmp(0.0f, 0.0f, 0.0f);
	tmp.x = v.x * v2.x;
	tmp.y = v.y * v2.y;
	tmp.z = v.z * v2.z;
	return tmp;
}

Vector3 operator*(float v, const Vector3& v2)
{
	return Vector3(v2.x * v, v2.y * v, v2.z * v);
}

Vector3 Project(const Vector3& v1, const Vector3& V2)
{
	Vector3 tmp;
	Vector3 v2 = V2;
	v2.Normalize();
	tmp = Dot(v1, v2) * v2;
	return tmp;
}

Vector3 ClosestPoint(const Vector3& point, const Segment& segment)
{
	Vector3 proj = Project(point - segment.origin, segment.diff);
	return segment.origin + proj;
}

Vector3 Perpendicular(const Vector3& vector) {
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return { -vector.y,vector.x,0.0f };
	}
	return { 0.0f ,-vector.z,vector.y};
}

Vector3 Normalize(const Vector3& vector)
{
	Vector3 tmp = vector;
	float length = Length(tmp);
	assert(length != 0.0f);
	tmp.x/= length;
	tmp.y /= length;
	tmp.z /= length;
	return tmp;
}

bool Intersection(Vector3& intersection,const Vector3& normal, const Segment& segment) {
	// 垂直判定
	float d = Dot(normal, segment.diff);
	// 平行だったら
	if (d == 0.0f) {
		return false;
	}
	// 線分と平面の当たり判定
	//float t = (plane.distanse_ - Dot(segment.origin,normal)) / d;
	// 線分と平面の当たったポイント
	intersection = segment.origin + d * segment.diff;
	return true;
}

AABB AABBAssignment(const AABB& aabb) {
	AABB result = aabb;
	// x
	result.min.x = (std::min)(result.min.x, result.max.x);
	result.max.x = (std::max)(result.min.x, result.max.x);
	// y
	result.min.y = (std::min)(result.min.y, result.max.y);
	result.max.y = (std::max)(result.min.y, result.max.y);
	// z
	result.min.z = (std::min)(result.min.z, result.max.z);
	result.max.z = (std::max)(result.min.z, result.max.z);

	return result;
}
