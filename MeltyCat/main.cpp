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
	int x = 360, y = 480, r = 32, moveX = 2, moveY = 0;
	/*PlayArea*/
	int edgeL = 320;
	/*JampPad*/
	enum Jamp { LU, LD, RU, RD };
	int jampX = 672, jampY = 480, vector = LU;

	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };

	// �Q�[�����[�v
	while (1)
	{
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 256; i++) {
			oldkeys[i] = keys[i];
		}
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
		/*Player_Moving*/
		x += moveX;
		y += moveY;
		if (x <= edgeL + r || x >= WIN_WIDTH - r) {
			moveX = -moveX;
		}
		if (y <= 0 + r || y >= WIN_HEIGHT - r) {
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

		// �`�揈��
		/*PlaeArea*/
		DrawBox(edgeL, 0, WIN_WIDTH, WIN_HEIGHT, GetColor(255, 192, 192), true);
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 12; j++) {
				DrawBox(i * 64 + edgeL, j * 64, (i + 1) * 64 + edgeL, (j + 1) * 64, GetColor(255, 255, 255), false);
			}
		}
		/*JampPad*/
		switch (vector) {
		case LU:
			DrawTriangle(jampX - r, jampY + r, jampX + r, jampY - r, jampX + r, jampY + r, GetColor(192, 255, 192), true);
			break;

		case LD:
			DrawTriangle(jampX - r, jampY - r, jampX + r, jampY + r, jampX + r, jampY - r, GetColor(192, 255, 192), true);
			break;

		case RU:
			DrawTriangle(jampX + r, jampY + r, jampX - r, jampY - r, jampX - r, jampY + r, GetColor(192, 255, 192), true);
			break;

		case RD:
			DrawTriangle(jampX + r, jampY - r, jampX - r, jampY + r, jampX - r, jampY - r, GetColor(192, 255, 192), true);
			break;

		}
		/*Player*/
		DrawCircle(x, y, r, GetColor(255, 255, 255), true);

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