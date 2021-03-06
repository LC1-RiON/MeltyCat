#include "DxLib.h"
#include "Player.h"
#include "Block.h"
#include "Item.h"
#include "Cursor.h"

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
	Player* player = new Player(800, 352, 32, 2, 0, SOLID);
	/*JampBlock*/
	enum Jamp { LU, LD, RD, RU };/*Left,Right,Up,Down*/
	Block* block = new Block(0, 0, 32, 0, LU);
	/*Goal*/

	/*Item*/
	Item* item = new Item(1120, 160, 8, 1);
	/*PlayArea*/
	const int edgeL = 320;
	/*Cursor*/
	Cursor* cursor = new Cursor(0, 0, 32, 0, 0, LU);

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
		player->Update(edgeL, WIN_WIDTH, WIN_HEIGHT, block, item);
		block->Update();
		item->Update();
		cursor->Update(edgeL, keys, oldkeys, click, oldclick, block, WIN_WIDTH, WIN_HEIGHT);

		// 描画処理
		/*PlaeArea*/
		DrawBox(edgeL, 0, WIN_WIDTH, WIN_HEIGHT, GetColor(255, 192, 192), true);
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 12; j++) {
				DrawBox(i * 64 + edgeL, j * 64, (i + 1) * 64 + edgeL, (j + 1) * 64, GetColor(255, 255, 255), false);
			}
		}

		cursor->Draw(edgeL, WIN_WIDTH, WIN_HEIGHT);
		block->Draw();
		item->Draw();
		player->Draw();

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