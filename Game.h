#pragma once




#include "DxLib.h"
#include "Mouse.h"

//�}�N����`
#define width  1920
#define height 1080
#define bit		32
#define GameTitle "CreyShooting"
#define GameVsync true

#define DebugMode false //�f�o�b�O���[�h

#define GameSceneCount 8 //�V�[���̐�
#define GameSceneNameMax 20 //�V�[�����̕�����

#define GameSceneChangeFrame 60 //�V�[���؂�ւ����\�ɂȂ�o�߃t���[����

#define WinScore 5 // �����X�R�A

//���������֐��p�̃}�N����`











//�Q�[���V�[��
enum GameScene{
	TitleScene,
	MainScene,
	AtackScene,
	DefScene,
	ResultScene,
	ShopScene,
	SoloScene,
	OptionScene,
	TutorialScene,
};




//�O���[�o���ϐ�
extern enum GameScene NowGameScene; //���݂̃Q�[���V�[��
extern enum GameScene ChangeGameScene; //�ڍs��̃Q�[���V�[��


extern float AtackScore;//�U�����̃X�R�A
extern float DefenceScore;//�h�q���̃X�R�A

//���ˑ�\����
typedef struct _hasya {
	bool color = true;
	int v = 1;
	int r = 1;
	//----------------------�ގ��@---------------------
	bool zaisitu = false;
	//int cost = 0;
}hasya;

extern hasya hasyaL;
extern hasya hasyaR;

//�N���C�̍\����
typedef struct _cley 
{
	VECTOR Position;//�ʒu
	VECTOR Velocity;//�ړ��̑���
	VECTOR Angle;	//�p�x
	VECTOR BreakPosition;//2��ꂽ�ʒu
	VECTOR Dir;	//�N���C�̕���
	int Color = 0;		//�F (1 => �F�A�@2 => �ԐF�@)
	bool IsMoving = false;	//�����Ă����Ԃ��ۂ�
	int Break;//2�̃N���[����ꂽ���ۂ�
	float BreakMoveX;//2����ꂽ��̃A�j���[�V��������X
	float BreakMoveY;//2����ꂽ��̃A�j���[�V��������Y
	float BreakMoveYgravity; //2����ꂽ��̃A�j���[�V��������Y�d��
	int StartTime = 0;		//�����o�����ŏ��̎���
	float Speed = 0;		//���x
	bool Shooted = false;


}cley;

extern cley Cley1;
extern cley Cley2;

//�e�̍\����
typedef struct _bullet {


	bool IsMoving = false;  // �ϐ��̏�����
	int StartTime = 0;      // �ϐ��̏�����
	VECTOR Position;	//�e�̈ʒu
	VECTOR Angle;			//�p�x
	int Color; //�F�@�@1 => �F�@, 2 => �ԐF



}bullet;

extern bullet Bullet1;//�e�P
extern bullet Bullet2;//�e�Q




//�A�v���P�[�V�����I�����ɁA�������[�Ɋi�[���ꂽ���Ɖ摜�̃f�[�^���������
extern void Releace();


//�O���t�B�b�N��ǂݍ���

extern void TitleTextureLoad(void); //�^�C�g��
extern void HomeTextureLoad(void);	//�z�[��
extern void ResultTextureLoad(void);//���U���g
extern void ShopTextureLoad(void);//�V���b�v


//���͂���x1,y1,x2,y2�̂Q�_�Ԃ̒�������肾���B
extern int SetLineToMouse(float x1, float y1, float x2, float y2);

//4�̓_�̍��W����Ui�͈̔͂�n��o���B
extern bool SetUI(float L_up_X, float L_up_Y, float R_up_x, float R_up_y, float L_down_x, float L_down_y, float R_down_x, float R_down_y);

extern bool CheckCollision(VECTOR spherePos, float sphereRadius, VECTOR boxPos, VECTOR boxSize);





//�V�[���֘A�̊֐��̃v���g�^�C�v�錾
extern void TitleInit(void); //�^�C�g��������
extern void TitleCtrl(void); //�^�C�g���Ǘ�
extern void TitleProc(void); //�^�C�g������
extern void TitleDraw(void); //�^�C�g���`��

extern void MainInit(void); //���C��������
extern void MainCtrl(void); //���C���Ǘ�
extern void MainProc(void); //���C������
extern void MainDraw(void); //���C���`��

//�h�q���
extern void DefInit(void); //�h�q������
extern void DefCtrl(void);	//�h�q�Ǘ�
extern void DefProc(void);	//�h�q����
extern void DefDraw(void);	//�h�q�`��

//�U�����
extern void AtackInit(void);//�U��������
extern void AtackCtrl(void);//�U���Ǘ�
extern void AtackProc(void);//�U������
extern void AtackDraw(void);//�U���`��

//���U���g���
extern void ResultInit(void); //���U���g������
extern void ResultCtrl(void); //���U���g�Ǘ�
extern void ResultProc(void); //���U���g����
extern void ResultDraw(void); //���U���g�`��


//�V���b�v���
extern void ShopInit(void); //���U���g������
extern void ShopCtrl(void); //���U���g�Ǘ�
extern void ShopProc(void); //���U���g����
extern void ShopDraw(void); //���U���g�`��


//solo���
extern void SoloInit(void); //�\��������
extern void SoloCtrl(void); //�\���Ǘ�
extern void SoloProc(void); //�\������
extern void SoloDraw(void); //�\���`��


//�I�v�V�������
extern void OptionInit(void); //���U���g������
extern void OptionCtrl(void); //���U���g�Ǘ�
extern void OptionProc(void); //���U���g����
extern void OptionDraw(void); //���U���g�`��



//�I�v�V�������
extern void TutorialInit(void); //���U���g������
extern void TutorialCtrl(void); //���U���g�Ǘ�
extern void TutorialProc(void); //���U���g����
extern void TutorialDraw(void); //���U���g�`��
