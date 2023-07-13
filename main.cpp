#include <Novice.h>
#include <cstdint>
#include "imgui.h"
#include "mat4x4.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Plane.h"
#include "OBB.h"
#include "MyMath.h"
#include "Collision.h"

#define _USE_MATH_DEFINES
#include <Math.h> 
const char kWindowTitle[] = "学籍番号";

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

static const int kWindowWidth = 1280;
static const int kWindowHeight = 720;

void MatrixScreenPrintf(int x, int y, const mat4x4& mat, const char* label) {
	Novice::ScreenPrintf(x, y, "%s", label);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight + kRowHeight, "%6.02f", mat.m[row][column]);
		}
	}

}

void VectorScreenPrintf(int x, int y, const Vector3& vec, const char* label) {
	Novice::ScreenPrintf(x * kColumnWidth, y, "%6.02f", vec.x);
	Novice::ScreenPrintf((x + 1) * kColumnWidth, y, "%6.02f", vec.y);
	Novice::ScreenPrintf((x + 2) * kColumnWidth, y, "%6.02f", vec.z);
	Novice::ScreenPrintf((x + 3) * kColumnWidth, y, "%s", label);
}

void DrawLine(const Vector3& v1, const Vector3& v2, const mat4x4& viewProjectionMatrix, const mat4x4& viewportMatrix, int32_t color) {

	Vector3 ndcVertex_Start = Transform(v1, viewProjectionMatrix);
	Vector3 screenVertices_Start = Transform(ndcVertex_Start, viewportMatrix);

	Vector3 ndcVertex_End = Transform(v2, viewProjectionMatrix);
	Vector3 screenVertices_End = Transform(ndcVertex_End, viewportMatrix);

	Novice::DrawLine(static_cast<int>(screenVertices_Start.x), static_cast<int>(screenVertices_Start.y), static_cast<int>(screenVertices_End.x), static_cast<int>(screenVertices_End.y), color);
}

void DrawLine(const Vector3& v1, const Vector3& v2, uint32_t color) {
	Novice::DrawLine(static_cast<int>(v1.x), static_cast<int>(v1.y), static_cast<int>(v2.x), static_cast<int>(v2.y), color);
}

void DrawGrid(const mat4x4& viewProjectionMatrix, const mat4x4& viewportMatrix) {
	const float kGridHalfWidth = 2.0f;//Gridの半分の幅
	const uint32_t kSubdivision = 10;//分割数
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);//一つ分の長さ
	//奥から手前への線を順々に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		//グリットのスケール
		Vector3 scale(1.0f, 1.0f, 1.0f);
		//グリットの回転
		Vector3 rotate(0.0f, 0.0f, 0.0f);
		//始点をずらす
		int i = xIndex - kSubdivision / 2;

		Vector3 position_Start(-kGridHalfWidth, 0.0f, static_cast<float>(kGridEvery * i));
		Vector3 position_End(kGridHalfWidth, 0.0f, static_cast<float>(kGridEvery * i));

		Vector3 ndcVertex_Start = Transform(position_Start, viewProjectionMatrix);
		Vector3 screenVertices_Start = Transform(ndcVertex_Start, viewportMatrix);

		Vector3 ndcVertex_End = Transform(position_End, viewProjectionMatrix);
		Vector3 screenVertices_End = Transform(ndcVertex_End, viewportMatrix);

		if (xIndex == kSubdivision / 2) {
			Novice::DrawLine(static_cast<int>(screenVertices_Start.x), static_cast<int>(screenVertices_Start.y), static_cast<int>(screenVertices_End.x), static_cast<int>(screenVertices_End.y), 0x000000FF);
		}
		else {
			Novice::DrawLine(static_cast<int>(screenVertices_Start.x), static_cast<int>(screenVertices_Start.y), static_cast<int>(screenVertices_End.x), static_cast<int>(screenVertices_End.y), 0xAAAAAAFF);
		}

	}
	//左から右
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		Vector3 scale(1.0f, 1.0f, 1.0f);
		Vector3 rotate(0.0f, 0.0f, 0.0f);
		int i = zIndex - kSubdivision / 2;
		Vector3 position_Start(static_cast<float>(kGridEvery * i), 0.0f, -kGridHalfWidth);
		Vector3 position_End(static_cast<float>(kGridEvery * i), 0.0f, kGridHalfWidth);

		Vector3 ndcVertex_Start = Transform(position_Start, viewProjectionMatrix);
		Vector3 screenVertices_Start = Transform(ndcVertex_Start, viewportMatrix);

		Vector3 ndcVertex_End = Transform(position_End, viewProjectionMatrix);
		Vector3 screenVertices_End = Transform(ndcVertex_End, viewportMatrix);

		if (zIndex == kSubdivision / 2) {
			Novice::DrawLine(static_cast<int>(screenVertices_Start.x), static_cast<int>(screenVertices_Start.y), static_cast<int>(screenVertices_End.x), static_cast<int>(screenVertices_End.y), 0x000000FF);
		}
		else {
			Novice::DrawLine(static_cast<int>(screenVertices_Start.x), static_cast<int>(screenVertices_Start.y), static_cast<int>(screenVertices_End.x), static_cast<int>(screenVertices_End.y), 0xAAAAAAFF);
		}
	}
}

