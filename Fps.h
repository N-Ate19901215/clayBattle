#pragma once

#include "DxLib.h"


//�}�N����`
#define GameFPS 60 //�ő�fps
#define MicroSecond 1000000.0f //1�}�C�N���b
#define MillSecond 1000.0f //�~���b
#define WaitTimeMill 3000 //�ő�Ŏ��Ă�~����


//�\���̂̒�`�����O�̍Ē�`
typedef struct _FPS
{
	LONGLONG FirstTakeTime = 0; //1�t���[���ڂ̌v������
	LONGLONG NowTakeTime = 0;  //���݂̌v������
	LONGLONG OldTakeTime = 0;; //�ȑO�̌v������

	float deltaTime = 0.000001f; //�f���^�^�C��(�o�ߎ���)
	int FrameCount = 1;  //���݂̃t���[����(1�t���[���`�ő�t���[���ڂ܂�)
	float Average = 0.0f; //����FPS�l
}FPS;

//�O���O���[�o���ϐ�
extern FPS fps;


//�t���[�����[�g�֘A�̃v���g�^�C�v�錾
extern void FPSInit(void);
extern void FPSCheck(void);
extern void FPSDraw(void);
extern void FPSWait(void);






