#include "DxLib.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "MeltyCat";

// ウィンドウ横幅
const int WIN_WIDTH = 1280;

// ウィンドウ縦幅
const int WIN_HEIGHT = 768;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x80, 0x80, 0xFF);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み


	// ゲームループで使う変数の宣言
	/*Player*/
	enum Cat { SOLID/*固体*/, LIQUID/*液体*/ };
	int x = 800/*edgeL+7×64+r*/, y = 352/*5×64+r*/, r = 32, moveX = 2, moveY = 0, state = SOLID;
	/*Item*/
	int itemX = 1120/* edgeL+12×64+r */, itemY = 160/* 2×64+r */, itemPut = 1;
	/*PlayArea*/
	const int edgeL = 320;
	/*JampPad*/
	enum Jamp { LU, LD, RD, RU };/*Left,Right,Up,Down*/
	int jampX = 0, jampY = 0, jampPut = 0, vector = LU;
	/*Cursor*/
	int cursorX, cursorY, putX, putY, putVector = LU;

	/*MapChip*/
	int map[12][15] = {
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
	};

	// 最新のキーボード情報用
	char keys[256] = { 0 };
	int click = 0;

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };
	int oldclick = 0;

	// ゲームループ
	while (1)
	{
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; i++) {
			oldkeys[i] = keys[i];
		}
		oldclick = click;
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);
		click = GetMouseInput();

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
		/*Player_Moving*/
		x += moveX;
		y += moveY;
		if (x < edgeL + r || x > WIN_WIDTH - r) {
			moveX = -moveX;
		}
		if (y < 0 + r || y > WIN_HEIGHT - r) {
			moveY = -moveY;
		}
		/*Player_Turning*/
		if (x == jampX && y == jampY && moveX > 0) {
			if (vector == LU) {
				moveX = 0;
				moveY = -2;
			}
			else if (vector == LD) {
				moveX = 0;
				moveY = 2;
			}
		}
		else if (x == jampX && y == jampY && moveX < 0) {
			if (vector == RU) {
				moveX = 0;
				moveY = -2;
			}
			else if (vector == RD) {
				moveX = 0;
				moveY = 2;
			}
		}
		else if (x == jampX && y == jampY && moveY > 0) {
			if (vector == LU) {
				moveX = -2;
				moveY = 0;
			}
			else if (vector == RU) {
				moveX = 2;
				moveY = 0;
			}
		}
		else if (x == jampX && y == jampY && moveY < 0) {
			if (vector == LD) {
				moveX = -2;
				moveY = 0;
			}
			else if (vector == RD) {
				moveX = 2;
				moveY = 0;
			}
		}
		/*State_Switch*/
		if (itemPut == 1 && (x - edgeL) / 64 == (itemX - edgeL) / 64 && y / 64 == itemY / 64) {
			itemPut = 0;
			state++;
			if (state > LIQUID) {
				state = SOLID;
			}
		}
		/*Cursor_Operate*/
		GetMousePoint(&cursorX, &cursorY);
		putX = (cursorX - edgeL) / 64 * 64 + edgeL + 32;
		putY = cursorY / 64 * 64 + 32;
		/*JampPad_Spining*/
		if (keys[KEY_INPUT_LSHIFT] == 1 && oldkeys[KEY_INPUT_LSHIFT] == 0) {
			putVector++;
			if (putVector > RU) {
				putVector = LU;
			}
		}
		/*JampPad_Putting*/
		if ((oldclick & MOUSE_INPUT_LEFT) == 0 && (click & MOUSE_INPUT_LEFT) == 1) {
			jampX = putX;
			jampY = putY;
			vector = putVector;
			jampPut = 1;
		}

		// 描画処理
		/*PlaeArea*/
		DrawBox(edgeL, 0, WIN_WIDTH, WIN_HEIGHT, GetColor(255, 192, 192), true);
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 12; j++) {
				DrawBox(i * 64 + edgeL, j * 64, (i + 1) * 64 + edgeL, (j + 1) * 64, GetColor(255, 255, 255), false);
			}
		}
		/*PutBox*/
		if (cursorX >= edgeL && cursorX <= WIN_WIDTH && cursorY >= 0 && cursorY <= WIN_HEIGHT) {
			DrawBox(putX - 32, putY - 32, putX + 32, putY + 32, GetColor(255, 255, 0), false);
		}
		switch (putVector) {
		case LU:
			DrawTriangle(cursorX - r, cursorY + r, cursorX + r, cursorY - r, cursorX + r, cursorY + r, GetColor(192, 255, 192), true);
			break;

		case LD:
			DrawTriangle(cursorX - r, cursorY - r, cursorX + r, cursorY + r, cursorX + r, cursorY - r, GetColor(192, 255, 192), true);
			break;

		case RD:
			DrawTriangle(cursorX + r, cursorY - r, cursorX - r, cursorY + r, cursorX - r, cursorY - r, GetColor(192, 255, 192), true);
			break;

		case RU:
			DrawTriangle(cursorX + r, cursorY + r, cursorX - r, cursorY - r, cursorX - r, cursorY + r, GetColor(192, 255, 192), true);
			break;
		}

		/*JampPad*/
		if (jampPut == 1) {
			switch (vector) {
			case LU:
				DrawTriangle(jampX - r, jampY + r, jampX + r, jampY - r, jampX + r, jampY + r, GetColor(192, 255, 192), true);
				break;

			case LD:
				DrawTriangle(jampX - r, jampY - r, jampX + r, jampY + r, jampX + r, jampY - r, GetColor(192, 255, 192), true);
				break;

			case RD:
				DrawTriangle(jampX + r, jampY - r, jampX - r, jampY + r, jampX - r, jampY - r, GetColor(192, 255, 192), true);
				break;

			case RU:
				DrawTriangle(jampX + r, jampY + r, jampX - r, jampY - r, jampX - r, jampY + r, GetColor(192, 255, 192), true);
				break;
			}
		}
		/*SwitchItem*/
		if (itemPut == 1) {
			DrawCircle(itemX, itemY, 8, GetColor(112, 112, 255), true);
		}
		/*Player*/
		if (state == SOLID) {
			DrawCircle(x, y, r, GetColor(255, 255, 128), true);
		}
		else if (state == LIQUID) {
			DrawCircle(x, y, r, GetColor(128, 128, 255), true);
		}

		/*デバッグコード*/
//		DrawFormatString(0, 0, GetColor(255, 255, 255), "");

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1)
		{
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}