void DrawSphere(const Sphere& sphere, const mat4x4& viewProjectionMatrix, const mat4x4& viewportMatrix, uint32_t color) {
	// 分割数
	const uint32_t kSubdivision = 16;
	// 経度分割1つ分の角度
	const float kLonEvery = static_cast<float>(M_PI) * 2.0f / kSubdivision;;
	// 緯度分割1つ分の角度
	const float kLatEvery = static_cast<float>(M_PI) / kSubdivision;

	// 緯度の方向に分割 -M_PI/2 ~ M_PI/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		//現在の緯度
		float lat = static_cast<float>(-M_PI) / 2.0f + kLatEvery * latIndex;
		// 経度の方向に分割 0 ~ 2*M_PI
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			// 現在の経度
			float lon = lonIndex * kLonEvery;
			// world座標系でのa,b,cを求める
			Vector3 a, b, c;
			a = sphere.center_ + (Vector3(std::cos(lat) * std::cos(lon), std::sin(lat), std::cos(lat) * std::sin(lon)) * sphere.radius_);
			b = sphere.center_ + (Vector3(std::cos(lat + kLatEvery) * std::cos(lon), std::sin(lat + kLatEvery), std::cos(lat + kLatEvery) * std::sin(lon)) * sphere.radius_);
			c = sphere.center_ + (Vector3(std::cos(lat) * std::cos(lon + kLonEvery), std::sin(lat), std::cos(lat) * std::sin(lon + kLonEvery)) * sphere.radius_);

			Vector3 ndc_a = Transform(a, viewProjectionMatrix);
			Vector3 screen_a = Transform(ndc_a, viewportMatrix);
			Vector3 ndc_b = Transform(b, viewProjectionMatrix);
			Vector3 screen_b = Transform(ndc_b, viewportMatrix);
			Vector3 ndc_c = Transform(c, viewProjectionMatrix);
			Vector3 screen_c = Transform(ndc_c, viewportMatrix);

			Novice::DrawLine(static_cast<int>(screen_a.x), static_cast<int>(screen_a.y), static_cast<int>(screen_b.x), static_cast<int>(screen_b.y), color);
			Novice::DrawLine(static_cast<int>(screen_a.x), static_cast<int>(screen_a.y), static_cast<int>(screen_c.x), static_cast<int>(screen_c.y), color);

		}
	}

}

void DrawPlane(const Plane& plane, const mat4x4& viewProjeectionMatrix, const mat4x4& viewportMatrix, uint32_t color) {
	Vector3 center = plane.distanse_ * plane.normal_;// 1
	Vector3 perpendiculars[4];
	perpendiculars[0] = Normalize(Perpendicular(plane.normal_));// 2
	perpendiculars[1] = { -perpendiculars[0].x,-perpendiculars[0].y,-perpendiculars[0].z };
	perpendiculars[2] = Cross(plane.normal_, perpendiculars[0]);// 4
	perpendiculars[3] = { -perpendiculars[2].x,-perpendiculars[2].y,-perpendiculars[2].z };
	// 6
	Vector3 points[4];
	for (int32_t index = 0; index < 4; ++index) {
		Vector3 extend = perpendiculars[index] * 2.0f;
		Vector3 point = center + extend;
		points[index] = Transform(Transform(point, viewProjeectionMatrix), viewportMatrix);
	}
	Novice::DrawLine(static_cast<int>(points[0].x), static_cast<int>(points[0].y), static_cast<int>(points[3].x), static_cast<int>(points[3].y), color);
	Novice::DrawLine(static_cast<int>(points[0].x), static_cast<int>(points[0].y), static_cast<int>(points[2].x), static_cast<int>(points[2].y), color);
	Novice::DrawLine(static_cast<int>(points[1].x), static_cast<int>(points[1].y), static_cast<int>(points[2].x), static_cast<int>(points[2].y), color);
	Novice::DrawLine(static_cast<int>(points[1].x), static_cast<int>(points[1].y), static_cast<int>(points[3].x), static_cast<int>(points[3].y), color);
}

