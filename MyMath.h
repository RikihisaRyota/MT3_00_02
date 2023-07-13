#pragma once

#include <vector>

#include "AABB.h"
#include "mat4x4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Line.h"
#include "Vec2.h"
#include "Line.h"
#include "Plane.h"
#include "OBB.h"

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
// -オーバーロード
Vector3 operator* (const mat4x4& mat, const Vector3& v);
Vector3 operator- (const Vector3& v1);
Vector3 operator-(const Vector3& v, const Vector3& v2);
Vector3 operator*(float v, const Vector3& v2);
Vector2 operator*(float v, const Vector2& v2);
mat4x4 operator*(const mat4x4& ma1, const mat4x4& mat2);

//内積
Vector3 Subtract(const Vector3& v1, const Vector3& v2);

float Dot(const Vector3& a, const Vector3& b);

float Length(const Vector3& a);

float Dot(const Vec2& a, const Vec2& b);

float Length(const Vec2& a, const Vec2& b);

//外積
Vector3 Cross(const Vector3& v1, const Vector3& v2);

// 正射影ベクトル
Vector3 Project(const Vector3& v1, const Vector3& v2);

// 最近接点
Vector3 ClosestPoint(const Vector3& point, const Segment& segment);

Vector3 Perpendicular(const Vector3& vector);

Vector3 Normalize(const Vector3& vector);

// 平面と線分の当たった場所
bool Intersection(Vector3& intersection, const Plane& plane, const Segment& segment);

// AABBに値を代入
AABB AABBAssignment(const AABB& aabb);

// OBBの回転角度の抽出
OBB OBBSetRotate(const OBB& Obb, const Vector3& rotate);

// OBBの平行移動
mat4x4 OBBMakeWorldMatrix(const OBB& obb);

mat4x4 SetRotate(const Vector3(&array)[3]);

// OBBの頂点
void OBBIndex(const OBB& obb,std::vector<Vector3>& output_vertices);
// 分離軸
bool SeparationAxis(const Vector3 axis, const OBB obb_1, const OBB obb_2);

// 曲線
// 二次ベジエ
Vector2 QuadraticBezier(const Vector2& controlPoint0,const Vector2& controlPoint1,const Vector2& controlPoint2,float t);
// 三次ベジエ
Vector3 CubicBezier(const Vector3& controlPoint0,const Vector3& controlPoint1,const Vector3& controlPoint2,float t);
// Lerp
float Lerp(float start, float end, float t);
Vector2 Lerp(const Vector2& start, const Vector2& end, float t);
Vector3 Lerp(const Vector3& start, const Vector3& end, float t);
// Slarp
Vector2 Slerp(const Vector2& start, const Vector2& end, float t);
Vector3 Slerp(const Vector3& start, const Vector3& end, float t);
// CatmullRom
Vector2 QuadraticCatmullRom(const Vector2& Position0, const Vector2& Position1, const Vector2& Position2, const Vector2& Position3, float t);
Vector3 CubicCatmullRom(const Vector3& Position0, const Vector3& Position1, const Vector3& Position2, const Vector3& Position3, float t);

// 平行移動取得
Vector3 GetTranslates(const mat4x4 mat);