#include <Novice.h>
#include <cstdint>
#include "mat4x4.h"
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

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	Vector3 scale{ 1.0f,1.0f,1.0f };
	Vector3 rotate{ 0.0f,0.0f,0.0f };
	Vector3 translate{ 0.0f,0.0f,10.0f };
	Vector3 cameraPosition{ 0.0f,0.0f,0.0f };

	Vector3 kLocalvertices[3];
	kLocalvertices[0] = { 0.5f,0.0f,0.0f };
	kLocalvertices[1] = { -0.5f,0.0f,0.0f };
	kLocalvertices[2] = { 0.0f,1.0f,0.0f };

	Vector3 v1{ 1.2f,-3.9f,2.5f };
	Vector3 v2{ 2.8f,0.4f,-1.3f };



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
		mat4x4 cameraMatrix = MakeAffineMatrix(scale, { 0.0f,0.0f,0.0f }, cameraPosition);
		mat4x4 viewMatrix = Inverse(cameraMatrix);
		mat4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		mat4x4 worldViewProjectionMatrix = Mul(worldMatrix, Mul(viewMatrix, projectionMatrix));
		mat4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
		Vector3 screenVertices[3];
		for (uint32_t i = 0; i < 3; ++i) {
			Vector3 ndcVertex = Transform(kLocalvertices[i], worldViewProjectionMatrix);
			screenVertices[i] = Transform(ndcVertex, viewportMatrix);
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		VectorScreenPrintf(0, 0, cross, "Cross");
		Novice::DrawTriangle(
			int(screenVertices[0].x), int(screenVertices[0].y),
			int(screenVertices[1].x), int(screenVertices[1].y),
			int(screenVertices[2].x), int(screenVertices[2].y),
			RED, kFillModeSolid
		);
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