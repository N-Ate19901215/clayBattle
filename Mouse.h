#pragma once

#include "DxLib.h"


#define MouseKindMax 3 //�}�E�X�{�^���̎��
#define MouseErrorIndex 999

typedef struct mousepoint
{
	int x;
	int y;
}MousePoint;


//�֐��̃v���g�^�C�v�錾

extern void MouseNowIntoOld(void);				//Now����׌n�̕ϐ��̒l��Old����׌n�̕ϐ��֓����
extern int MouseCodeToIndex(int MOUSE_INPUT_);  //�}�E�X�̂ڂ��񂱁[�ǂ�z��̗v�f���ɕϊ�����

extern void MouseInit(void);//�܂������͏����̏�����
extern void MouseUpdate(void);//�}�E�X���͏����̍X�V
extern bool MouseDown(int MOUSE_INPUT_);//����̃}�E�X�{�^������������
extern bool MousePush(int MOUSE_INPUT_);//�}�E�X�{�^�����������u�Ԃ̔���
extern bool MouseClick(int MOUSE_INPUT_);//����̃}�E�X�{�^�����N���b�N������
extern int  MousePressFrame(int MOUSE_INPUT_);//����̉��O���������t���[���� 


extern MousePoint NowMousePos(void);
extern MousePoint OldMousePos(void);
extern MousePoint DifMousePos(void);
