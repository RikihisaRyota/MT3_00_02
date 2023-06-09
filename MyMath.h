#pragma once
#include "mat4x4.h"
#include "Vector3.h"
#include "Line.h"
#include "Vec2.h"

//1,行列の加法
mat4x4 Add(const mat4x4& m1, const mat4x4& m2);
//2,行列の減算
mat4x4 Sub(const mat4x4& m1, const mat4x4& m2);
//3,行列の積
mat4x4 Mul(const mat4x4& m1, const mat4x4& m2);
//3,行列の積(スカラー倍)
mat4x4 Mul(const float scaler, const mat4x4& m2);
//4,逆行列
mat4x4 Inverse(const mat4x4& m);
//5,転置行列
mat4x4 Transpose(const mat4x4& m);
//6,単位行列
mat4x4 MakeIdentity4x4();

//1,平行移動行列
mat4x4 MakeTranslateMatrix(const Vector3& translate);
//2,拡大縮小行列
mat4x4 MakeScaleMatrix(const Vector3& scale);
//3,座標変換
Vector3 Transform(const Vector3& vector, const mat4x4& matrix);

//1,X軸回転行列
mat4x4 MakeRotateXMatrix(float radian);
//2,Y軸回転行列
mat4x4 MakeRotateYMatrix(float radian);
//3,Z軸回転行列
mat4x4 MakeRotateZMatrix(float radian);

//3次元アフィン変換
mat4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

//1,透視投影行列
mat4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);
//2,正射影行列
mat4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);
//3,ビューポート変換行列
mat4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

//matrix4x4*Vector3
Vector3 operator* (const mat4x4& mat, const Vector3& v);

//内積
Vector3 Subtract(const Vector3& v1, const Vector3& v2);

float Dot(const Vector3& a, const Vector3& b);

float Length(const Vector3& a);

float Dot(const Vec2& a, const Vec2& b);

float Length(const Vec2& a, const Vec2& b);

//外積
Vector3 Cross(const Vector3& v1, const Vector3& v2);

//-オーバーロード
Vector3 operator-(const Vector3& v, const Vector3& v2);

//-オーバーロード
Vector3 operator*(const Vector3& v, const Vector3& v2);

//-オーバーロード
Vector3 operator*(float v, const Vector3& v2);

// 正射影ベクトル
Vector3 Project(const Vector3& v1, const Vector3& v2);

// 最近接点
Vector3 ClosestPoint(const Vector3& point, const Segment& segment);

Vector3 Perpendicular(const Vector3& vector);

Vector3 Normalize(const Vector3& vector);