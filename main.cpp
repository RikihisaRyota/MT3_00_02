#include <Novice.h>
#include "mat4x4.h"
const char kWindowTitle[] = "学籍番号";

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

void MatrixScreenPrintf(int x, int y, const mat4x4& mat, const char* label) {
	Novice::ScreenPrintf(x, y, "%s", label);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight + kRowHeight, "%6.02f", mat.m[row][column]);
		}
	}

}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	//m1
	mat4x4 m1 = {
		3.2f, 0.7f, 9.6f, 4.4f,
		5.5f, 1.3f, 7.8f, 2.1f,
		6.9f, 8.0f, 2.6f, 1.0f,
		0.5f, 7.2f, 5.1f, 3.3f
	};
	//m2
	mat4x4 m2 = {
		4.1f, 6.5f, 3.3f, 2.2f,
		8.8f, 0.6f, 9.9f, 7.7f,
		1.1f, 5.5f, 6.6f, 0.0f,
		3.3f, 9.9f, 8.8f, 2.2f
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
		mat4x4 resultAdd = Add(m1, m2);
		mat4x4 resultMul = Mul(m1, m2);
		mat4x4 resultSub = Sub(m1, m2);
		mat4x4 resultInverseM1 = Inverse(m1);
		mat4x4 resultInverseM2 = Inverse(m2);
		mat4x4 resultTransposeM1 = Transpose(m1);
		mat4x4 resultTransposeM2 = Transpose(m2);
		mat4x4 identity = MakeIdentity4x4();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		MatrixScreenPrintf(0, 0, resultAdd, "Add");
		MatrixScreenPrintf(0, kRowHeight * 5, resultSub, "Sub");
		MatrixScreenPrintf(0, kRowHeight * 5 * 2, resultMul, "Mul");
		MatrixScreenPrintf(0, kRowHeight * 5 * 3, resultInverseM1, "InverseM1");
		MatrixScreenPrintf(0, kRowHeight * 5 * 4, resultInverseM2, "InverseM2");

		MatrixScreenPrintf(kColumnWidth * 5, 0, resultTransposeM1, "TransposeM1");
		MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 5, resultTransposeM2, "TransposeM2");
		MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 5 * 2, identity, "identity");
		///
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