void DrawTriangle(const Triangle& triangle, const mat4x4& viewProjectionMatrix, const mat4x4& viewPortMatrix, uint32_t color) {
	Vector3 ndc_a = Transform(triangle.vertices[0], viewProjectionMatrix);
	Vector3 screen_a = Transform(ndc_a, viewPortMatrix);
	Vector3 ndc_b = Transform(triangle.vertices[1], viewProjectionMatrix);
	Vector3 screen_b = Transform(ndc_b, viewPortMatrix);
	Vector3 ndc_c = Transform(triangle.vertices[2], viewProjectionMatrix);
	Vector3 screen_c = Transform(ndc_c, viewPortMatrix);
	Novice::DrawTriangle(static_cast<int>(screen_a.x), static_cast<int>(screen_a.y), static_cast<int>(screen_b.x), static_cast<int>(screen_b.y), static_cast<int>(screen_c.x), static_cast<int>(screen_c.y), color, kFillModeWireFrame);
}

void DrawAABB(const AABB& aabb, const mat4x4& viewProjectionMatrix, const mat4x4& viewPortMatrix, uint32_t color) {
	Vector3 vertices[] = {
		{aabb.min},
		{aabb.max.x,aabb.min.y,aabb.min.z},
		{aabb.max.x,aabb.min.y,aabb.max.z},
		{aabb.min.x,aabb.min.y,aabb.max.z},
		{aabb.min.x,aabb.max.y,aabb.min.z},
		{aabb.max.x,aabb.max.y,aabb.min.z},
		{aabb.max},
		{aabb.min.x,aabb.max.y,aabb.max.z},
	};
	for (int i = 0; i < 4; i++) {
		int j = (i + 1) % 4;
		DrawLine(vertices[i], vertices[j], viewProjectionMatrix, viewPortMatrix,color);
		DrawLine(vertices[i], vertices[i + 4], viewProjectionMatrix, viewPortMatrix, color);
		DrawLine(vertices[i + 4], vertices[j + 4], viewProjectionMatrix, viewPortMatrix, color);
	}
}

void DrawOBB(const OBB& obb, const mat4x4& viewProjectionMatrix, const mat4x4& viewPortMatrix, uint32_t color) {

	Vector3 vertices[] = {
		{-obb.size},
		{+obb.size.x,-obb.size.y,-obb.size.z},
		{+obb.size.x,-obb.size.y,+obb.size.z},
		{-obb.size.x,-obb.size.y,+obb.size.z},
		{-obb.size.x,+obb.size.y,-obb.size.z},
		{+obb.size.x,+obb.size.y,-obb.size.z},
		{ obb.size},
		{-obb.size.x,+obb.size.y,+obb.size.z},
	};

	mat4x4 rotateMatrix = SetRotate(obb.orientations);
	for (auto& vertex : vertices) {
		vertex = Transform(vertex, rotateMatrix);
		vertex = vertex + obb.center;
		Vector3 ndc = Transform(vertex, viewProjectionMatrix);
		vertex = Transform(ndc, viewPortMatrix);
	}

	for (int i = 0; i < 4; i++) {
		int j = (i + 1) % 4;
		DrawLine(vertices[i], vertices[j], color);
		DrawLine(vertices[i], vertices[i + 4], color);
		DrawLine(vertices[i + 4], vertices[j + 4], color);
	}
}

