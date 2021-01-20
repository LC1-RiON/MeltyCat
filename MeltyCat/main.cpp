#include "DxLib.h"

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "MeltyCat";

// �E�B���h�E����
const int WIN_WIDTH = 1280;

// �E�B���h�E�c��
const int WIN_HEIGHT = 768;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x80, 0x80, 0xFF);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���


	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	/*Player*/
	enum Cat { SOLID/*�ő�*/, LIQUID/*�t��*/ };
	int x = 800/*edgeL+7�~64+r*/, y = 352/*5�~64+r*/, r = 32, moveX = 2, moveY = 0, state = SOLID;
	/*Item*/
	int itemX = 1120/* edgeL+12�~64+r */, itemY = 160/* 2�~64+r */, itemPut = 1;
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

	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };
	int click = 0;

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };
	int oldclick = 0;

	// �Q�[�����[�v
	while (1)
	{
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 256; i++) {
			oldkeys[i] = keys[i];
		}
		oldclick = click;
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);
		click = GetMouseInput();

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
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

		// �`�揈��
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

		/*�f�o�b�O�R�[�h*/
//		DrawFormatString(0, 0, GetColor(255, 255, 255), "");

		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1)
		{
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}