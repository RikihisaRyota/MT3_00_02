#include <Novice.h>
#include <cstdint>
#include "imgui.h"
#include "mat4x4.h"
#include "Sphere.h"
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
	const uint32_t kSubdivision = 30;
	// 経度分割1つ分の角度
	const float kLonEvery = (360.0f / kSubdivision)* static_cast<float>(M_PI) / 180.0f;
	// 緯度分割1つ分の角度
	const float kLatEvery = (360.0f / kSubdivision) * static_cast<float>(M_PI) / 180.0f;

	float theta_b = static_cast<float>(M_PI) / kSubdivision;
	float ph_b = static_cast<float>(M_PI) * 2.0f / kSubdivision;
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
			a = sphere.center_ + (Vector3(cosf(lat) * cosf(lon), sinf(lat), cosf(lat) * sinf(lon)) * sphere.radius_);
			b = sphere.center_ + (Vector3(cosf(lat + theta_b) * cosf(lon), sinf(lat + theta_b), cosf(lat + theta_b) * sinf(lon)) * sphere.radius_);
			c = sphere.center_ + (Vector3(cosf(lat) * cosf(lon + ph_b), sinf(lat), cosf(lat) * sinf(lon + ph_b)) * sphere.radius_);

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

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	Vector3 scale{ 1.0f,1.0f,1.0f };
	Vector3 rotate{ 0.0f,0.0f,0.0f };
	Vector3 translate{ 0.0f,0.0f,0.0f };
	Vector3 camera{ 0.0f,0.0f,1.0f };
	Vector3 cameraScale{ 1.0f,1.0f,1.0f };
	Vector3 cameraTranslate{ 0.0f,1.9f,-6.49f };
	Vector3 cameraRotate{ 0.26f,0.0f,0.0f };

	Vector3 kLocalvertices[3];
	kLocalvertices[0] = { 0.5f,0.0f,0.0f };
	kLocalvertices[1] = { -0.5f,0.0f,0.0f };
	kLocalvertices[2] = { 0.0f,1.0f,0.0f };

	Vector3 v1{ 1.2f,-3.9f,2.5f };
	Vector3 v2{ 2.8f,0.4f,-1.3f };


	Sphere sphere = {
		{0.0f,0.0f,0.0f},
		{0.5f}
	};

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
		Vector3 cross = Cross(v1, v2);

		if (keys[DIK_W]) {
			translate.z += 0.1f;
		}
		if (keys[DIK_S]) {
			translate.z -= 0.1f;
		}
		if (keys[DIK_D]) {
			translate.x += 0.1f;
		}
		if (keys[DIK_A]) {
			translate.x -= 0.1f;
		}
		rotate.y += 0.02f;
		mat4x4 worldMatrix = MakeAffineMatrix(scale, rotate, translate);
		mat4x4 cameraMatrix = MakeAffineMatrix(cameraScale, cameraRotate, cameraTranslate);
		mat4x4 viewMatrix = Inverse(cameraMatrix);
		mat4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		mat4x4 worldViewProjectionMatrix = Mul(worldMatrix, Mul(viewMatrix, projectionMatrix));
		mat4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
		Vector3 screenVertices[3];
		for (uint32_t i = 0; i < 3; ++i) {
			Vector3 ndcVertex = Transform(kLocalvertices[i], worldViewProjectionMatrix);
			screenVertices[i] = Transform(ndcVertex, viewportMatrix);
		}
		ImGui::Begin("window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::End();
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		DrawGrid(Mul(viewMatrix, projectionMatrix), viewportMatrix);
		DrawSphere(sphere, Mul(viewMatrix, projectionMatrix), viewportMatrix, BLACK);
		/*VectorScreenPrintf(0, 0, cross, "Cross");*/
		/*if (Dot(camera, (Cross(screenVertices[1] - screenVertices[0], screenVertices[2] - screenVertices[1]))) <= 0.0f) {
			Novice::DrawTriangle(
				int(screenVertices[0].x), int(screenVertices[0].y),
				int(screenVertices[1].x), int(screenVertices[1].y),
				int(screenVertices[2].x), int(screenVertices[2].y),
				RED, kFillModeSolid
			);
		}*/

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