void DrawBezier(const Vector3& v1, const Vector3& v2, const Vector3& v3,const mat4x4& viewProjectionMatrix, const mat4x4& viewPortMatrix, uint32_t color) {
	const int32_t DivisionCount = 16;
	for (float i = 1.0f; i < DivisionCount; i++) {
		DrawLine(
			CubicBezier(v1, v2, v3, static_cast<float>(i - 1) / static_cast<float>(DivisionCount)), 
			CubicBezier(v1, v2, v3, static_cast<float>(i) / static_cast<float>(DivisionCount)),
			viewProjectionMatrix,
			viewPortMatrix,
			color);
	}
}

void DrawCatmullRom(const Vector3 v0, const Vector3& v1, const Vector3& v2, const Vector3& v3, const mat4x4& viewProjectionMatrix, const mat4x4& viewPortMatrix, uint32_t color) {
	const int32_t DivisionCount = 100;
	for (float i = 1.0f; i < DivisionCount; i++) {
		// p0,p1間
		DrawLine(
			CubicCatmullRom(v0, v0, v1, v2, static_cast<float>(i - 1) / static_cast<float>(DivisionCount)),
			CubicCatmullRom(v0, v0, v1, v2, static_cast<float>(i) / static_cast<float>(DivisionCount)),
			viewProjectionMatrix,
			viewPortMatrix,
			color);
		// p1,p2間
		DrawLine(
			CubicCatmullRom(v0, v1, v2, v3, static_cast<float>(i - 1) / static_cast<float>(DivisionCount)),
			CubicCatmullRom(v0, v1, v2, v3,  static_cast<float>(i) / static_cast<float>(DivisionCount)),
			viewProjectionMatrix,
			viewPortMatrix,
			color);
		// p2,p3間
		DrawLine(
			CubicCatmullRom(v1, v2, v3, v3, static_cast<float>(i - 1) / static_cast<float>(DivisionCount)),
			CubicCatmullRom(v1, v2, v3, v3, static_cast<float>(i) / static_cast<float>(DivisionCount)),
			viewProjectionMatrix,
			viewPortMatrix,
			color);
	}
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	Vector3 cameraScale{ 1.0f,1.0f,1.0f };
	Vector3 cameraTranslate{ 0.0f,1.9f,-6.49f };
	Vector3 cameraRotate{ 0.26f,0.0f,0.0f };

	Segment segment{ {0.0f,0.3f,-0.3f},{0.0f,0.3f,1.0f} };
	int32_t segmentColor = WHITE;
	Line line{ {0.0f,0.3f,-0.3f},{0.0f,0.3f,1.0f} };
	int32_t lineColor = WHITE;
	Ray ray{ {0.0f,0.3f,-0.3f},{0.0f,0.3f,0.3f} };
	int32_t rayColor = WHITE;
	Vector3 point{ -1.5f,0.6f,0.6f };


	Vector3 kLocalvertices[3];
	kLocalvertices[0] = { 0.5f,0.0f,0.0f };
	kLocalvertices[1] = { -0.5f,0.0f,0.0f };
	kLocalvertices[2] = { 0.0f,1.0f,0.0f };

	Sphere sphere_ = {
		{0.0f,0.0f,0.0f},
		{0.5f}
	};

	Plane plane_ = {
		{0.0f,1.0f,0.0f},
		{0.0f}
	};

	Triangle triangle = {
		{
		{-1.0f,0.0f,0.0f},
		{0.0f,1.0f,0.0f},
		{1.0f,0.0f,0.0f},
		}
	};

	Vector3 rotate{ 0.0f,0.0f,0.0f };

	OBB obb_0{
		.center{-2.0f,0.0f,0.0f},
		.orientations = {
		{1.0f,0.0f,0.0f},
		{0.0f,1.0f,0.0f},
		{0.0f,0.0f,1.0f},},
		.size{0.5f,0.5f,0.5f},
	};
	OBB obb_1{
		.center{0.0f,0.0f,0.0f},
		.orientations = {
		{1.0f,0.0f,0.0f},
		{0.0f,1.0f,0.0f},
		{0.0f,0.0f,1.0f},},
		.size{0.5f,0.5f,0.5f},
	};

	AABB aabb_1{
		.min{-0.5f, -0.5f, -0.5f},
		.max{0.5f, 0.5f, 0.5f},
	};
	int32_t aabb_1Color = WHITE;

	AABB aabb_2{
		.min{0.2f,0.2f,0.2f},
		.max{1.0f,1.0f,1.0f},
	};
	int32_t aabb_2Color = WHITE;

	Vector3 controlPoints[4] = {
		{-0.8f,0.58f,1.0f},
		{1.76f,1.0f,-0.3f},
		{0.94f,-0.7f,2.3f},
		{-0.53f,-0.26f,0.15f},
	};

	Vector3 translates[3] = {
		{0.2f,1.0f,0.0f},
		{0.4f,0.0f,0.0f},
		{0.3f,0.0f,0.0f},
	};

	Vector3 rotates[3] = {
		{0.0f,0.0f,-6.8f},
		{0.0f,0.0f,-1.8f},
		{0.0f,0.0f,0.0f},
	};

	Vector3 scales[3] = {
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f},
	};
	mat4x4 shoulder = MakeAffineMatrix(scales[0],rotates[0],translates[0]);
	mat4x4 elbow = MakeAffineMatrix(scales[1],rotates[1],translates[1]);
	mat4x4 hand= MakeAffineMatrix(scales[2],rotates[2],translates[2]);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		mat4x4 cameraMatrix = MakeAffineMatrix(cameraScale, cameraRotate, cameraTranslate);
		mat4x4 viewMatrix = Inverse(cameraMatrix);
		mat4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		mat4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
		Vector3 screenVertices[3];
		for (uint32_t i = 0; i < 3; ++i) {
			Vector3 ndcVertex = Transform(kLocalvertices[i], Mul(viewMatrix, projectionMatrix));
			screenVertices[i] = Transform(ndcVertex, viewportMatrix);
		}

		mat4x4 viewProjectMatrix = Mul(viewMatrix, projectionMatrix);

		// 回転行列から軸を抽出

		ImGui::Begin("window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::End();

		/*ImGui::Begin("obb");
		ImGui::DragFloat3("rotate", &rotate.x, 0.01f);
		ImGui::DragFloat3("center", &obb_0.center.x, 0.01f);
		ImGui::End();

		obb_0 = OBBSetRotate(obb_0, rotate);*/

		ImGui::Begin("point");
		ImGui::DragFloat3("scales[0]", &scales[0].x, 0.01f);
		ImGui::DragFloat3("rotates[0]", &rotates[0].x, 0.01f);
		ImGui::DragFloat3("translates[0]", &translates[0].x, 0.01f);
		ImGui::DragFloat3("scales[1]", &scales[1].x, 0.01f);
		ImGui::DragFloat3("rotates[1]", &rotates[1].x, 0.01f);
		ImGui::DragFloat3("translates[1]", &translates[1].x, 0.01f);
		ImGui::DragFloat3("scales[2]", &scales[2].x, 0.01f);
		ImGui::DragFloat3("rotates[2]", &rotates[2].x, 0.01f);
		ImGui::DragFloat3("translates[2]", &translates[2].x, 0.01f);
		ImGui::End();

		shoulder = MakeAffineMatrix(scales[0], rotates[0], translates[0]);
		elbow = Mul(MakeAffineMatrix(scales[1], rotates[1], translates[1]), shoulder);
		hand = Mul(MakeAffineMatrix(scales[2], rotates[2], translates[2]), elbow);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		DrawGrid(viewProjectMatrix, viewportMatrix);
		/*if (IsCollision(obb_0, obb_1)) {
			aabb_1Color = RED;
		}
		else {
			aabb_1Color = WHITE;
		}*/
		DrawSphere(Sphere(GetTranslates(shoulder), 0.05f), viewProjectMatrix, viewportMatrix, RED);
		DrawSphere(Sphere(GetTranslates(elbow), 0.05f), viewProjectMatrix, viewportMatrix, GREEN);
		DrawSphere(Sphere(GetTranslates(hand), 0.05f), viewProjectMatrix, viewportMatrix, BLUE);
		DrawLine(GetTranslates(shoulder), GetTranslates(elbow), viewProjectMatrix, viewportMatrix,WHITE);
		DrawLine(GetTranslates(elbow), GetTranslates(hand), viewProjectMatrix, viewportMatrix,WHITE);
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}