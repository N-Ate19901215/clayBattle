#pragma once


#include "DxLib.h"


//�}�N����`
#define KeyKindMax 256 //�L�[�̎��



//�L�[�{�[�h���͊֘A�̃v���g�^�C�v�錾
extern void KeyInit(void);//�L�[���͏����̏�����
extern void KeyUpdate(void);//�L�[���͏����̍X�V
extern bool KeyDown(int KEY_INPUT_);//����̃L�[����������
extern bool KeyPush(int KEY_INPUT_);//I�L�[���������u�Ԃ̔���
extern bool KeyClick(int KEY_INPUT_);//����̃L�[���N���b�N������
extern int KeyPressFrame(int KEY_INPUT_);//����̃L�[���������t���[���� 



